//Parser.cpp
//IN PROGRESS
//v 1.4

#include "Parser.h"

const std::string Parser::MSG_INVALID = "Invalid command.\n";

//display msg
const std::string Parser::MSG_DISPLAYCOM = "displayed completed tasks";
const std::string Parser::MSG_DISPLAYINCOM = "displayed incompleted tasks";
const std::string Parser::MSG_DISPLAYTODAY = "displayed today tasks";

//search msg
const std::string Parser::MSG_SEARCH = "search completed";
//delete msg
const std::string Parser::MSG_DELETE = "all indicated tasks deleted";
//complete msg
const std::string Parser::MSG_COMPLETE = "all indicated tasks completed";
//undo msg
const std::string Parser::MSG_UNDO = "undo last action";
//redo msg
const std::string Parser::MSG_REDO = "redo last undo";

const std::string Parser::MSG_ADD = "task has been added";

const std::string Parser::MSG_EDIT = "task has been edited";

const std::string Parser::CMD_ADD = "add";
const std::string Parser::CMD_EDIT = "edit";
const std::string Parser::CMD_DELETE = "delete";
const std::string Parser::CMD_DISPLAY = "display";
const std::string Parser::CMD_EXIT = "exit";
const std::string Parser::CMD_SEARCH = "search";
const std::string Parser::CMD_COMPLETE = "complete";
const std::string Parser::CMD_UNDO = "undo";
const std::string Parser::CMD_REDO = "redo";
	
const std::string Parser::KEYWORD_COMPLETE = "complete";
const std::string Parser::KEYWORD_INCOMPLETE = "incomplete";
const std::string Parser::KEYWORD_TODAY = "today";

