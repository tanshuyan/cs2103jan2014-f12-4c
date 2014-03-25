//Parser.cpp
//IN PROGRESS
//v 2.6

#include "Parser.h"

const std::string Parser::MSG_INVALID = "Invalid command.\n";

//display msg
const std::string Parser::MSG_DISPLAYCOM = "displayed completed tasks";
const std::string Parser::MSG_DISPLAYINCOM = "displayed incompleted tasks";
const std::string Parser::MSG_DISPLAYTODAY = "displayed today tasks";
const std::string Parser::MSG_DISPLAYALL = "displayed all tasks";

//search msg
const std::string Parser::MSG_SEARCH = "search completed";
//delete msg
const std::string Parser::MSG_DELETE = "all indicated tasks deleted";
//complete msg
const std::string Parser::MSG_COMPLETE = "all indicated tasks completed";
const std::string Parser::MSG_INCOMPLETE = "all indicated tasks incompleted";
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
const std::string Parser::CMD_INCOMPLETE = "incomplete";
const std::string Parser::CMD_UNDO = "undo";
const std::string Parser::CMD_REDO = "redo";
	
const std::string Parser::KEYWORD_COMPLETE = "complete";
const std::string Parser::KEYWORD_INCOMPLETE = "incomplete";
const std::string Parser::KEYWORD_TODAY = "today";
const std::string Parser::KEYWORD_ALL = "all";

Parser::Parser() {
}

void Parser::getIncompleteTasks() {
	_logic.getIncompleteTasks();
}

void Parser::getCompleteTasks() {
	_logic.getCompleteTasks();
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
	} else if ((command == CMD_INCOMPLETE)) {
		return COMMAND_TYPE::INCOMPLETE;
	} else if ((command == CMD_UNDO)) {
		return COMMAND_TYPE::UNDO;
	} else if ((command == CMD_REDO)) {
		return COMMAND_TYPE::REDO;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}


std::string Parser::executeUserInput(std::string userInput) {
	std::istringstream input(userInput);
	std::string command;
	std::string dummy;
	std::string commandLine;
	input >> command; // the first word is always a command
	std::getline(input, dummy, ' '); // trim whitespace 
	std::getline(input, commandLine); // commandLine gets the remaining userInput
	std::string commandStatus;
	switch(getCommand(command)) {
	case ADD: {
		commandStatus = addCMD(commandLine);		
		break;
	}
	case DELETE: {
		commandStatus = deleteCMD(commandLine);
		break;
	}
	case EDIT: {
		commandStatus = editCMD(commandLine);
		break;
	}	
	case SEARCH: {
		commandStatus = searchCMD(commandLine);
		break;
	}
	case DISPLAY: {
		commandStatus = displayCMD(commandLine);
		break;
	}
	case COMPLETE: {
		commandStatus = completeCMD(commandLine);
		break;
	}
	case INCOMPLETE: {
		commandStatus = incompleteCMD(commandLine);
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
		commandStatus = CMD_EXIT;
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
	_logic.undo();
	return MSG_UNDO;
}

std::string Parser::redoCMD() {
	_logic.redo();
	return MSG_REDO;
}

std::string Parser::searchCMD(std::string userInput) {
	_logic.searchTasks(userInput);
	return MSG_SEARCH;
}

std::string Parser::displayCMD(std::string userInput) {
	std::istringstream input(userInput);
	std::string displayType;
	input >> displayType;
	if (displayType == KEYWORD_COMPLETE) {
		_logic.getCompleteTasks();
		return MSG_DISPLAYCOM;
	} else if (displayType == KEYWORD_INCOMPLETE) {
		_logic.getIncompleteTasks();
		return MSG_DISPLAYINCOM;
	} else if(displayType == KEYWORD_TODAY) {
		//Logic::getTodayTasks();
		return MSG_DISPLAYTODAY;
	} else if (displayType == KEYWORD_ALL) {
		_logic.getTasks();
		return MSG_DISPLAYALL;
	} else {
		return MSG_INVALID;
	}
}

std::string Parser::incompleteCMD(std::string userInput) {
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
	_logic.setIncomplete(_index);
	return MSG_INCOMPLETE;
}

std::string Parser::completeCMD(std::string userInput) {
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
	_logic.setComplete(_index);
	return MSG_COMPLETE;
}

std::string Parser::deleteCMD(std::string userInput) {
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
	_logic.deleteTask(_index);
	return MSG_DELETE;
}

// from here onward, there is a need to rework and user regex for better parser
// Reworked!

std::string Parser::editCMD(std::string userInput) {
	std::istringstream inputStream(userInput);
	int index;
	inputStream >> index;
	std::string input;
	std::getline(inputStream, input);

	QString descString(input.c_str());
	QDate startDate;
	QTime startTime;
	QDate endDate;
	QTime endTime;
	bool dateTimeIsUnlablled;

	_nlParser.parse(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	//catch the error for invalid time and invalid date here, thrown by nlParser, thrown by DateTimeParser
	descString = descString.trimmed();
	if (dateTimeIsUnlablled){
		//user did not specify if date/time was a start date or an end date
		//_logic.editTask(index, descString.toStdString(), startDate, startTime);

	}
	else{
		//_logic.editTask(index, descString.toStdString(), startDate, startTime, endDate, endTime);
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
	try{
	_nlParser.parse(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	}
	catch(int e){
		if (e == 10){
			std::cout<<"invalid time\n";
		}
		if (e == 20){
			std::cout<<"invalid date\n";
		}
	return "lalala";
	}
	_nlParser.guessContextualTime(descString, startTime);
	descString = descString.trimmed();
	//catch the error for invalid time and invalid date here, thrown by nlParser, thrown by DateTimeParser
	if (dateTimeIsUnlablled || (endDate.isNull() && endTime.isNull())){
		//user did not specify if date/time was a start date or an end date
	//	_logic.addTask(descString.toStdString(), startDate, startTime);
	}
	else{
//		_logic.addTask(descString.toStdString(), startDate, startTime, endDate, endTime);
	}

	
	//This should be an error message?
	return MSG_EDIT;

}



/*
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
	if (index >= 1 && index <= _logic.getDisplaySize()) { 
		return true; 
	} else { 
		return false; 
	}
}

*/

