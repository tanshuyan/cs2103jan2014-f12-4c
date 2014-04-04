//Parser.h
//IN PROGRESS
//v 2.8
// updated parser to accomodate new architecture

#ifndef PARSER_H
#define PARSER_H

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
#include "AnalysedData.h"


class Parser{
private:
	DateTimeParser _dateTimeParser;
	std::vector<int> _index;
	NLParser _nlParser;
	MultipleIndexParser _multipleIndexParser;

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
	static const std::string CMD_INVALID;

	static const std::string DISPLAY_ALL;
	static const std::string DISPLAY_COMPLETE;
	static const std::string DISPLAY_INCOMPLETE;
	static const std::string DISPLAY_TODAY;
	
	enum COMMAND_TYPE {
		ADD, DELETE, SEARCH, EDIT, COMPLETE, INCOMPLETE, UNDO, REDO, DISPLAY, EXIT, INVALID
	};

public:
	Parser();

	COMMAND_TYPE getCommand(std::string);
	
	AnalysedData parse(std::string);

	AnalysedData editCMD(std::string);
	AnalysedData addCMD(std::string);
	
	//Able to delete multiple indexes 
	AnalysedData deleteCMD(std::string);
	AnalysedData completeCMD(std::string);
	AnalysedData incompleteCMD(std::string);
	
	//checks if user input is complete, incomplete, today, tmr, this week, next week, this month, specific date)
	//additional functionailty if you can code: display from specific day1 to specific day2
	AnalysedData displayCMD(std::string);
	
	//supports multiple search terms (search for A and B and C)
	AnalysedData searchCMD(std::string);
	
	AnalysedData undoCMD();
	AnalysedData redoCMD();

};
#endif