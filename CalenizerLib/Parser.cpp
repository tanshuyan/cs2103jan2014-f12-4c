//Parser.cpp
//IN PROGRESS
//v 2.8
//editted the display string to view, exit to quit
//defaulted view to view all

#include "Parser.h"

Parser::Parser() {
}

AnalysedData Parser::parse(std::string userInput) {
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
		return deleteCMD(commandLine);
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
		return completeCMD(commandLine);
		break;
	}
	case INCOMPLETE: {
		return incompleteCMD(commandLine);
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
		analysedData.setCommand(DisplayOutput::CMD_EXIT);
		return analysedData;
		break;
	}
	case INVALID: {
		AnalysedData analysedData;
		analysedData.setCommand(DisplayOutput::CMD_INVALID);
		return analysedData;
		break;
	}
	default: {
		AnalysedData analysedData;
		analysedData.setCommand(DisplayOutput::CMD_INVALID);
		return analysedData;
		break;
	}
	}

}

Parser::COMMAND_TYPE Parser::getCommand(std::string command) {
	if(command == DisplayOutput::CMD_ADD) {
		return COMMAND_TYPE::ADD;
	} else if ((command== DisplayOutput::CMD_DELETE)) {
		return COMMAND_TYPE::DELETE;
	} else if ((command == DisplayOutput::CMD_DISPLAY)) {
		return COMMAND_TYPE::DISPLAY;
	} else if ((command == DisplayOutput::CMD_EXIT)) {
		return COMMAND_TYPE::EXIT;
	} else if ((command == DisplayOutput::CMD_SEARCH)) {
		return COMMAND_TYPE::SEARCH;
	} else if ((command == DisplayOutput::CMD_EDIT)) {
		return COMMAND_TYPE::EDIT;
	} else if ((command == DisplayOutput::CMD_COMPLETE)) {
		return COMMAND_TYPE::COMPLETE;
	} else if ((command == DisplayOutput::CMD_INCOMPLETE)) {
		return COMMAND_TYPE::INCOMPLETE;
	} else if ((command == DisplayOutput::CMD_UNDO)) {
		return COMMAND_TYPE::UNDO;
	} else if ((command == DisplayOutput::CMD_REDO)) {
		return COMMAND_TYPE::REDO;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}

AnalysedData Parser::undoCMD() {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_UNDO);
	return analysedData;
}

AnalysedData Parser::redoCMD() {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_REDO);
	return analysedData;
}

AnalysedData Parser::searchCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_SEARCH);
	analysedData.setDisplayType(userInput);
	return analysedData;
}

AnalysedData Parser::displayCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_DISPLAY);
	if(userInput.empty()) {
		analysedData.setDisplayType(DisplayOutput::DISPLAY_ALL);
	} else if(userInput == DisplayOutput::DISPLAY_COMPLETE || userInput == DisplayOutput::DISPLAY_ALL || userInput == DisplayOutput::DISPLAY_INCOMPLETE || userInput == DisplayOutput::DISPLAY_TODAY) {
		analysedData.setDisplayType(userInput);
	} else {
		analysedData.setCommand(DisplayOutput::CMD_INVALID);
	}
	return analysedData;
}

AnalysedData Parser::incompleteCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_INCOMPLETE);
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
	analysedData.setIndexVector(_index);
	return analysedData;
}

AnalysedData Parser::completeCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_COMPLETE);
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
	analysedData.setIndexVector(_index);
	return analysedData;
}

AnalysedData Parser::deleteCMD(std::string userInput) {
	AnalysedData analysedData;
	analysedData.setCommand(DisplayOutput::CMD_DELETE);
	_index = _multipleIndexParser.parseMultipleIndex(userInput);
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

	_nlParser.parseDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled);
	//catch the error for invalid time and invalid date here, thrown by nlParser, thrown by DateTimeParser
	descString = descString.trimmed();

	analysedData.setCommand(DisplayOutput::CMD_EDIT);
	analysedData.setIndex(index);
	analysedData.setTaskDesc(descString.toStdString());
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
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
//	try{
	_nlParser.parseDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled);
/*	}
	catch(int e){
		if (e == 10){
			std::cout<<"invalid time\n";
		}
		if (e == 20){
			std::cout<<"invalid date\n";
		}
	return analysedData;
	}*/
	
	_nlParser.guessContextualTime(descString, startTime);
	descString = descString.trimmed();

	analysedData.setCommand(DisplayOutput::CMD_ADD);
	analysedData.setTaskDesc(descString.toStdString());
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
	return analysedData;
}

