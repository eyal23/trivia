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
        private Communicator communicator;

        public MainWindow()
        {
            InitializeComponent();
            communicator = new Communicator();
        }

        public MainWindow(Communicator communicator)
        {
            InitializeComponent();
            this.communicator = communicator;
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
            m.Play();

            if (userName.Text == null || password.Password == null || (userName.Text == "user name" && password.Password == "password"))
            {
                //TODO: IMPLEMENT MESSAGE BOX   
            }
            else
            {
                Responses.Login loginResponse = this.communicator.submitRequest<Requests.Login, Responses.Login>(new Requests.Login(userName.Text, password.Password), (int)Defs.Codes.LOGIN_REQUEST);

                if (loginResponse.status == 0)
                {
                    //TODO: IMPLEMENT MESSAGE BOX   
                }

                mainManu main = new mainManu(this.communicator);
                main.Show();
                this.Close();
            }
        }

        private void signUp_Click(object sender, RoutedEventArgs e)
        {
            MediaPlayer m = new MediaPlayer();

            m.Open(new Uri("../../digi_plink.wav", UriKind.RelativeOrAbsolute));
            m.Play();

            if (userName.Text == null || password.Password == null || (userName.Text == "user name" && password.Password == "password")) //TODO: add email statement
            {
                //TODO: IMPLEMENT MESSAGE BOX 
            }

            Responses.Signup signupResponse = this.communicator.submitRequest<Requests.Signup, Responses.Signup>(new Requests.Signup(userName.Text, password.Password, "aaa"), (int)Defs.Codes.SIGN_UP_REQUEST); //TODO: chnage email

            if (signupResponse.status == 0)
            {
                //TODO: IMPLEMENT MESSAGE BOX 
            }
            else
            {
                MessageBox.Show($"send: {userName.Text} {password.Password} aaa@gmail.com"); //TODO: chnage email
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

        private void MainWindow_OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DragMove();
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

        private void Email_GotFocus(object sender, RoutedEventArgs e)
        {

        }
    }
}
