#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, unsigned int gameId, LoggedUser user) :
    m_handlerFactory(handlerFactory), m_gameId(gameId), m_user(user)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == LEAVE_GAME_REQUEST ||
        requestInfo.id == GET_QUESTION_REQUEST ||
        requestInfo.id == SUBMIT_ANSWER_REQUEST ||
        requestInfo.id == GET_GAME_RESULT_REQUEST;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	if (!this->isRequestRelevant(requestInfo))
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}

	try
	{
		switch (requestInfo.id)
		{
		case LEAVE_GAME_REQUEST:
			return this->leaveGame(requestInfo);
			break;

		case GET_QUESTION_REQUEST:
			return this->getQuestion(requestInfo);
			break;

		case SUBMIT_ANSWER_REQUEST:
			return this->submitAnswer(requestInfo);
			break;

		case GET_GAME_RESULT_REQUEST:
			return this->getGameResults(requestInfo);
			break;
		}
	}
	catch (const std::exception& e)
	{
		return {
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ "ERROR" })),
			nullptr
		};
	}
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
	Question question = this->m_handlerFactory.getGameManager()[this->m_gameId].getQuestionForUser(this->m_user);
	map<unsigned int, string> answers = {
		{ 0, question.getCorrectAnswer() },
		{ 1, question.getAnswers()[0] },
		{ 2, question.getAnswers()[1] },
		{ 3, question.getAnswers()[2] }
	};

	return {
		JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse( { 1, question.getQuestion(), answers } )),
		this
	};
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(requestInfo.buffer);

	this->m_handlerFactory.getGameManager()[this->m_gameId].submitAnswer(this->m_user, submitAnswerRequest.answerId);

	return {
		JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse({ 1 })),
		this
	};
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse({ 1, this->m_handlerFactory.getGameManager()[this->m_gameId].getGameResults() })),
		this
	};
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
	this->m_handlerFactory.getGameManager()[this->m_gameId].removePlayer(this->m_user);

	return {
		JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse({ 1 })),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}
