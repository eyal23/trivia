#pragma once

#include <iostream>
#include <vector>

#include "Room.h"

using std::string;
using std::vector;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;


typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetStatisticsResponse
{
	unsigned int status;
	vector<string> statistics;
} GetStatisticsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;


class JsonResponsePacketSerializer
{
public:
	static vector<uint8_t> serializeResponse(const ErrorResponse errorRes);
	static vector<uint8_t> serializeResponse(const LoginResponse loginRes);
	static vector<uint8_t> serializeResponse(const SignupResponse signRes);
	static vector<uint8_t> serializeResponse(const LogoutResponse logoutRes);
	static vector<uint8_t> serializeResponse(const GetRoomsResponse getRoomsRes);
	static vector<uint8_t> serializeResponse(const GetPlayersInRoomResponse getPlayersInRoomRes);
	static vector<uint8_t> serializeResponse(const JoinRoomResponse joinRoomRes);
	static vector<uint8_t> serializeResponse(const CreateRoomResponse createRoomRes);
	static vector<uint8_t> serializeResponse(const GetStatisticsResponse getStatisticsRes);

};