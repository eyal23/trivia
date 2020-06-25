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
        public mainManu()
        {
            InitializeComponent();
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

        private void maxButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.WindowState = WindowState.Maximized;
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

        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Hide();
            new CreateRoom().ShowDialog();
            ShowDialog();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}

