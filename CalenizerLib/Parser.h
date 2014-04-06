//Parser.h
//IN PROGRESS
//v 2.8
// updated parser to accomodate new architecture
//v 3.0
//edited some code bits to add ability to properly parse subsequent days of the week
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
#include "DisplayOutput.h"

class Parser{
private:
	DateTimeParser _dateTimeParser;
	std::vector<int> _index;
	NLParser _nlParser;
	MultipleIndexParser _multipleIndexParser;

	enum COMMAND_TYPE {
		ADD, DELETE, SEARCH, EDIT, COMPLETE, INCOMPLETE, UNDO, REDO, DISPLAY, EXIT, INVALID
	};

public:
	Parser();
	
	AnalysedData parse(std::string);
	COMMAND_TYPE getCommand(std::string);
	
	AnalysedData undoCMD();
	AnalysedData redoCMD();	
	AnalysedData searchCMD(std::string);
	AnalysedData displayCMD(std::string);
	AnalysedData incompleteCMD(std::string);
	AnalysedData completeCMD(std::string);
	AnalysedData deleteCMD(std::string);
	AnalysedData editCMD(std::string);
	AnalysedData addCMD(std::string);
};
#endif