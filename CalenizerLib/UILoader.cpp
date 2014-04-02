//DELETE THIS FILE . KIV

//UI.cpp
// v1.0


#include <iostream>
#include <string>
#include "UILoader.h"
#include "task.h"
#include "Parser.h"

UILoader::UILoader(){

}

void UILoader::ProgramLaunch() {
	std::cout << CMD_USERPROMPT;
	std::string exitStatus;
	while(exitStatus!= CMD_EXIT) {
	std::string commandLine;
	std::getline(std::cin, commandLine);
	exitStatus = _parser.executeUserInput(commandLine);
	}
	exit(0);
}

const std::string UILoader::CMD_EXIT = "exit";
const std::string UILoader::CMD_USERPROMPT= "command: ";