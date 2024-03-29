//@author A0094659L

// DisplayOutput.cpp

#include "DisplayOutput.h"

const std::string DisplayOutput::EMPTY = "";
const std::string DisplayOutput::DELIMITER = ". ";

DisplayOutput::DisplayOutput() {
} 

void DisplayOutput::displayTasks(std::vector<Task*> displayList){
	int counter = 1;

	//ensure it is cleared before displaying new list
	if(!_displayList.empty()){
		_displayList.clear();
	}

	for(std::vector<Task*>::iterator iter = displayList.begin(); iter != displayList.end();){
		//Numbering
		std::stringstream output;
		output << counter << DELIMITER;
		counter++;

		//assertion to ensure there is no empty task displayed
		assert(*iter != NULL);

		output << (*iter)->outputToString();
		iter++;
		_displayList.push_back(output.str());
	}
}

void DisplayOutput::setFeedBack(std::string feedback) {
	assert(feedback != EMPTY);
	_feedback = feedback;
}

void DisplayOutput::setDisplayStatus(bool displayStatus) {
	_displayStatus = displayStatus;
}

void DisplayOutput::setDisplayListStatus(std::vector<std::string> displayListStatus) {
	//to ensure it is clear
	if(!_displayListStatus.empty()){
		_displayListStatus.clear();
	}
	_displayListStatus = displayListStatus;
}

std::vector<std::string> DisplayOutput::getDisplayListStatus() {
	return _displayListStatus;
}

std::string DisplayOutput::getFeedBack() {
	return _feedback;
}

std::vector<std::string> DisplayOutput::getDisplay() {
	return _displayList;
}

bool DisplayOutput::getDisplayStatus() {
	return _displayStatus;
}

void DisplayOutput::displayToUser(std::string output) {
	assert(output != EMPTY);

	try {
		std::cout << output;
	}
	catch (EmptyMessageException &e){
		std::cout <<  _actionMsg.MSG_NOTHING_DISPLAY;
	}
}

std::string DisplayOutput::deleteFeedback(std::string userInput) {
	sprintf_s(buffer, Message::MSG_DELETE_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::deleteMultipleFeedback(int userInput) {
	std::string numofTasks= intToString(userInput);
	sprintf_s(buffer, Message::MSG_DELETE_MULTIPLE_SUCCESS.c_str(), numofTasks.c_str());
	return buffer;
}

std::string DisplayOutput::intToString(int userInput){
	std::stringstream ss;
	ss << userInput;
	return ss.str();
}

std::string DisplayOutput::addFeedback(std::string userInput) {
	sprintf_s(buffer, Message::MSG_ADD_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::invalidFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_CMD.c_str());
	return buffer;
}

std::string DisplayOutput::undoSuccessFeedback(){
	sprintf_s(buffer, Message::MSG_UNDO_SUCCESS.c_str());
	return buffer;
}

std::string DisplayOutput::undoFailureFeedback(){
	sprintf_s(buffer, Message::MSG_UNDO_FAILURE.c_str());
	return buffer;
}

std::string DisplayOutput::redoSuccessFeedback(){
	sprintf_s(buffer, Message::MSG_REDO_SUCCESS.c_str());
	return buffer;
}

std::string DisplayOutput::redoFailureFeedback(){
	sprintf_s(buffer, Message::MSG_REDO_FAILURE.c_str());
	return buffer;
}

std::string DisplayOutput::searchSuccessFeedback(std::string userInput){
	sprintf_s(buffer, Message::MSG_SEARCH_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::searchFailureFeedback(std::string userInput){
	sprintf_s(buffer, Message::MSG_SEARCH_FAILURE.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::invalidIndexFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_INDEX.c_str());
	return buffer;
}

std::string DisplayOutput::invalidTimeFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_TIME.c_str());
	return buffer;
}

std::string DisplayOutput::invalidDateFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_DATE.c_str());
	return buffer;
}

std::string DisplayOutput::invalidDateTimeFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_DATETIME.c_str());
	return buffer;
}

std::string DisplayOutput::invalidTaskFeedback(){
	sprintf_s(buffer, Message::MSG_INVALID_TASK.c_str());
	return buffer;
}

std::string DisplayOutput::completeSuccessFeedback(std::string userInput){
	sprintf_s(buffer, Message::MSG_COMPLETE_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::completeMultipleSuccessFeedback(int userInput) {
	std::string numofTasks= intToString(userInput);
	sprintf_s(buffer, Message::MSG_COMPLETE_MULTIPLE_SUCCESS.c_str(), numofTasks.c_str());
	return buffer;
}

std::string DisplayOutput::incompleteSuccessFeedback(std::string userInput){
	sprintf_s(buffer, Message::MSG_INCOMPLETE_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::incompleteMultipleSuccessFeedback(int userInput) {
	std::string numofTasks= intToString(userInput);
	sprintf_s(buffer, Message::MSG_INCOMPLETE_MULTIPLE_SUCCESS.c_str(), numofTasks.c_str());
	return buffer;
}

std::string DisplayOutput::editFeedback(std::string userInput){
	sprintf_s(buffer, Message::MSG_EDIT_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string DisplayOutput::displayCompleteFeedback(){
	sprintf_s(buffer, Message::MSG_DISPLAYCOM.c_str());
	return buffer;
}

std::string DisplayOutput::displayIncompleteFeedback(){
	sprintf_s(buffer, Message::MSG_DISPLAYINCOM.c_str());
	return buffer;
}

std::string DisplayOutput::displayTodayFeedback(){
	sprintf_s(buffer, Message::MSG_DISPLAYTODAY.c_str());
	return buffer;
}

std::string DisplayOutput::displayAllFeedback(){
	sprintf_s(buffer, Message::MSG_DISPLAYALL.c_str());
	return buffer;
}

std::string DisplayOutput::loadFileFeedback(){
	sprintf_s(buffer, Message::MSG_LOAD_FILE.c_str());
	return buffer;
}

std::string DisplayOutput::unableToConvertFeedback(){
	sprintf_s(buffer, Message::MSG_UNABLE_TO_CONVERT.c_str());
	return buffer;
}