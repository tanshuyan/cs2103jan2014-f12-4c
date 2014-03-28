// Display.cpp
// v1.3
#include <iostream>
#include "ParserFeedback.h"

const std::string ParserFeedback:: _programName = "Calenzier";	

const std::string ParserFeedback::MSG_ADD_SUCCESS ="added to %s: \"%s\"";
const std::string ParserFeedback::MSG_EDIT_SUCCESS ="%s updated";
const std::string ParserFeedback::MSG_DELETE_SUCCESS ="deleted from %s: \"%s\"";
const std::string ParserFeedback::MSG_UNDO_SUCCESS ="latest change to %s undone";
const std::string ParserFeedback::MSG_UNDO_FAILURE ="Nothing to undone in %s";
const std::string ParserFeedback::MSG_REDO_SUCCESS ="latest undo to %s reverted";
const std::string ParserFeedback::MSG_REDO_FAILURE ="Nothing to redo in %s";
const std::string ParserFeedback::MSG_SEARCH_SUCCESS ="search term %s found in %s";
const std::string ParserFeedback::MSG_SEARCH_FAILURE ="search term %s not found in %s";
const std::string ParserFeedback::MSG_COMPLETE_SUCCESS ="%S marked as complete";

const std::string ParserFeedback::MSG_DISPLAYCOM = "completed tasks in %s shown";
const std::string ParserFeedback::MSG_DISPLAYINCOM = "incompleted tasks in %s shown";
const std::string ParserFeedback::MSG_DISPLAYTODAY = "today tasks in %s shown";
const std::string ParserFeedback::MSG_DISPLAYALL = "all tasks in %s shown";

const std::string ParserFeedback::MSG_INVALID_CMD = "invalid command";
const std::string ParserFeedback::MSG_INVALID_INDEX = "invalid line";
const std::string ParserFeedback::MSG_INVALID_TIME = "invalid time";
const std::string ParserFeedback::MSG_INVALID_DATE = "invalid date";

const std::string ParserFeedback::MSG_NOT_FOUND ="\"%s\" not found in %s";
const std::string ParserFeedback::MSG_EMPTY_FILE = "%s is empty";
const std::string ParserFeedback::DELIMITER =". ";

std::string ParserFeedback::emptyFeedback() {
	sprintf_s(buffer, MSG_EMPTY_FILE.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::deleteFeedback(std::string removedContent) {
	sprintf_s(buffer, MSG_DELETE_SUCCESS.c_str(), _programName.c_str(), removedContent.c_str());
	return buffer;
}

std::string ParserFeedback::addFeedback(std::string userInput) {
	sprintf_s(buffer, MSG_ADD_SUCCESS.c_str(), _programName.c_str(), userInput.c_str());
	return buffer;
}

std::string ParserFeedback::invalidFeedback(){
	sprintf_s(buffer, MSG_INVALID_CMD.c_str());
	return buffer;
}

std::string ParserFeedback::notFoundFeedback(std::string userInput){
	sprintf_s(buffer, MSG_NOT_FOUND.c_str(), userInput.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::undoSuccessFeedback(){
	sprintf_s(buffer, MSG_UNDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::undoFailureFeedback(){
	sprintf_s(buffer, MSG_UNDO_FAILURE.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::redoSuccessFeedback(){
	sprintf_s(buffer, MSG_REDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::redoFailureFeedback(){
	sprintf_s(buffer, MSG_REDO_FAILURE.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::searchSuccessFeedback(std::string userInput){
	sprintf_s(buffer, MSG_SEARCH_SUCCESS.c_str(), userInput.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::searchFailureFeedback(std::string userInput){
	sprintf_s(buffer, MSG_SEARCH_FAILURE.c_str(), userInput.c_str(),_programName.c_str());
	return buffer;
}

std::string ParserFeedback::invalidTimeFeedback(){
	sprintf_s(buffer, MSG_INVALID_TIME.c_str());
	return buffer;
}

std::string ParserFeedback::invalidDateFeedback(){
	sprintf_s(buffer, MSG_INVALID_DATE.c_str());
	return buffer;
}

std::string ParserFeedback::completeFeedback(std::string userInput){
	sprintf_s(buffer,  MSG_COMPLETE_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string ParserFeedback::editFeedback(std::string userInput){
	sprintf_s(buffer, MSG_EDIT_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string ParserFeedback::displayCompleteFeedback(){
	sprintf_s(buffer, MSG_DISPLAYCOM.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::displayIncompleteFeedback(){
	sprintf_s(buffer, MSG_DISPLAYINCOM.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::displayTodayFeedback(){
	sprintf_s(buffer, MSG_DISPLAYTODAY.c_str(), _programName.c_str());
	return buffer;
}

std::string ParserFeedback::displayAllFeedback(){
	sprintf_s(buffer, MSG_DISPLAYALL.c_str(), _programName.c_str());
	return buffer;
}

