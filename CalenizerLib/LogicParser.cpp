// LogicParser.cpp
// v1.0
// facade pattern interaction between logic and parser

#include "LogicParser.h"

LogicParser::LogicParser() {
}

AnalysedData LogicParser::parse(std::string userInput, const std::vector<Task*> &_displayList) {
	AnalysedData analysedData;
	analysedData = _parser.parse(userInput, _displayList);
	return analysedData;
}