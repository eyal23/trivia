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

        public JoinRoomPage(Communicator communicator)
        {
            InitializeComponent();
            this.communicator = communicator;
        }

        public void RoomName_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox name = (TextBox)sender;
            name.Text = string.Empty;
            name.GotFocus -= RoomName_GotFocus;
        }
    }
}
