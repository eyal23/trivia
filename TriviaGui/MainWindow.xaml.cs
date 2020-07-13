using System;
using System.IO;
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
using Requests = TriviaFront.Classes.Networking.Requests;
using Responses = TriviaFront.Classes.Networking.Responses;
using Communicat = TriviaFront.Classes.Networking.Communicator;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Media;

namespace TriviaGui
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool isOnRegister = false;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void login_Click(Responses.Login req)
        {
            var logRe = 0;
            if (logRe != null && logRe.status == 1)
            {
                MediaPlayer m = new MediaPlayer();

                m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
                m.Play();

                mainManu main = new mainManu();
                main.Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Can't login", "Error", MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }

        }

        private void signUp_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
            m.Play();

            if (isOnRegister)
                MessageBox.Show($"send: {userName.Text} {password.Password}");


            else
                MessageBox.Show($"send: {userName.Text} {password.Password}");
        }

        private void MainWindow_OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if(e.LeftButton == MouseButtonState.Pressed)
                DragMove();
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

        private void userName_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox uname = (TextBox)sender;
            uname.Text = string.Empty;
            uname.GotFocus -= userName_GotFocus;
        }

        private void password_GotFocus(object sender, RoutedEventArgs e)
        {
            PasswordBox password = (PasswordBox)sender;
            password.Password = string.Empty;
            password.GotFocus -= password_GotFocus;
        }
    }
}
