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
    /// Interaction logic for StatisticsPgae.xaml
    /// </summary>
    public partial class StatisticsPgae : Page
    {
        private Communicator communicator;

        public StatisticsPgae(Communicator communicator)
        {
            InitializeComponent();
            this.communicator = communicator;
        }

        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            HighScore Hs = new HighScore(this.communicator);

            if(Hs.IsInitialized)
            {
            }
            Hs.Show();
        }

        private void personalStatistics_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
