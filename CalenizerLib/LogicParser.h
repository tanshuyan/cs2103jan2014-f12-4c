//@author A0094659L

//LogicParser.h 

#ifndef LOGICPARSER_H
#define LOGICPARSER_H

#include <string>
#include "AnalysedData.h"
#include "Parser.h"

class LogicParser {
private:
	Parser _parser;

public:
	LogicParser();
	AnalysedData parse(std::string userInput, const std::vector<Task*> &_displayList);
};
#endif