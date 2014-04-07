//DisplayOutput.h
//v 1.0
// this is an object between the interaction of Logic and Parser

#ifndef DISPLAYOUTPUT_H
#define DISPLAYOUTPUT_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "Task.h"

class DisplayOutput{
private:
	std::string intToString(int userInput);
	static const std::string MSG_WELCOME;
	static const std::string MSG_USERPROMPT;

	static const int MAX_SIZE = 255;
	char buffer[MAX_SIZE];

	static const std::string _programName;

	std::string _feedback;
	std::vector<std::string> _displayList;
	// keeps a corresponding tracker on the status of task, if it is overdue, completed, incompleted etc
	std::vector<std::string> _displayListStatus;
	bool _displayStatus;

	static const std::string MSG_ADD_SUCCESS;
	static const std::string MSG_EDIT_SUCCESS;
	static const std::string MSG_DELETE_SUCCESS;
	static const std::string MSG_DELETE_MULTIPLE_SUCCESS;

	static const std::string MSG_UNDO_SUCCESS;
	static const std::string MSG_UNDO_FAILURE;

	static const std::string MSG_REDO_SUCCESS;
	static const std::string MSG_REDO_FAILURE;

	static const std::string MSG_SEARCH_SUCCESS;
	static const std::string MSG_SEARCH_FAILURE;

	static const std::string MSG_COMPLETE_SUCCESS;
	static const std::string MSG_COMPLETE_MULTIPLE_SUCCESS;
	static const std::string MSG_INCOMPLETE_SUCCESS;
	static const std::string MSG_INCOMPLETE_MULTIPLE_SUCCESS;

	static const std::string MSG_DISPLAYCOM;
	static const std::string MSG_DISPLAYINCOM;
	static const std::string MSG_DISPLAYTODAY;
	static const std::string MSG_DISPLAYALL;

	static const std::string MSG_INVALID_CMD;
	static const std::string MSG_INVALID_INDEX;
	static const std::string MSG_INVALID_TIME;
	static const std::string MSG_INVALID_DATE;

	static const std::string MSG_NOT_FOUND;
	static const std::string MSG_EMPTY_FILE;

public:
	DisplayOutput();
	void displayTasks(std::vector<Task*>);
	void setFeedBack(std::string);
	void setFeedBack(std::vector<int>);
	void setDisplayStatus(bool);
	void setDisplayListStatus(std::vector<std::string>);
	std::vector<std::string> getDisplayListStatus();
	std::string getFeedBack();
	std::vector<std::string> getDisplay();
	bool getDisplayStatus();

	std::string welcomeMsg();
	std::string promptMsg();
	void displayToUser(std::string output);

	std::string emptyFeedback();
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

	std::string notFoundFeedback(std::string);
	std::string invalidFeedback();
	std::string invalidIndexFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();

	std::string displayCompleteFeedback();
	std::string displayIncompleteFeedback();
	std::string displayTodayFeedback();
	std::string displayAllFeedback();

	static const std::string CMD_ADD;
	static const std::string CMD_EDIT;
	static const std::string CMD_DELETE;
	static const std::string CMD_DISPLAY;
	static const std::string CMD_EXIT;
	static const std::string CMD_SEARCH;
	static const std::string CMD_COMPLETE;
	static const std::string CMD_INCOMPLETE;
	static const std::string CMD_UNDO;
	static const std::string CMD_REDO;
	static const std::string CMD_INVALID;

	static const std::string DISPLAY_ALL;
	static const std::string DISPLAY_COMPLETE;
	static const std::string DISPLAY_INCOMPLETE;
	static const std::string DISPLAY_TODAY;

	static const std::string STATUS_OVERDUE;
	static const std::string STATUS_ONGOING;
	static const std::string STATUS_COMPLETE;
	static const std::string STATUS_INCOMPLETE;

};
#endif