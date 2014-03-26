//Parser.h
//IN PROGRESS
//v 2.6

#ifndef PARSER_H
#define PARSER_H

#include "Logic.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <QRegExp>
#include "NLParser.h"
#include "MultipleIndexParser.h"

enum TaskType{
	ACTIVITY, DEADLINE, EVENT, FLOATINGTASK
};

class Parser{
private:
	DateTimeParser _dateTimeParser;
	Logic _logic;
	std::vector<int> _index;
	NLParser _nlParser;
	MultipleIndexParser _multipleIndexParser;
	
	enum COMMAND_TYPE {
		ADD, DELETE, SEARCH, EDIT, COMPLETE, INCOMPLETE, UNDO, REDO, DISPLAY, EXIT, INVALID
	};


	static const std::string CMD_ADD;
	static const std::string CMD_EDIT;
	static const std::string CMD_DELETE;
	static const std::string CMD_DISPLAY;
	static const std::string CMD_EXIT;
	static const std::string CMD_SEARCH;
	static const std::string CMD_COMPLETE;
	static const std::string CMD_INCOMPLETE;
	static const std::string CMD_UNDO;
	static const std::string CMD_REDO;

	static const std::string MSG_INVALID;
	static const std::string MSG_DISPLAYCOM;
	static const std::string MSG_DISPLAYINCOM;
	static const std::string MSG_DISPLAYTODAY;
	static const std::string MSG_DISPLAYALL;
	static const std::string MSG_SEARCH;
	static const std::string MSG_DELETE;
	static const std::string MSG_COMPLETE;
	static const std::string MSG_INCOMPLETE;
	static const std::string MSG_UNDO;
	static const std::string MSG_REDO;
	static const std::string MSG_ADD;
	static const std::string MSG_EDIT;

	// this are keywords for display
	static const std::string KEYWORD_COMPLETE;
	static const std::string KEYWORD_INCOMPLETE;
	static const std::string KEYWORD_TODAY;
	static const std::string KEYWORD_ALL;

public:
	Parser();
	
	void getIncompleteTasks();
	void getCompleteTasks();
	std::string executeUserInput(std::string userInput);

	COMMAND_TYPE getCommand(std::string);
		
	std::string editCMD(std::string userInput);
	std::string addCMD(std::string userInput);
	
	//Able to delete multiple indexes 
	std::string deleteCMD(std::string);
	std::string completeCMD(std::string);
	std::string incompleteCMD(std::string);
	
	//checks if user input is complete, incomplete, today, tmr, this week, next week, this month, specific date)
	//additional functionailty if you can code: display from specific day1 to specific day2
	std::string displayCMD(std::string);
	
	//supports multiple search terms (search for A and B and C)
	std::string searchCMD(std::string);
	
	std::string undoCMD();
	std::string redoCMD();

	// these functions are shared with deleteCMD and completeCMD
	//std::string invalidIndexMsg();
	//void getValidIndex(std::string);
	//bool isValidIndex(int index);
	//int convertToIndex(std::string); 

};
#endif