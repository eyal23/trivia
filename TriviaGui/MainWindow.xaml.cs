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

        private void login_Click(object sender, RoutedEventArgs e)
        {
            isOnRegister = !isOnRegister;
            var temp = login.Content;
            login.Content = (string)signup.Content;
            signup.Content = temp;

            userName.Text = "";
            password.Password = "";

            mainManu main = new mainManu();
            main.Show();
            this.Close();
        }

        private void signUp_Click(object sender, RoutedEventArgs e)
        {
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
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= userName_GotFocus;
        }

        private void password_GotFocus(object sender, RoutedEventArgs e)
        {
            PasswordBox tb = (PasswordBox)sender;
            tb.Password = string.Empty;
            tb.GotFocus -= password_GotFocus;
        }
    }
}
