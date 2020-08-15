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
        public StatisticsPgae(Responses.GetStatistics getStatisticsResponse)
        {
            InitializeComponent();

            for (int i = 0; i < getStatisticsResponse.highScores.Count; i++)
            {
                ListBox.Items.Add($"{i + 1}.    {getStatisticsResponse.highScores[i]}");
            }

            ListBox1.Items.Add($"Correct answers: {getStatisticsResponse.numberOfCorrectAnswers}");
            ListBox1.Items.Add($"Total answers: {getStatisticsResponse.numberOfTotalAnswers}");
            ListBox1.Items.Add($"Games played: {getStatisticsResponse.numberOfPlayerGames}");
            ListBox1.Items.Add($"Average answer time: {getStatisticsResponse.averageAnswerTime}");
        }
    }
}
