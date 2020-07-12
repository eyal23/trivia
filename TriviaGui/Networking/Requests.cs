using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaFront.Classes.Networking
{
    namespace Requests
    {
        public interface IRequest
        {
            [JsonIgnore]
            byte Code
            {
                get;
            }
        }

        public class Login : IRequest
        {
            public string username;
            public string password;

            byte IRequest.Code => 0;
        }

        public class Signup : IRequest
        {
            public string username;
            public string password;
            public string email;

            byte IRequest.Code => 1;
        }

        public class Logout : IRequest
        {
            byte IRequest.Code => 0;
        }

        public class GetRooms : IRequest
        {
            byte IRequest.Code => 1;
        }

        public class GetPlayersInRoom : IRequest
        {
            public string roomName;

            byte IRequest.Code => 2;
        }

        public class GetTop : IRequest
        {
            public int maxUsers = 0;

            byte IRequest.Code => 3;
        }

        public class GetUserStats : IRequest
        {
            public string userName = "";

            byte IRequest.Code => 4;
        }

        public class JoinRoom : IRequest
        {
            public string roomName;

            byte IRequest.Code => 5;
        }

        public class CreateRoom : IRequest
        {
            public string roomName;
            public int maxUsers = 0;
            public int questionCount = 0;
            public int answerTimeout = 0;

            byte IRequest.Code => 6;
        }

        public class ExitRoom : IRequest
        {
            public string roomName;

            byte IRequest.Code => 0;
        }

        public class StartGame : IRequest
        {
            public int status;

            byte IRequest.Code => 1;
        }

        /*public class GetRoomState : IRequest  // unuseful?
        {
            public int status = 0;
            public bool hasGameBegun;
            public List<string> players;
            public int questionCount = 0;
            public int answerAnswer = 0;

            byte IRequest.Code => 0;
        }*/

        public class SubmitAnswer : IRequest
        {
            public string answer;

            byte IRequest.Code => 0;
        }

        public class LeaveGameReq : IRequest
        {
            public int status;

            byte IRequest.Code => 1;
        }
    }
}