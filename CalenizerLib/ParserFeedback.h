//ParserFeedback.h
//v1.0
#pragma once
#ifndef PARSERFEEDBACK_H
#define PARSERFEEDBACK_H

#include <string>

class ParserFeedback {

private:
	static const std::string MSG_ADD_SUCCESS;

	static const std::string MSG_EDIT_SUCCESS;

	static const std::string MSG_DELETE_SUCCESS;

	static const std::string MSG_UNDO_SUCCESS;
	static const std::string MSG_UNDO_FAILURE;

	static const std::string MSG_REDO_SUCCESS;
	static const std::string MSG_REDO_FAILURE;

	static const std::string MSG_SEARCH_SUCCESS;
	static const std::string MSG_SEARCH_FAILURE;

	static const std::string MSG_COMPLETE_SUCCESS;

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
	static const std::string DELIMITER;
	static const int MAX_SIZE = 255;

	char buffer[MAX_SIZE];
	static const std::string _programName;

public:
	
	std::string emptyFeedback();
	std::string editFeedback(std::string);
	std::string addFeedback(std::string);
	std::string deleteFeedback(std::string);
	std::string undoSuccessFeedback();
	std::string undoFailureFeedback();
	std::string redoSuccessFeedback();
	std::string redoFailureFeedback();
	std::string searchSuccessFeedback(std::string);
	std::string searchFailureFeedback(std::string);
	std::string completeFeedback(std::string);

	std::string notFoundFeedback(std::string);
	std::string invalidFeedback();
	std::string invalidTimeFeedback();
	std::string invalidDateFeedback();

	std::string displayCompleteFeedback();
	std::string displayIncompleteFeedback();
	std::string displayTodayFeedback();
	std::string displayAllFeedback();
};

#endif