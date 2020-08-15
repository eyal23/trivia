using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaGui.pages
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : Page
    {
        private Communicator communicator;
        private mainManu mainMenuWindow;

        public JoinRoomPage(Communicator communicator, Responses.GetRooms getRoomsResponses, mainManu mainMenuWindow)
        {
            InitializeComponent();
            this.communicator = communicator;
            this.mainMenuWindow = mainMenuWindow;

            for (int i = 0; i < getRoomsResponses.rooms.Count; i++)
            {
                ListBox.Items.Add($"{getRoomsResponses.rooms[i].name} ------> {getRoomsResponses.rooms[i].id}");
            }
        }

        public void RoomName_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox name = (TextBox)sender;
            name.Text = string.Empty;
            name.GotFocus -= RoomName_GotFocus;
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Responses.JoinRoom joinRoomResponse = this.communicator.submitRequest<Requests.JoinRoom, Responses.JoinRoom>(new Requests.JoinRoom(int.Parse(RoomName.Text)), (int)Defs.Codes.JOIN_ROOM_REQUEST);

            if (joinRoomResponse.status == 0)
            {
                MessageBox.Show($"Join room faild...");
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
