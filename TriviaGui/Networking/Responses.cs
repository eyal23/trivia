using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGui
{
    namespace Responses
    {
        public struct Signup
        {
            public Signup(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct Login
        {
            public Login(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct Logout
        {
            public Logout(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct CreateRoom
        {
            public CreateRoom(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct GetPlayersInRoom
        {
            public GetPlayersInRoom(int status, List<string> players)
            {
                this.status = status;
                this.players = players;
            }

            public int status;
            public List<string> players;
        }

        public struct Room
        {
            public Room(int id, string name)
            {
                this.id = id;
                this.name = name;
            }

            public int id;
            public string name;
        }

        public struct GetRooms
        {
            public GetRooms(int status, List<Room> rooms)
            {
                this.status = status;
                this.rooms = rooms;
            }

            public int status;
            public List<Room> rooms;
        }

        public struct JoinRoom
        {
            public JoinRoom(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct GetStatistics
        {
            public GetStatistics(int status, float averageAnswerTime, int numberOfCorrectAnswers, int numberOfTotalAnswers, int numberOfPLayerGames, List<int> highScores)
            {
                this.status = status;
                this.averageAnswerTime = averageAnswerTime;
                this.numberOfCorrectAnswers = numberOfCorrectAnswers;
                this.numberOfTotalAnswers = numberOfTotalAnswers;
                this.numberOfPlayerGames = numberOfPLayerGames;
                this.highScores = highScores;
            }

            public int status;
            public float averageAnswerTime;
            public int numberOfCorrectAnswers;
            public int numberOfTotalAnswers;
            public int numberOfPlayerGames;
            public List<int> highScores;
        }

        public struct CloseRoom
        {
            public CloseRoom(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct StartGame
        {
            public StartGame(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct GetRoomState
        {
            public GetRoomState(int status, bool hasGameBegun, List<string> players, int questionCount, int answerTimeout)
            {
                this.status = status;
                this.hasGameBegun = hasGameBegun;
                this.players = players;
                this.questionCount = questionCount;
                this.answerTimeout = answerTimeout;
            }

            public int status;
            public bool hasGameBegun;
            public List<string> players;
            public int questionCount;
            public int answerTimeout;
        }

        public struct LeaveRoom
        {
            public LeaveRoom(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct LeaveGame
        {
            public LeaveGame(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct GetQuestion
        {
            public GetQuestion(int status, string question, Dictionary<int, string> answers)
            {
                this.status = status;
                this.question = question;
                this.answers = answers;
            }

            public int status;
            public string question;
            public Dictionary<int, string> answers;
        }

        public struct SubmitAnswer
        {
            public SubmitAnswer(int status)
            {
                this.status = status;
            }

            public int status;
        }

        public struct PlayerResult
        {
            public PlayerResult(string username, int correctAnswersCount, int wrongAnswersCount, float averageAnswerTime)
            {
                this.username = username;
                this.correctAnswersCount = correctAnswersCount;
                this.wrongAnswersCount = wrongAnswersCount;
                this.averageAnswerTime = averageAnswerTime;
            }

            public string username;
            public int correctAnswersCount;
            public int wrongAnswersCount;
            public float averageAnswerTime;
        }

        public struct GetGameResults
        {
            public GetGameResults(int status, List<PlayerResult> results)
            {
                this.status = status;
                this.results = results;
            }

            public int status;
            public List<PlayerResult> results;
        }

        public struct Error
        {
            public Error(string message)
            {
                this.message = message;
            }

            public string message;
        }
    }
}