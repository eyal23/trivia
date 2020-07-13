using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using TriviaFront.Classes.Networking;
using Newtonsoft.Json;
using System.Windows;
using System.Runtime.Serialization.Formatters;
using System.Threading;
using System.IO;
using System.Windows.Threading;

using System.Collections.Generic;

using System.Windows.Interop;

namespace TriviaFront.Classes.Networking
{
    class Communicator
    {
        private TcpClient client = new TcpClient();

        public Communicator()
        {
            StreamReader clientIn;
            StreamWriter clientOut;

            client.BeginConnect(Defs.Ip, Defs.Port, null, null);

            if (client.Connected)
            {
                clientIn = new StreamReader(client.GetStream());
                clientOut = new StreamWriter(client.GetStream());

                clientOut.AutoFlush = true;
            }
        }

        public Responses.Signup submitSignupRequest(Requests.Signup signupRequest)
        {
            return new Responses.Signup(1);
        }

        public Responses.Login submitLoginRequest(Requests.Login loginRequest)
        {
            return new Responses.Login(1);
        }

        public Responses.Logout submitLogoutRequest()
        {
            return new Responses.Logout(1);
        }

        public Responses.CreateRoom submitCreateRoomRequest(Requests.CreateRoom createRoomRequest)
        {
            return new Responses.CreateRoom(1);
        }

        public Responses.GetRooms submitGetRoomsRequest()
        {
            return new Responses.GetRooms(1, new List<string>(new string[] { "room1", "room2", "room3", "room4" }));
        }

        public Responses.GetPlayersInRoom submitGetPlayersInRoomRequest(Requests.GetPlayersInRoom getPlayersInRoomRequest)
        {
            return new Responses.GetPlayersInRoom(1, new List<string>(new string[] { "player1", "player2", "player3", "player4" }));
        }

        public Responses.JoinRoom submitJoinRoomRequest(Requests.JoinRoom joinRoomRequest)
        {
            return new Responses.JoinRoom(1);
        }

        public Responses.GetStatistics submitGetStatisticsRequest()
        {
            return new Responses.GetStatistics(1, (float)5.5, 67, 123, 20, new List<int>(new int[] { 100, 75, 74, 69, 62 }));
        }

        public Responses.CloseRoom submitCloseRoomRequest()
        {
            return new Responses.CloseRoom(1);
        }

        public Responses.StartGame submitStartGameRequest()
        {
            return new Responses.StartGame(1);
        }

        public Responses.GetRoomState submitGetRoomStateRequest()
        {
            return new Responses.GetRoomState(1, false, new List<string>(new string[] { "player1", "player2", "player3", "player4" }), 10, 10);
        }

        public Responses.LeaveRoom submitLeaveRoomRequest()
        {
            return new Responses.LeaveRoom(1);
        }

        public Responses.LeaveGame submitLeaveGameRequest()
        {
            return new Responses.LeaveGame(1);
        }

        public Responses.GetQuestion submitGetQuestionRequest()
        {
            return new Responses.GetQuestion(1, "whats up???", new Dictionary<int, string> { { 0, "asnwer1" }, { 1, "answer2" }, { 2, "answer3" }, { 3, "answer4" } });
        }

        public Responses.SubmitAnswer submitSubmitAnswerRequest(Requests.SubmitAnswer submitAnswerRequest)
        {
            return new Responses.SubmitAnswer(1);
        }

        public Responses.GetGameResults submitGetGameResultsRequest()
        {
            return new Responses.GetGameResults(1, new List<Responses.PlayerResult>(new Responses.PlayerResult[] { new Responses.PlayerResult("user1", 6, 4, (float)5.6), new Responses.PlayerResult("user2", 6, 4, (float)5.6), new Responses.PlayerResult("user3", 6, 4, (float)5.6), new Responses.PlayerResult("user4", 6, 4, (float)5.6) }));
        }
    }
}