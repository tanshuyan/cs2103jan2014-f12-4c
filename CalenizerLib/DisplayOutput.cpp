// DisplayOutput.cpp
// v1.0
// main interaction with GUI and logic

#include "DisplayOutput.h"
#include <iostream>

const std::string DisplayOutput:: _programName = "Calenizer";	

DisplayOutput::DisplayOutput() {
}

void DisplayOutput::displayTasks(std::vector<Task*> displayList){
	int counter = 1;
	_displayList.clear();
	for(std::vector<Task*>::iterator iter = displayList.begin(); iter != displayList.end();){
		//Numbering
		std::stringstream output;
		output << counter << ". ";
		counter++;
		output << (*iter)->outputToString();
		iter++;
		_displayList.push_back(output.str());
	}
}

void DisplayOutput::setFeedBack(std::string feedback) {
	_feedback = feedback;
}

void DisplayOutput::setFeedBack(std::vector<int> feedback) {
	std::stringstream output;
	for(std::vector<int>::iterator iter = feedback.begin(); iter!=feedback.end(); iter++) {
		output << "Index " << *iter;
		if(iter == feedback.end()) {
			output << " cannot be found\n";
		} else {
			output << " ";
		}
	}
	_feedback = output.str();
}

void DisplayOutput::setDisplayStatus(bool displayStatus) {
	_displayStatus = displayStatus;
}

void DisplayOutput::setDisplayListStatus(std::vector<std::string> displayListStatus) {
	_displayListStatus.clear();
	_displayListStatus = displayListStatus;
}

std::vector<std::string> DisplayOutput::getDisplayListStatus() {
	return _displayListStatus;
}

bool DisplayOutput::getDisplayStatus() {
	return _displayStatus;
}

std::string DisplayOutput::getFeedBack() {
	return _feedback;
}

std::vector<std::string> DisplayOutput::getDisplay() {
	return _displayList;
}


void DisplayOutput::displayToUser(std::string output) {
	std::cout << output;

	//no newline after "command: "
	if(output != MSG_USERPROMPT){
		std::cout << std::endl;
	}
}

std::string DisplayOutput::welcomeMsg(){
	sprintf_s(buffer, MSG_WELCOME.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::promptMsg(){
	sprintf_s(buffer, MSG_USERPROMPT.c_str(), _programName.c_str());
	return buffer;
}

const std::string DisplayOutput::MSG_ADD_SUCCESS ="added to %s: \"%s\"";
const std::string DisplayOutput::MSG_EDIT_SUCCESS ="%s updated";
const std::string DisplayOutput::MSG_DELETE_SUCCESS ="task deleted from %s";
const std::string DisplayOutput::MSG_UNDO_SUCCESS ="latest change to %s undone";
const std::string DisplayOutput::MSG_UNDO_FAILURE ="Nothing to undone in %s";
const std::string DisplayOutput::MSG_REDO_SUCCESS ="latest undo to %s reverted";
const std::string DisplayOutput::MSG_REDO_FAILURE ="Nothing to redo in %s";
const std::string DisplayOutput::MSG_SEARCH_SUCCESS ="search term %s found in %s";
const std::string DisplayOutput::MSG_SEARCH_FAILURE ="search term %s not found in %s";
const std::string DisplayOutput::MSG_COMPLETE_SUCCESS ="task marked as complete";
const std::string DisplayOutput::MSG_INCOMPLETE_SUCCESS ="task marked as incomplete";

const std::string DisplayOutput::MSG_DISPLAYCOM = "completed tasks in %s shown";
const std::string DisplayOutput::MSG_DISPLAYINCOM = "incompleted tasks in %s shown";
const std::string DisplayOutput::MSG_DISPLAYTODAY = "today tasks in %s shown";
const std::string DisplayOutput::MSG_DISPLAYALL = "all tasks in %s shown";

const std::string DisplayOutput::MSG_INVALID_CMD = "invalid command";
const std::string DisplayOutput::MSG_INVALID_INDEX = "invalid index";
const std::string DisplayOutput::MSG_INVALID_TIME = "invalid time";
const std::string DisplayOutput::MSG_INVALID_DATE = "invalid date";

const std::string DisplayOutput::MSG_NOT_FOUND ="\"%s\" not found in %s";
const std::string DisplayOutput::MSG_EMPTY_FILE = "%s is empty";

std::string DisplayOutput::emptyFeedback() {
	sprintf_s(buffer, MSG_EMPTY_FILE.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::deleteFeedback() {
	sprintf_s(buffer, MSG_DELETE_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::addFeedback(std::string userInput) {
	sprintf_s(buffer, MSG_ADD_SUCCESS.c_str(), _programName.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::invalidFeedback(){
	sprintf_s(buffer, MSG_INVALID_CMD.c_str());
	return buffer;
}

std::string DisplayOutput::notFoundFeedback(std::string userInput){
	sprintf_s(buffer, MSG_NOT_FOUND.c_str(), userInput.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::undoSuccessFeedback(){
	sprintf_s(buffer, MSG_UNDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::undoFailureFeedback(){
	sprintf_s(buffer, MSG_UNDO_FAILURE.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::redoSuccessFeedback(){
	sprintf_s(buffer, MSG_REDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::redoFailureFeedback(){
	sprintf_s(buffer, MSG_REDO_FAILURE.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::searchSuccessFeedback(std::string userInput){
	sprintf_s(buffer, MSG_SEARCH_SUCCESS.c_str(), userInput.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::searchFailureFeedback(std::string userInput){
	sprintf_s(buffer, MSG_SEARCH_FAILURE.c_str(), userInput.c_str(),_programName.c_str());
	return buffer;
}

std::string DisplayOutput::invalidIndexFeedback(){
	sprintf_s(buffer, MSG_INVALID_INDEX.c_str());
	return buffer;
}

std::string DisplayOutput::invalidTimeFeedback(){
	sprintf_s(buffer, MSG_INVALID_TIME.c_str());
	return buffer;
}

std::string DisplayOutput::invalidDateFeedback(){
	sprintf_s(buffer, MSG_INVALID_DATE.c_str());
	return buffer;
}

std::string DisplayOutput::completeSuccessFeedback(){
	sprintf_s(buffer,  MSG_COMPLETE_SUCCESS.c_str());
	return buffer;
}

std::string DisplayOutput::incompleteSuccessFeedback(){
	sprintf_s(buffer,  MSG_INCOMPLETE_SUCCESS.c_str());
	return buffer;
}

std::string DisplayOutput::editFeedback(std::string userInput){
	sprintf_s(buffer, MSG_EDIT_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::displayCompleteFeedback(){
	sprintf_s(buffer, MSG_DISPLAYCOM.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::displayIncompleteFeedback(){
	sprintf_s(buffer, MSG_DISPLAYINCOM.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::displayTodayFeedback(){
	sprintf_s(buffer, MSG_DISPLAYTODAY.c_str(), _programName.c_str());
	return buffer;
}

std::string DisplayOutput::displayAllFeedback(){
	sprintf_s(buffer, MSG_DISPLAYALL.c_str(), _programName.c_str());
	return buffer;
}

const std::string DisplayOutput::MSG_WELCOME = "Welcome to %s. At your service.";
const std::string DisplayOutput::MSG_USERPROMPT= "what would you like %s to do? Give your command: ";
