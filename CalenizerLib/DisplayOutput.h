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
	static const std::string MSG_INCOMPLETE_SUCCESS;

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
	std::string deleteMultipleFeedback();
	std::string undoSuccessFeedback();
	std::string undoFailureFeedback();
	std::string redoSuccessFeedback();
	std::string redoFailureFeedback();
	std::string searchSuccessFeedback(std::string);
	std::string searchFailureFeedback(std::string);
	std::string completeSuccessFeedback(std::string);
	std::string incompleteSuccessFeedback(std::string);

	std::string notFoundFeedback(std::string);
	std::string invalidFeedback();
	std::string invalidIndexFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();

	std::string displayCompleteFeedback();
	std::string displayIncompleteFeedback();
	std::string displayTodayFeedback();
	std::string displayAllFeedback();

};
#endif