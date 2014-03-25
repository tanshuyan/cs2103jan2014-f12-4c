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

	static const std::string MSG_ADD_SUCCESS;

	static const std::string MSG_EDIT_SUCCESS;

	static const std::string MSG_DELETE_SUCCESS;

	static const std::string MSG_UNDO_SUCCESS;
	static const std::string MSG_UNDO_FAILURE;

	static const std::string MSG_REDO_SUCCESS;
	static const std::string MSG_REDO_FAILURE;

	static const std::string MSG_COMPLETE_SUCCESS;

	static const std::string MSG_INVALID_CMD;
	static const std::string MSG_INVALID_INDEX;
	static const std::string MSG_INVALID_TIME;
	static const std::string MSG_INVALID_DATE;

	static const std::string MSG_NOT_FOUND;
	static const std::string MSG_EMPTY_FILE;
	static const std::string DELIMITER;
	static const int MAX_SIZE = 255;

	char buffer[MAX_SIZE];
	static const std::string _programName;

public:
	UIDisplay();
	
	void displayTasks(std::vector<Task*>);

	std::string welcomeMsg();
	std::string promptMsg();

	std::string clearFeedback();
	std::string emptyFeedback();
	std::string editFeedback(std::string);
	std::string addFeedback(std::string);
	std::string deleteFeedback(std::string);
	std::string undoSuccessFeedback();
	std::string undoFailureFeedback();
	std::string redoSucessFeedback();
	std::string redoFailureFeedback();
	std::string notFoundFeedback(std::string);
	std::string invalidFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();
	std::string completeFeedback(std::string);

	void displayUI(std::string output);
};

#endif