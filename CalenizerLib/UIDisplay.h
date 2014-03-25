//UIDisplay.h
// v1.3
#pragma once
#ifndef UIDISPLAY_H
#define UIDISPLAY_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "taskStorage.h"
#include "task.h"

class UIDisplay {

private:

	static const std::string MSG_WELCOME;
	static const std::string MSG_USERPROMPT;

	static const int MAX_SIZE = 255;
	char buffer[MAX_SIZE];

	static const std::string _programName;

public:
	UIDisplay();
	
	void displayTasks(std::vector<Task*>);

	std::string welcomeMsg();
	std::string promptMsg();

	void displayToUser(std::string output);
};

#endif