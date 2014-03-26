//DisplayOutput.h
//v 1.0
// this is an object between the interaction of Logic and Parser

#ifndef DISPLAYOUTPUT_H
#define DISPLAYOUTPUT_H

#include <string>
#include <vector>
#include <sstream>
#include "Task.h"

class DisplayOutput{

private:
	
	static const std::string MSG_WELCOME;
	static const std::string MSG_USERPROMPT;

	static const int MAX_SIZE = 255;
	char buffer[MAX_SIZE];

	static const std::string _programName;

	std::string _feedback;
	std::vector<std::string> _displayList;
	// keeps a corresponding tracker on the status of task, if it is overdue, completed, incompleted etc
	std::vector<int> _displayTaskStatus;
public:
	DisplayOutput();
	void displayTasks(std::vector<Task*>);
	void setFeedBack(std::string);
	void setFeedBack(std::vector<int>);
	std::string getFeedBack();
	std::vector<std::string> getDisplay();
	
	std::string welcomeMsg();
	std::string promptMsg();
	void displayToUser(std::string output);

};
#endif