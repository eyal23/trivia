using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TriviaGui
{
    /// <summary>
    /// Interaction logic for mainManu.xaml
    /// </summary>
    public partial class mainManu : Window
    {
        private MediaPlayer player;
        private Communicator communicator;

        public mainManu(Communicator communicator)
        {
            InitializeComponent();
            PlayMusic();
            this.communicator = communicator;
        }

        private void MinimizeButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.WindowState = WindowState.Minimized;
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Close();
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void StatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            string path = System.IO.Path.GetFullPath("digi_plink.wav");

            m.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            m.Play();

            pages.StatisticsPgae statPage = new pages.StatisticsPgae(this.communicator);
            frame1.NavigationService.Navigate(statPage);
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            string path = System.IO.Path.GetFullPath("digi_plink.wav");

            m.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            m.Play();

            pages.Page1 createRoomPage = new pages.Page1(this.communicator, this);
            frame1.NavigationService.Navigate(createRoomPage);
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            string path = System.IO.Path.GetFullPath("digi_plink.wav");

            m.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            m.Play();

            pages.JoinRoomPage joinRoomPage = new pages.JoinRoomPage(this.communicator);
            frame1.NavigationService.Navigate(joinRoomPage);
        }

        private void PlayMusic()
        {
            player = new MediaPlayer();
            string path = System.IO.Path.GetFullPath("Immanuel.mp3");
            player.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            player.Play();
        }

        private void mainManu_OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
                DragMove();
        }

        private void LogOutButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}

