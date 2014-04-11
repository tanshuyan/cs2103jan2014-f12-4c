//Parser.cpp
#include "Parser.h"

Parser::Parser() {
}

AnalysedData Parser::parse(std::string userInput, const std::vector<Task*> &_displayList) {
	std::istringstream input(userInput);
	std::string command;
	std::string dummy;
	std::string commandLine;
	input >> command; // the first word is always a command
	std::getline(input, dummy, ' '); // trim whitespace 
	std::getline(input, commandLine); // commandLine gets the remaining userInput

	switch(getCommand(command)) {
	case ADD: {
		return addCMD(commandLine);
		break;
	}
	case DELETE: {
		return deleteCMD(commandLine, _displayList);
		break;
	}
	case EDIT: {
		return editCMD(commandLine);
		break;
	}	
	case SEARCH: {
		return searchCMD(commandLine);
		break;
	}
	case DISPLAY: {
		return displayCMD(commandLine);
		break;
	}
	case COMPLETE: {
		return completeCMD(commandLine, _displayList);
		break;
	}
	case INCOMPLETE: {
		return incompleteCMD(commandLine, _displayList);
		break;
	}
	case UNDO: {
		return undoCMD();
		break;
	}
	case REDO: {
		return redoCMD();
		break;
	}
	case EXIT: {
		AnalysedData analysedData;
		analysedData.setCommand(Message::CMD_EXIT);
		return analysedData;
		break;
	}
	case INVALID: {
		AnalysedData analysedData;
		analysedData.setCommand(Message::CMD_INVALID);
		return analysedData;
		break;
	}
	default: {
		AnalysedData analysedData;
		analysedData.setCommand(Message::CMD_INVALID);
		return analysedData;
		break; 
	}
	}

}

Parser::COMMAND_TYPE Parser::getCommand(std::string command) {
	if(command == Message::CMD_ADD) {
		return COMMAND_TYPE::ADD;
	} else if ((command== Message::CMD_DELETE)) {
		return COMMAND_TYPE::DELETE;
	} else if ((command == Message::CMD_DISPLAY)) {
		return COMMAND_TYPE::DISPLAY;
	} else if ((command == Message::CMD_EXIT)) {
		return COMMAND_TYPE::EXIT;
	} else if ((command == Message::CMD_SEARCH)) {
		return COMMAND_TYPE::SEARCH;
	} else if ((command == Message::CMD_EDIT)) {
		return COMMAND_TYPE::EDIT;
	} else if ((command == Message::CMD_COMPLETE)) {
		return COMMAND_TYPE::COMPLETE;
	} else if ((command == Message::CMD_INCOMPLETE)) {
		return COMMAND_TYPE::INCOMPLETE;
	} else if ((command == Message::CMD_UNDO)) {
		return COMMAND_TYPE::UNDO;
	} else if ((command == Message::CMD_REDO)) {
		return COMMAND_TYPE::REDO;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}

AnalysedData Parser::undoCMD() {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_UNDO);
	return analysedData;
}

AnalysedData Parser::redoCMD() {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_REDO);
	return analysedData;
}

AnalysedData Parser::searchCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_SEARCH);
	analysedData.setDisplayType(userInput);
	return analysedData;
}

AnalysedData Parser::displayCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_DISPLAY);
	if(userInput.empty()) {
		analysedData.setDisplayType(Message::DISPLAY_ALL);
	} else if(userInput == Message::DISPLAY_COMPLETE || userInput == Message::DISPLAY_ALL || userInput == Message::DISPLAY_INCOMPLETE || userInput == Message::DISPLAY_TODAY) {
		analysedData.setDisplayType(userInput);
	} else {
		analysedData.setCommand(Message::CMD_INVALID);
	}
	return analysedData;
}

AnalysedData Parser::incompleteCMD(std::string userInput, const std::vector<Task*> &_displayList) {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_INCOMPLETE);
	try{
		_index = _nlpSentenceParser.parseSentence(userInput.c_str(), _displayList);
	}
	catch(SentenceFailedToParse){
		 _multipleIndexParser.parseMultipleIndex(userInput.c_str());
	}
	analysedData.setIndexVector(_index);
	return analysedData;
}

AnalysedData Parser::completeCMD(std::string userInput, const std::vector<Task*> &_displayList) {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_COMPLETE);
	try{
		_index = _nlpSentenceParser.parseSentence(userInput.c_str(), _displayList);
	}
	catch(SentenceFailedToParse){
		 _multipleIndexParser.parseMultipleIndex(userInput.c_str());
	}
	analysedData.setIndexVector(_index);
	return analysedData;
}

AnalysedData Parser::deleteCMD(std::string userInput, const std::vector<Task*> &_displayList) {
	AnalysedData analysedData;
	analysedData.setCommand(Message::CMD_DELETE);
	try{
		_index = _nlpSentenceParser.parseSentence(userInput.c_str(), _displayList);
	}
	catch(SentenceFailedToParse){
		 _multipleIndexParser.parseMultipleIndex(userInput.c_str());
	}
	analysedData.setIndexVector(_index);
	return analysedData;
}

AnalysedData Parser::editCMD(std::string userInput) {
	AnalysedData analysedData;
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
	bool dateTimeIsUnlabelled;
	int dayOfWeek = -1;

	_nlpDateParser.parseDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek);
	descString = descString.trimmed();

	analysedData.setCommand(Message::CMD_EDIT);
	analysedData.setIndex(index);
	analysedData.setTaskDesc(descString.toStdString());
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
	analysedData.setDayOfWeek(dayOfWeek);
	return analysedData;
}

AnalysedData Parser::addCMD(std::string userInput) {
	AnalysedData analysedData;
	QString descString(userInput.c_str());
	QDate startDate;
	QTime startTime;
	QDate endDate;
	QTime endTime;
	bool dateTimeIsUnlabelled;
	int dayOfWeek = -1;

	_nlpDateParser.parseDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek);	
	descString = descString.trimmed();

	analysedData.setCommand(Message::CMD_ADD);
	analysedData.setTaskDesc(descString.toStdString());
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
	analysedData.setDayOfWeek(dayOfWeek);
	return analysedData;
}

