using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaGui
{
    namespace Requests
    {
        public struct Signup
        {
            public Signup(string username, string password, string email)
            {
                this.username = username;
                this.password = password;
                this.email = email;
            }

            public string username;
            public string password;
            public string email;
        }

        public struct Login
        {
            public Login(string username, string password)
            {
                this.username = username;
                this.password = password;
            }

            public string username;
            public string password;
        }

        public struct CreateRoom
        {
            public CreateRoom(string roomName, int maxUsers, int questionCount, int answerTimeout)
            {
                this.roomName = roomName;
                this.maxUsers = maxUsers;
                this.questionCount = questionCount;
                this.answerTimeout = answerTimeout;
            }

            public string roomName;
            public int maxUsers;
            public int questionCount;
            public int answerTimeout;
        }

        public struct GetPlayersInRoom
        {
            public GetPlayersInRoom(int roomId)
            {
                this.roomId = roomId;
            }

            public int roomId;
        }

        public struct JoinRoom
        {
            public JoinRoom(int roomId)
            {
                this.roomId = roomId;
            }

            public int roomId;
        }

        public struct SubmitAnswer
        {
            public SubmitAnswer(int answerId, float answerTime)
            {
                this.answerId = answerId;
                this.answerTime = answerTime;
            }

            public int answerId;
            public float answerTime;
        }
    }
}