QRegExp Parser::RX_FROM_UNTIL("\\b(starting from|start|from|begin|beginning)\\b(.+)\\b(end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp Parser::RX_ON_AT_BY("\\b(on|at|by)\\b(.+)", Qt::CaseInsensitive);
//should I implement these? hmmm
QRegExp Parser::RX_FROM("\\b(starting from|start|from|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp Parser::RX_UNTIL("\\b(end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
//this exists only because Jim might be a massive dick
QRegExp Parser::RX_UNTIL_FROM("\\b(end|until|till|til|to)\\b(.+)\\b(starting from|start|from|begin|beginning)\\b(.+)", Qt::CaseInsensitive);


Parser::Parser() {
}

Parser::COMMAND_TYPE Parser::getCommand(std::string command) {
	if(command == CMD_ADD) {
		return COMMAND_TYPE::ADD;
	} else if ((command==CMD_DELETE)) {
		return COMMAND_TYPE::DELETE;
	} else if ((command== CMD_DISPLAY)) {
		return COMMAND_TYPE::DISPLAY;
	} else if ((command== CMD_EXIT)) {
		return COMMAND_TYPE::EXIT;
	} else if ((command== CMD_SEARCH)) {
		return COMMAND_TYPE::SEARCH;
	} else if ((command== CMD_EDIT)) {
		return COMMAND_TYPE::EDIT;
	} else if ((command== CMD_COMPLETE)) {
		return COMMAND_TYPE::COMPLETE;
	} else if ((command == CMD_UNDO)) {
		return COMMAND_TYPE::UNDO;
	} else if ((command == CMD_REDO)) {
		return COMMAND_TYPE::REDO;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}


std::string Parser::executeUserInput(std::string userInput) {
	userInput = toLower(userInput);
	std::istringstream input(userInput);
	std::string command;
	std::string dummy;
	input >> command; // the first word is always a command
	std::getline(input, dummy, ' '); // trim whitespace 
	std::string commandStatus;
	switch(getCommand(command)) {
	case ADD: {
		commandStatus = addCMD(input.str());		
		break;
	}
	case DELETE: {
		commandStatus = deleteCMD(input.str());
		break;
	}
	case EDIT: {
		commandStatus = editCMD(input.str());
		break;
	}	
	case SEARCH: {
		commandStatus = searchCMD(input.str());
		break;
	}
	case DISPLAY: {
		commandStatus = displayCMD(input.str());
		break;
	}
	case COMPLETE: {
		commandStatus = completeCMD(input.str());
		break;
	}
	case UNDO: {
		commandStatus = undoCMD();
		break;
	}
	case REDO: {
		commandStatus = redoCMD();
		break;
	}
	case EXIT: {
		commandStatus = CMD_EDIT;
		break;
	}
	case INVALID: {
		commandStatus = MSG_INVALID;
		break;
	}
	} // end switch block

	return commandStatus;
}

std::string Parser::undoCMD() {
	// Logic::undo();
	return MSG_UNDO;
}

std::string Parser::redoCMD() {
	// Logic::redo();
	return MSG_REDO;
}

std::string Parser::searchCMD(std::string userInput) {
	std::istringstream input(userInput);
	std::string searchTerm;
	input >> searchTerm;
	while(!input.eof()) {
	//	Logic::searchTasks(searchTerm);
		input >> searchTerm;
	}
	return MSG_SEARCH;
}

std::string Parser::displayCMD(std::string userInput) {
	std::istringstream input(userInput);
	std::string displayType;
	input >> displayType;
	if (displayType == KEYWORD_COMPLETE) {
		//Logic::getCompleteTasks();
		return MSG_DISPLAYCOM;
	} else if (displayType == KEYWORD_INCOMPLETE) {
		//Logic::getIncompleteTasks();
		return MSG_DISPLAYINCOM;
	} else if(displayType == KEYWORD_TODAY) {
		//Logic::getTodayTasks();
		return MSG_DISPLAYTODAY;
	} else {
		return MSG_INVALID;
	}
}

std::string Parser::completeCMD(std::string userInput) {
	getValidIndex(userInput);
	for(unsigned int i =_validIndex.size(); i > 0; i--) {
		//Logic::toggleComplete(_validIndex[i-1]);
	}

	if(!_invalidIndex.empty()) {// have invalid index
		return invalidIndexMsg();
	} else {
		return MSG_COMPLETE;
	}
	
}

std::string Parser::deleteCMD(std::string userInput) {
	getValidIndex(userInput);
	for(unsigned int i =_validIndex.size(); i > 0; i--) { 
		//Logic::deleteTask(_validIndex[i-1]);
	}

	if(!_invalidIndex.empty()) {// have invalid index
		return invalidIndexMsg();
	} else {
		return MSG_DELETE;
	}
	
}

std::string Parser::invalidIndexMsg() {
	std::ostringstream invalidIndexOuput;
	invalidIndexOuput << "Index ";
	for(unsigned int i = 0; i < _invalidIndex.size(); i++) {
		invalidIndexOuput << _invalidIndex[i];
		if(i == (_invalidIndex.size() -1)) {
			invalidIndexOuput << " cannot be found.\n";
		} else {
			invalidIndexOuput << ", ";
		}
	}

	return invalidIndexOuput.str();
}

void Parser::getValidIndex(std::string userInput) {
	_validIndex.clear();
	_invalidIndex.clear();
	int commaPos = userInput.find_first_of(",");
	int index;
	if(commaPos == std::string::npos) { // there is no comma, only 1 task
		index = convertToIndex(userInput);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
	} else { // more than 1 index // assumes that each index is seperated by a ","
		while(commaPos != std::string::npos) {
		std::string prevString = userInput.substr(0, commaPos);
		userInput = userInput.substr(commaPos+1, userInput.size()-1);
		index = convertToIndex(prevString);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
		commaPos = userInput.find_first_of(",");
		}
		
		index = convertToIndex(userInput);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
	}
	std::sort(_validIndex.begin(), _validIndex.end()); // sorts the valid index by ascending order
}

int Parser::convertToIndex(std::string userInput) {
	std::istringstream input(userInput);
	int index;
	input >> index;
	return index;
}

bool Parser::isValidIndex(int index) {
	if (index >= 1 /*&& index <= Display::getDisplaySize()*/) { 
		return true; 
	} else { 
		return false; 
	}
}

//can delete
std::string Parser::toLower(std::string userInput) {
		for(int i = 0; i < (int) userInput.size(); i++){
		userInput[i] = tolower(userInput[i]);
	}
		return userInput;
}


// from here onward, there is a need to rework and user regex for better parser
// Reworked!

std::string Parser::editCMD(std::string userInput) {
	std::istringstream inputStream(userInput);
	int index;
	inputStream >> index;
	if(!isValidIndex(index)) { // index is invalid
		return invalidIndexMsg();
	}
	
	QString descString(inputStream.str().c_str());
	QDate startDate;
	QTime startTime;
	QDate endDate;
	QTime endTime;
	bool dateTimeIsUnlablled;

	_nlParser.parse(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	//catch the error for invalid time and invalid date here, thrown by nlParser, thrown by DateTimeParser
	
	if (dateTimeIsUnlablled){
		//user did not specify if date/time was a start date or an end date
		_logic.addTask(descString, startDate, startTime);
	}
	else{
		_logic.addTask(descString, startDate, startTime, endDate, endTime);
	}

	//This should be an error message?
	return MSG_EDIT;
}


std::string Parser::addCMD(std::string userInput) {
	QString descString(userInput.c_str());
	QDate startDate;
	QTime startTime;
	QDate endDate;
	QTime endTime;
	bool dateTimeIsUnlablled;

	_nlParser.parse(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	//catch the error for invalid time and invalid date here, thrown by nlParser, thrown by DateTimeParser
	
	if (dateTimeIsUnlablled){
		//user did not specify if date/time was a start date or an end date
		_logic.addTask(descString, startDate, startTime);
	}
	else{
		_logic.addTask(descString, startDate, startTime, endDate, endTime);
	}

	
	//This should be an error message?
	return MSG_EDIT;

}

