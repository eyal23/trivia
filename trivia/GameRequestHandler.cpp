#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


/*
	usage: constructor
	in: the handler factory, the game id, the user
	out: no
*/
GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, unsigned int gameId, LoggedUser user) :
    m_handlerFactory(handlerFactory), m_gameId(gameId), m_user(user)
{
}

/*
	usage: the method checks if a request is relevant
	in: the request info 
	out: if the request is relevant
*/
bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    return requestInfo.id == LEAVE_GAME_REQUEST ||
        requestInfo.id == GET_QUESTION_REQUEST ||
        requestInfo.id == SUBMIT_ANSWER_REQUEST ||
        requestInfo.id == GET_GAME_RESULT_REQUEST;
}

/*
	usage: the method handles a request
	in: the request info
	out: the request result
*/
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
			return this->leaveGame();
			break;

		case GET_QUESTION_REQUEST:
			return this->getQuestion();
			break;

		case SUBMIT_ANSWER_REQUEST:
			return this->submitAnswer(requestInfo);
			break;

		case GET_GAME_RESULT_REQUEST:
			return this->getGameResults();
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

/*
	usage: the method  gets a question for a user
	in: no
	out: the request result
*/
RequestResult GameRequestHandler::getQuestion()
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

/*
	usage: the method submits a user's answer
	in: the request info
	out: the request result
*/
RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(requestInfo.buffer);

	this->m_handlerFactory.getGameManager()[this->m_gameId].submitAnswer(this->m_user, submitAnswerRequest.answerId, submitAnswerRequest.answerTime);

	return {
		JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse({ 1 })),
		this
	};
}

/*
	usage: the method gets a game's results
	in: no
	out: the request result
*/
RequestResult GameRequestHandler::getGameResults()
{
	return {
		JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse({ 1, this->m_handlerFactory.getGameManager()[this->m_gameId].getGameResults() })),
		this
	};
}

/*
	usage: the method removes a user from a game
	in: no
	out: the request result
*/
RequestResult GameRequestHandler::leaveGame()
{
	this->m_handlerFactory.getGameManager()[this->m_gameId].removePlayer(this->m_user);

	return {
		JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse({ 1 })),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}
