#pragma once

#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::uint8_t;

typedef struct LoginRequest
{
	string username;
	string password;
} LoginRequest;

typedef struct SignUpRequest
{
	string username;
	string password;
	string email;
} SingUpRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimout;
} CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
	float answerTime;
} SubmitAnswerRequest;


class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const vector<uint8_t> buffer);
	static SignUpRequest deserializeSignUpRequest(const vector<uint8_t> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const vector<uint8_t> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const vector<uint8_t> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const vector<uint8_t> buffer);
	static SubmitAnswerRequest deserializerSubmitAnswerRequest(const vector<uint8_t> buffer);
};