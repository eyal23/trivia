#pragma once

#include <iostream>
#include <vector>
#include <map>

#define USERS_USERNAME "USERNAME"
#define USERS_PASSWORD "PASSWORD"
#define USERS_EMAIL "EMAIL"
#define QUESTIONS_QUESTION "QUESTION"
#define QUESTIONS_CORRECT_ANSWER "CORRECT_ANSWER"
#define QUESTIONS_INCORRECT_ANSWER_1 "INCORRECT_ANSWER1"
#define QUESTIONS_INCORRECT_ANSWER_2 "INCORRECT_ANSWER2"
#define QUESTIONS_INCORRECT_ANSWER_3 "INCORRECT_ANSWER3"

using std::string;
using std::map;
using std::vector;


enum MessageCode
{
	SIGN_UP_REQUEST,
	LOGIN_REQUEST,
	ERROR_RESPONSE,
	SIGN_UP_RESPONSE,
	LOGIN_RESPONSE
};

vector<map<const string, const string>> questions = {
		{
			{ QUESTIONS_QUESTION, "\"What did the Spanish autonomous community of Catalonia ban in 2010, that took effect in 2012?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Bullfighting\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Fiestas\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Flamenco\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Mariachi\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What is the romanized Russian word for 'winter'?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Zima\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Leto\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Vesna\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Osen\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"The term 'scientist' was coined in which year?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"1833\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"1933\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"1942\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"1796\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"The new One World Trade Center in Manhattan, New York City was designed by which architect?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"David Childs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Bjarke Ingels\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Michael Arad\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Fumihiko Maki\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Amsterdam Centraal station is twinned with what station?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"London Liverpool Street\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Frankfurt (Main) Hauptbahnhof\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Paris Gare du Nord\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Brussels Midi\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Where does water from Poland Spring water bottles come from?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Maine, United States\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Hesse, Germany\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Masovia, Poland\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Bavaria, Poland\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"In a 1994 CBS interview, Microsoft co-founder Bill Gates performed what unusual trick on camera?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Jumping over an office chair\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Jumping backwards over a desk\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Standing on his head\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Typing on a keyboard during a handstand\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What is real haggis made of?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Sheep's Heart, Liver and Lungs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Sheep's Heart, Kidneys and Lungs\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Sheep's Liver, Kidneys and Eyes\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Whole Sheep\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"Which of these words means 'idle spectator'?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Gongoozler\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Gossypiboma\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Jentacular\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Meupareunia\"" }
		},
		{
			{ QUESTIONS_QUESTION, "\"What was the name given to Japanese military dictators who ruled the country through the 12th and 19th Century?\"" },
			{ QUESTIONS_CORRECT_ANSWER, "\"Shogun\"" },
			{ QUESTIONS_INCORRECT_ANSWER_1, "\"Ninja\"" },
			{ QUESTIONS_INCORRECT_ANSWER_2, "\"Samurai\"" },
			{ QUESTIONS_INCORRECT_ANSWER_3, "\"Shinobi\"" }
		}
};