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
using TriviaFront.Classes;
using TriviaFront.Classes.Networking;
using Requests = TriviaFront.Classes.Networking.Requests;
using Responses = TriviaFront.Classes.Networking.Responses;


namespace TriviaGui
{
    /// <summary>
    /// Interaction logic for Page1.xaml 
    /// </summary>
    public partial class Page1 : Page
    {
        public Page1()
        {
            InitializeComponent();
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
            /*
            var roomData = new Requests.CreateRoom();
            Communicator communicator = new Communicator;

            roomData.roomName = this.RoomName.Text;
            try
            {
                roomData.answerTimeout = Int32.Parse(this.QustienTime.Text);
                roomData.maxUsers = Int32.Parse(this.NumberOfPlayers.Text);
            }
            catch (FormatException)
            {
                MessageBox.Show($"Pl", "Error", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return;
            }

            communicator.TryToSend(roomData);
            */
        }
    }
}
