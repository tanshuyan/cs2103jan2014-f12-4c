// Message.cpp

#include "Message.h"

const std::string Message::MSG_ADD_SUCCESS ="Added to %s: \"%s\"\n";
const std::string Message::MSG_EDIT_SUCCESS ="%s updated\n";
const std::string Message::MSG_DELETE_SUCCESS ="Deleted from %s: \"%s\"\n";
const std::string Message::MSG_DELETE_MULTIPLE_SUCCESS ="Deleted from %s: %s tasks\n";
const std::string Message::MSG_UNDO_SUCCESS ="Latest change to %s undone\n";
const std::string Message::MSG_UNDO_FAILURE ="Nothing to undo in %s\n";
const std::string Message::MSG_REDO_SUCCESS ="Latest undo to %s reverted\n";
const std::string Message::MSG_REDO_FAILURE ="Nothing to redo in %s\n";
const std::string Message::MSG_SEARCH_SUCCESS ="Search term \"%s\" found in %s\n";
const std::string Message::MSG_SEARCH_FAILURE ="Invalid search term: \"%s\" not found in %s\n";
const std::string Message::MSG_COMPLETE_SUCCESS ="\"%s\" marked as complete\n";
const std::string Message::MSG_COMPLETE_MULTIPLE_SUCCESS ="%s tasks marked as complete\n";
const std::string Message::MSG_INCOMPLETE_SUCCESS ="\"%s\" marked as incomplete\n";
const std::string Message::MSG_INCOMPLETE_MULTIPLE_SUCCESS ="%s tasks marked as incomplete\n";

const std::string Message::MSG_DISPLAYCOM = "Completed tasks in %s shown\n";
const std::string Message::MSG_DISPLAYINCOM = "Incompleted tasks in %s shown\n";
const std::string Message::MSG_DISPLAYTODAY = "Today tasks in %s shown\n";
const std::string Message::MSG_DISPLAYALL = "All tasks in %s shown\n";

const std::string Message::MSG_INVALID_CMD = "Invalid command\n";
const std::string Message::MSG_INVALID_INDEX = "Invalid index\n";
const std::string Message::MSG_INVALID_TIME = "Invalid time\n";
const std::string Message::MSG_INVALID_DATE = "Invalid date\n";
const std::string Message::MSG_INVALID_DATETIME = "Input order of start and end date is wrong\n";

const std::string Message::MSG_UNABLE_TO_CONVERT = "Task is unable to be converted\n";

const std::string Message::MSG_NOT_FOUND ="\"%s\" not found in %s\n";
const std::string Message::MSG_EMPTY_FILE = "%s is empty\n";
const std::string Message::MSG_LOAD_FILE = "All tasks in %s loaded\n";
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
