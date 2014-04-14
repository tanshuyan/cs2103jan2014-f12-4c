//@author A0094659L

//DisplayOutput.h

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

	static const int MAX_SIZE = 10000;
	char buffer[MAX_SIZE];

	std::string _feedback;
	std::vector<std::string> _displayList;
	std::vector<std::string> _displayListStatus;
	bool _displayStatus;
	static const std::string EMPTY; 
	static const std::string DELIMITER; 
	Message _actionMsg;

public:
	DisplayOutput();
	void displayTasks(std::vector<Task*> displayList);
	void setFeedBack(std::string feedback);
	void setDisplayStatus(bool status);
	void setDisplayListStatus(std::vector<std::string> displayListStatus);
	std::vector<std::string> getDisplayListStatus();
	std::string getFeedBack();
	std::vector<std::string> getDisplay();
	bool getDisplayStatus();

	void displayToUser(std::string output);

	std::string editFeedback(std::string userInput);
	std::string addFeedback(std::string userInput);
	std::string deleteFeedback(std::string userInput);
	std::string deleteMultipleFeedback(int index);
	std::string undoSuccessFeedback();
	std::string undoFailureFeedback();
	std::string redoSuccessFeedback();
	std::string redoFailureFeedback();
	std::string searchSuccessFeedback(std::string userInput);
	std::string searchFailureFeedback(std::string userInput);
	std::string completeSuccessFeedback(std::string userInput);
	std::string completeMultipleSuccessFeedback(int index);
	std::string incompleteSuccessFeedback(std::string userInput);
	std::string incompleteMultipleSuccessFeedback(int index);

	std::string invalidFeedback();
	std::string invalidIndexFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();
	std::string invalidDateTimeFeedback();
	std::string invalidTaskFeedback();

	std::string displayCompleteFeedback();
	std::string displayIncompleteFeedback();
	std::string displayTodayFeedback();
	std::string displayAllFeedback();

	std::string loadFileFeedback();
	std::string unableToConvertFeedback();
};
#endif