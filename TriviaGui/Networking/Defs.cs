﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaFront.Classes.Networking
{
    public static class Defs
    {
        public const int Port = 8826;
        public const string Ip = "localhost";

        public enum Codes : int
        {
			SIGN_UP_REQUEST,
			LOGIN_REQUEST,
			LOGOUT_REQUEST,
			CREATE_ROOM_REQUEST,
			GET_ROOMS_REQUEST,
			GET_PLAYERS_IN_ROOM_REQUEST,
			JOIN_ROOM_REQUEST,
			GET_STATISTICS_REQUEST,
			CLOSE_ROOM_REQUEST,
			START_GAME_REQUEST,
			GET_ROOM_STATE_REQUEST,
			LEAVE_ROOM_REQUEST,
			LEAVE_GAME_REQUEST,
			GET_QUESTION_REQUEST,
			SUBMIT_ANSWER_REQUEST,
			GET_GAME_RESULT_REQUEST,

			SIGN_UP_RESPONSE,
			LOGIN_RESPONSE,
			LOGOUT_RESPONSE,
			CREATE_ROOM_RESPONSE,
			GET_ROOMS_RESPONSE,
			GET_PLAYERS_IN_ROOM_RESPONSE,
			JOIN_ROOM_RESPONSE,
			GET_STATISTICS_RESPONSE,
			CLOSE_ROOM_RESPONSE,
			START_GAME_RESPONSE,
			GET_ROOM_STATE_RESPONSE,
			LEAVE_ROOM_RESPONSE,
			LEAVE_GAME_RESPONSE,
			GET_QUESTION_RESPONSE,
			SUBMIT_ANSWER_RESPONSE,
			GET_GAME_RESULT_RESPONSE,
			ERROR_RESPONSE
		}
    }
}