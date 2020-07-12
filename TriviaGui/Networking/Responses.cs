using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaFront.Classes.Networking
{
    namespace Responses
    {
        public class Login
        {
            public int status = 0;
        }

        public class Logout
        {
            public int status = 0;
        }

        public class Signup
        {
            public int status = 0;
            public int value = 0;
        }

        public class Error
        {
            public string message;
        }

        public class GetRooms
        {
            public List<string> roomNames;
        }

        public class GetPlayersInRoom
        {
            public List<string> players;
            public string roomName;
        }

        public class Score
        {
            public string username;
            public float score;
        }

        public class GetTop
        {
            public List<Score> tops;
        }

        public class GetUserStats
        {
            public string userName;
            public int numOfGame = 0;
            public int numWrongAns = 0;
            public int numRightAns = 0;
            public float avrageTimeToAns = 0;
        }

        public class JoinRoom
        {
            public int status = 0;
            public List<string> players;
            public Requests.CreateRoom roomData;
        }

        public class CloseRoom
        {
            public int status = 0;
        }

        public class CreateRoom
        {
            public int status = 0;
            public Requests.CreateRoom roomData;
        }

        public class ExitRoom
        {
            public int status = 0;
        }

        public class UserLeave
        {
            public string username;
        }

        public class UserJoin
        {
            public string username;
        }

        public class StartGamedata
        {
            public string gameName;
            public int questionNum = 0;
            public float timePerquestion = 0;
        }

        public class GetQuestion
        {
            public int status = 0;
            public string question;
            public List<string> answers;
        }

        public class updateRightAnswer
        {
            public string rightAnswer;
            public float currentScore = 0;
        }

        public class SubmitAnswer
        {
            public int status = 0;
            public string Answer;
        }

        public class PlayerResults
        {
            public string username;
            public float finalResult = 0;
            public int correctAnswerCount = 0;
            public int wrongAnswerCount = 0;
            public float averageAnswerTime = 0;
        }

        public class GetGameResults
        {
            public int status = 0;
            public List<PlayerResults> results;
        }

        public class LeaveGame
        {
            public int status = 0;
        }
    }
}