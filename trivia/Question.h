#pragma once

#include <iostream>
#include <vector>

using std::string;
using std::vector;


class Question
{
private:
	string m_question;
	vector<string> m_answers;

public:
	Question(string question, vector<string> answers);

	string getQuestion() const;
	vector<string> getAnswers() const;
	string getCorrectAnswer() const;
};

