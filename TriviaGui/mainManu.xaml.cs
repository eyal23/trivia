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

            frame1.NavigationService.RemoveBackEntry();
            frame1.Navigate(new Uri("pages/StatisticsPgae.xaml", UriKind.RelativeOrAbsolute));

        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            string path = System.IO.Path.GetFullPath("digi_plink.wav");

            m.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            m.Play();

            frame1.Navigate(new Uri("pages/Page1.xaml", UriKind.RelativeOrAbsolute));
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            string path = System.IO.Path.GetFullPath("digi_plink.wav");

            m.Open(new Uri(path, UriKind.RelativeOrAbsolute));
            m.Play();

            frame1.Navigate(new Uri("pages/JoinRoomPage.xaml", UriKind.RelativeOrAbsolute));

        }
    }
}

