#pragma once

#include <iostream>

using std::string;

class LoggedUser
{
private:
	string m_username;

public:
	string getUsername() const;
};