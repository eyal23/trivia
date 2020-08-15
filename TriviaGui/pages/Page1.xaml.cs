using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TriviaGui.Responses;

namespace TriviaGui.pages
{
    /// <summary>
    /// Interaction logic for Page1.xaml 
    /// </summary>
    public partial class Page1 : Page
    {
        private Communicator communicator;
        private mainManu mainMenuWindow;

        public Page1(Communicator communicator, mainManu mainMenuWindow)
        {
            InitializeComponent();
            this.communicator = communicator;
            this.mainMenuWindow = mainMenuWindow;
        }

        private void NumberOfPlayers_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox NumOfPlayers = (TextBox)sender;
            NumOfPlayers.Text = string.Empty;
            NumOfPlayers.GotFocus -= NumberOfPlayers_GotFocus;
        }

        private void QustienTime_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox Qtime = (TextBox)sender;
            Qtime.Text = string.Empty;
            Qtime.GotFocus -= QustienTime_GotFocus;
        }

        public void RoomName_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox name = (TextBox)sender;
            name.Text = string.Empty;
            name.GotFocus -= RoomName_GotFocus;
        }


        private void CreateRoomClick(object sender, RoutedEventArgs e)
        {
            if (RoomName.Text == string.Empty || QuestionTime.Text == string.Empty || MaxOfPlayers.Text == string.Empty || QuestionCount.Text == string.Empty || RoomName.Text == "room name" || QuestionTime.Text == "time for each question" || MaxOfPlayers.Text == "number of players in room" || QuestionCount.Text == "question count")
            {
                //TODO: implement message box
            }
            else
            {
                Responses.CreateRoom createRoomResponse = this.communicator.submitRequest<Requests.CreateRoom, Responses.CreateRoom>(new Requests.CreateRoom(RoomName.Text, int.Parse(MaxOfPlayers.Text), int.Parse(QuestionCount.Text), int.Parse(QuestionCount.Text)), (int)Defs.Codes.CREATE_ROOM_REQUEST);

                if (createRoomResponse.status == 0)
                {
                    //TODO: implement message box
                }
                else
                {
                    RoomWindow roomWindow = new RoomWindow(this.communicator);
                    roomWindow.Show();
                    this.mainMenuWindow.Close();
                }
            }
        }
    }
}
