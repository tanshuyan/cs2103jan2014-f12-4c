// Message.h
// v 1.1

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
class Message {
public:
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
	static const std::string MSG_INVALID_DATETIME;

	static const std::string MSG_NOT_FOUND;
	static const std::string MSG_EMPTY_FILE;
	static const std::string MSG_LOAD_FILE;

	static const std::string MSG_UNABLE_TO_CONVERT;
	
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