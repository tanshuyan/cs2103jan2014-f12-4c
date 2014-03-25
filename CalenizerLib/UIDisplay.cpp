// Display.cpp
// v1.0
#include <iostream>
#include "UIDisplay.h"

UIDisplay::UIDisplay(){
}

const std::string UIDisplay:: _programName = "Calenzier";	
	
void UIDisplay::displayTasks(std::vector<Task*> displayList){
	std::stringstream output;
	int counter = 1;

	for(std::vector<Task*>::iterator iter = displayList.begin(); iter != displayList.end();){
		//Numbering
		output << counter << ". ";
		counter++;
		output << (*iter)->outputToString();
		iter++;
	}
	std::cout << output.str();
}

const std::string UIDisplay::MSG_WELCOME = "Welcome to %s. It is ready for use";
const std::string UIDisplay::MSG_USERPROMPT= "what would you like %s to do? Give your command: ";
const std::string UIDisplay::MSG_ADD_SUCCESS ="added to %s: \"%s\"";
const std::string UIDisplay::MSG_EDIT_SUCCESS ="%s updated";
const std::string UIDisplay::MSG_DELETE_SUCCESS ="deleted from %s: \"%s\"";
const std::string UIDisplay::MSG_UNDO_SUCCESS ="latest change to %s undone";
const std::string UIDisplay::MSG_REDO_SUCCESS ="latest undo to %s reverted";
const std::string UIDisplay::MSG_COMPLETE_SUCCESS ="%S marked as complete";

const std::string UIDisplay::MSG_INVALID_CMD = "invalid command";
const std::string UIDisplay::MSG_INVALID_LINENO = "invalid line";
const std::string UIDisplay::MSG_INVALID_TIME = "invalid time";
const std::string UIDisplay::MSG_INVALID_DATE = "invalid date";

const std::string UIDisplay::MSG_NOT_FOUND ="\"%s\" not found in %s";
const std::string UIDisplay::MSG_EMPTY_FILE = "%s is empty";
const std::string UIDisplay::DELIMITER =". ";

void UIDisplay::displayUI(std::string output) {
	std::cout << output;

	//no newline after "command: "
	if(output != MSG_USERPROMPT){
		std::cout << std::endl;
	}
}

std::string UIDisplay::welcomeMsg(){
	sprintf_s(buffer, MSG_WELCOME.c_str(), _programName.c_str());
	return buffer;
}

std::string UIDisplay::promptMsg(){
	sprintf_s(buffer, MSG_USERPROMPT.c_str(), _programName.c_str());
	return buffer;
}


std::string UIDisplay::emptyFeedback() {
	sprintf_s(buffer, MSG_EMPTY_FILE.c_str(), _programName.c_str());
	return buffer;
}

std::string UIDisplay::deleteFeedback(std::string removedContent) {
	sprintf_s(buffer, MSG_DELETE_SUCCESS.c_str(), _programName.c_str(), removedContent.c_str());
	return buffer;
}

std::string UIDisplay::addFeedback(std::string userInput) {
	sprintf_s(buffer, MSG_ADD_SUCCESS.c_str(), _programName.c_str(), userInput.c_str());
	return buffer;
}

std::string UIDisplay::invalidFeedback(){
	sprintf_s(buffer, MSG_INVALID_CMD.c_str());
	return buffer;
}

std::string UIDisplay::notFoundFeedback(std::string userInput){
	sprintf_s(buffer, MSG_NOT_FOUND.c_str(), userInput.c_str(), _programName.c_str());
	return buffer;
}

std::string UIDisplay::undoFeedback(){
	sprintf_s(buffer, MSG_UNDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string UIDisplay::redoFeedback(){
	sprintf_s(buffer, MSG_REDO_SUCCESS.c_str(), _programName.c_str());
	return buffer;
}

std::string UIDisplay::invalidTimeFeedback(){
	sprintf_s(buffer, MSG_INVALID_TIME.c_str());
	return buffer;
}

std::string UIDisplay::invalidDateFeedback(){
	sprintf_s(buffer, MSG_INVALID_DATE.c_str());
	return buffer;
}

std::string UIDisplay::completeFeedback(std::string userInput){
	sprintf_s(buffer,  MSG_COMPLETE_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}

std::string UIDisplay::editFeedback(std::string userInput){
	sprintf_s(buffer, MSG_EDIT_SUCCESS.c_str(), userInput.c_str());
	return buffer;
}
