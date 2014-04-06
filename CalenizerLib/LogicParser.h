//LogicParser.h 
//v 1.0
// 

#ifndef LOGICPARSER_H
#define LOGICPARSER_H

#include "AnalysedData.h"
#include "Parser.h"
#include <string>

class LogicParser {
private:
	Parser _parser;

public:
	LogicParser();
	AnalysedData parse(std::string, std::vector<Task*> _displayList);

};
#endif