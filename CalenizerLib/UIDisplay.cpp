// Display.cpp
// v1.3
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

void UIDisplay::displayToUser(std::string output) {
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

const std::string UIDisplay::MSG_WELCOME = "Welcome to %s. At your service.";
const std::string UIDisplay::MSG_USERPROMPT= "what would you like %s to do? Give your command: ";
