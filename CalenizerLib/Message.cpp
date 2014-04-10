// Message.cpp

#include "Message.h"

const std::string Message::MSG_ADD_SUCCESS ="Added: \"%s\"\n";
const std::string Message::MSG_EDIT_SUCCESS ="Edited: \"%s\"\n";
const std::string Message::MSG_DELETE_SUCCESS ="Deleted: \"%s\"\n";
const std::string Message::MSG_DELETE_MULTIPLE_SUCCESS ="%s tasks deleted\n";
const std::string Message::MSG_UNDO_SUCCESS ="Latest change undone\n";
const std::string Message::MSG_UNDO_FAILURE ="Nothing to undo\n";
const std::string Message::MSG_REDO_SUCCESS ="Latest undo reverted\n";
const std::string Message::MSG_REDO_FAILURE ="Nothing to redo\n";
const std::string Message::MSG_SEARCH_SUCCESS ="Search term \"%s\" found\n";
const std::string Message::MSG_SEARCH_FAILURE ="Invalid search term: \"%s\"\n";
const std::string Message::MSG_COMPLETE_SUCCESS ="\"%s\" marked as complete\n";
const std::string Message::MSG_COMPLETE_MULTIPLE_SUCCESS ="%s tasks marked as complete\n";
const std::string Message::MSG_INCOMPLETE_SUCCESS ="\"%s\" marked as incomplete\n";
const std::string Message::MSG_INCOMPLETE_MULTIPLE_SUCCESS ="%s tasks marked as incomplete\n";

const std::string Message::MSG_DISPLAYCOM = "Completed tasks shown\n";
const std::string Message::MSG_DISPLAYINCOM = "Incompleted tasks shown\n";
const std::string Message::MSG_DISPLAYTODAY = "Today tasks shown\n";
const std::string Message::MSG_DISPLAYALL = "All tasks shown\n";

const std::string Message::MSG_INVALID_CMD = "Invalid command\n";
const std::string Message::MSG_INVALID_INDEX = "Invalid index\n";
const std::string Message::MSG_INVALID_TIME = "Invalid time\n";
const std::string Message::MSG_INVALID_DATE = "Invalid date\n";
const std::string Message::MSG_INVALID_DATETIME = "Invalid input order of start and end date\n";

const std::string Message::MSG_UNABLE_TO_CONVERT = "Task is unable to be converted\n";
const std::string Message::MSG_LOAD_FILE = "All tasks loaded\n";
const std::string Message::MSG_NOTHING_DISPLAY = "Invalid: nothing can be shown\n";

const std::string Message::CMD_ADD = "add";
const std::string Message::CMD_EDIT = "edit";
const std::string Message::CMD_DELETE = "delete";
const std::string Message::CMD_DISPLAY = "view";
const std::string Message::CMD_EXIT = "quit";
const std::string Message::CMD_SEARCH = "search";
const std::string Message::CMD_COMPLETE = "complete";
const std::string Message::CMD_INCOMPLETE = "incomplete";
const std::string Message::CMD_UNDO = "undo";
const std::string Message::CMD_REDO = "redo";
const std::string Message::CMD_INVALID = "invalid";

const std::string Message::DISPLAY_ALL = "all";
const std::string Message::DISPLAY_COMPLETE = "complete";
const std::string Message::DISPLAY_INCOMPLETE = "incomplete";
const std::string Message::DISPLAY_TODAY = "today";

const std::string Message::STATUS_OVERDUE = "Overdue"; 
const std::string Message::STATUS_ONGOING = "Ongoing"; 
const std::string Message::STATUS_COMPLETE = "Complete"; 
const std::string Message::STATUS_INCOMPLETE = "Incomplete";
