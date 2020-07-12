using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaFront.Classes.Networking
{
    public static class Defs
    {
        public const int Port = 8826;
        public const string Ip = "89.138.136.118";

        public enum Codes : int
        {
            Error,
            Login,
            Signup,
            Logout,
            GetRooms,
            GetPlayersInRoom,
            JoinRoom,
            ExitRoom,
            CreateRoom,
            UserStats,
            Tops,
            CloseRoom,
            StartGame,
            GetRoomState,
            UserLeave,
            UserJoin,
            LeaveGame,
            GetQuestion,
            SubmitAnswer,
            PlayerResults,
            GetGameResults,
            updateRightAnswer,
            StartGamedata
        }
    }
}