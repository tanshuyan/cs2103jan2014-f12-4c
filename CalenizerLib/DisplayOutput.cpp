// DisplayOutput.cpp
// v1.0
// main interaction with GUI and logic

#include "DisplayOutput.h"
#include <iostream>

const std::string DisplayOutput:: _programName = "Calenzier";	

DisplayOutput::DisplayOutput() {
}

void DisplayOutput::displayTasks(std::vector<Task*> displayList){
	int counter = 1;

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

const std::string DisplayOutput::MSG_WELCOME = "Welcome to %s. At your service.";
const std::string DisplayOutput::MSG_USERPROMPT= "what would you like %s to do? Give your command: ";
