// LogicParser.cpp
// v1.0
// facade pattern interaction between logic and parser

#include "LogicParser.h"

LogicParser::LogicParser() {
}

AnalysedData LogicParser::parse(std::string userInput) {
	AnalysedData analysedData;
	analysedData = _parser.parse(userInput);
	return analysedData;
}