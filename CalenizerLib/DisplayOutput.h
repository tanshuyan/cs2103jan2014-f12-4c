//DisplayOutput.h
//v 1.0
// this is an object between the interaction of Logic and Parser

#ifndef DISPLAYOUTPUT_H
#define DISPLAYOUTPUT_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "Exception.h"
#include "Task.h"
#include "Message.h"

class DisplayOutput{
private:
	std::string intToString(int userInput);

	static const int MAX_SIZE = 255;
	char buffer[MAX_SIZE];

	std::string _feedback;
	std::vector<std::string> _displayList;
	// keeps a corresponding tracker on the status of task, if it is overdue, completed, incompleted etc
	std::vector<std::string> _displayListStatus;
	bool _displayStatus;
	static const std::string EMPTY; 
	Message _actionMsg;

public:
	DisplayOutput();
	void displayTasks(std::vector<Task*>);
	void setFeedBack(std::string);
	//void setFeedBack(std::vector<int>);
	void setDisplayStatus(bool);
	void setDisplayListStatus(std::vector<std::string>);
	std::vector<std::string> getDisplayListStatus();
	std::string getFeedBack();
	std::vector<std::string> getDisplay();
	bool getDisplayStatus();

	void displayToUser(std::string output);

	std::string editFeedback(std::string);
	std::string addFeedback(std::string);
	std::string deleteFeedback(std::string);
	std::string deleteMultipleFeedback(int);
	std::string undoSuccessFeedback();
	std::string undoFailureFeedback();
	std::string redoSuccessFeedback();
	std::string redoFailureFeedback();
	std::string searchSuccessFeedback(std::string);
	std::string searchFailureFeedback(std::string);
	std::string completeSuccessFeedback(std::string);
	std::string completeMultipleSuccessFeedback(int);
	std::string incompleteSuccessFeedback(std::string);
	std::string incompleteMultipleSuccessFeedback(int);

	std::string invalidFeedback();
	std::string invalidIndexFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();
	std::string invalidDateTimeFeedback();

	std::string displayCompleteFeedback();
	std::string displayIncompleteFeedback();
	std::string displayTodayFeedback();
	std::string displayAllFeedback();

	std::string loadFileFeedback();
	std::string unableToConvertFeedback();
};
#endif