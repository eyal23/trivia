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
using System.Windows.Shapes;

namespace TriviaGui
{
    /// <summary>
    /// Interaction logic for mainManu.xaml
    /// </summary>
    public partial class mainManu : Window
    {
        private MediaPlayer player;

        public mainManu()
        {
            InitializeComponent();
            PlayMusic();
        }

        private void PlayMusic()
        {

            player = new MediaPlayer();
            player.Open(new Uri("../../Immanuel.mp3", UriKind.RelativeOrAbsolute));
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

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
            m.Play();
            frame1.NavigationService.RemoveBackEntry();
            frame1.Navigate(new Uri("pages/StatisticsPgae.xaml", UriKind.RelativeOrAbsolute));

        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));

            m.Play();
            frame1.Navigate(new Uri("pages/Page1.xaml", UriKind.RelativeOrAbsolute));
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
            m.Play();
        }
    }
}

