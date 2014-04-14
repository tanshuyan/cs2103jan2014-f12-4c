//@author A0094659L

// LogicParser.cpp

#include "LogicParser.h"

LogicParser::LogicParser() {
}

AnalysedData LogicParser::parse(std::string userInput, const std::vector<Task*> &_displayList) {
	AnalysedData analysedData;
	analysedData = _parser.parse(userInput, _displayList);
	return analysedData;
}