//Parser.h
//IN PROGRESS
//v 1.2

#ifndef PARSER_H
#define PARSER_H

#include "Logic.h"
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <QRegExp>
#include "NLParser.h"

enum TaskType{
	ACTIVITY, DEADLINE, EVENT, FLOATINGTASK
};

class Parser{
private:
	DateTimeParser _dateTimeParser;
	Logic _logic;
	//std::string _userInput;
	std::vector<int> _validIndex;
	std::vector<int> _invalidIndex;

	NLParser _nlParser;
	
	std::vector<std::string> _taskDesc;
	// _startDate ;
	// _startTime;


	enum COMMAND_TYPE {
		ADD, DELETE, SEARCH, EDIT, COMPLETE, UNDO, REDO, DISPLAY, EXIT, INVALID
	};


	static const std::string CMD_ADD;
	static const std::string CMD_EDIT;
	static const std::string CMD_DELETE;
	static const std::string CMD_DISPLAY;
	static const std::string CMD_EXIT;
	static const std::string CMD_SEARCH;
	static const std::string CMD_COMPLETE;
	static const std::string CMD_UNDO;
	static const std::string CMD_REDO;

	static const std::string MSG_INVALID;
	static const std::string MSG_DISPLAYCOM;
	static const std::string MSG_DISPLAYINCOM;
	static const std::string MSG_DISPLAYTODAY;
	static const std::string MSG_SEARCH;
	static const std::string MSG_DELETE;
	static const std::string MSG_COMPLETE;
	static const std::string MSG_UNDO;
	static const std::string MSG_REDO;
	static const std::string MSG_ADD;
	static const std::string MSG_EDIT;

	// this are keywords for display
	static const std::string KEYWORD_COMPLETE;
	static const std::string KEYWORD_INCOMPLETE;
	static const std::string KEYWORD_TODAY;

	// this are keywords for timed tasks
	static const std::string KEYWORD_FROM;
	static const std::string KEYWORD_TO;

	// this are keywords for deadline tasks
	static const std::string KEYWORD_ON;
	static const std::string KEYWORD_BY;
	static const std::string KEYWORD_AT;
	
	// this are keywords for edit
	static QRegExp RX_FROM_UNTIL;
	static QRegExp RX_FROM;
	//Not yet implemented
	static QRegExp RX_UNTIL;
	static QRegExp RX_ON_AT_BY;
	static QRegExp RX_UNTIL_FROM;


public:
	Parser();
	
	std::string executeUserInput(std::string userInput);

	std::string toLower(std::string);

	COMMAND_TYPE getCommand(std::string);


	std::string addCMD(std::string);
	
	bool isTimedTask(std::string);
	bool isDeadlineTask(std::string);
	
	
	
	std::string editCMD(std::string);
	
	
	//Able to delete multiple indexes 
	std::string deleteCMD(std::string);
	std::string completeCMD(std::string);
	
	//checks if user input is complete, incomplete, today, tmr, this week, next week, this month, specific date)
	//additional functionailty if you can code: display from specific day1 to specific day2
	std::string displayCMD(std::string);
	
	//supports multiple search terms (search for A and B and C)
	std::string searchCMD(std::string);
	
	std::string undoCMD();
	std::string redoCMD();

	// these functions are shared with deleteCMD and completeCMD
	std::string invalidIndexMsg();
	void getValidIndex(std::string);
	bool isValidIndex(int index);
	int convertToIndex(std::string); 
};
#endif