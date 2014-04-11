//Parser.h

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <QRegExp>
#include "NLPDateParser.h"
#include "NLPSentenceParser.h"
#include "AnalysedData.h"
#include "Message.h"
#include "MultipleIndexParser.h"

class Parser{
private:
	DateTimeParser _dateTimeParser;
	std::vector<int> _index;
	NLPDateParser _nlpDateParser;
	NLPSentenceParser _nlpSentenceParser;
	MultipleIndexParser _multipleIndexParser;

	enum COMMAND_TYPE {
		ADD, DELETE, SEARCH, EDIT, COMPLETE, INCOMPLETE, UNDO, REDO, DISPLAY, EXIT, INVALID
	};

public:
	Parser();
	
	AnalysedData parse(std::string, const std::vector<Task*> &_displayList);
	COMMAND_TYPE getCommand(std::string userInput);
	
	AnalysedData undoCMD();
	AnalysedData redoCMD();	
	AnalysedData searchCMD(std::string userInput);
	AnalysedData displayCMD(std::string userInput);
	AnalysedData incompleteCMD(std::string userInput, const std::vector<Task*> &_taskList);
	AnalysedData completeCMD(std::string userInput, const std::vector<Task*> &_taskList);
	AnalysedData deleteCMD(std::string userInput, const std::vector<Task*> &_taskList);
	AnalysedData editCMD(std::string userInput);
	AnalysedData addCMD(std::string userInput);
};
#endif