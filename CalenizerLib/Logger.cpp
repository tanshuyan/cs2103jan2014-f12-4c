// Logger.cpp
// v 1.1
// added different warning levels

#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"

const std::string LOG_FILENAME = "log.log";
const std::string LOG_WARNING = "WARNING";
const std::string LOG_ERROR = "ERROR";
const std::string LOG_INFORMATION = "INFORMATION";


Logger::Logger() {
}

void Logger::addLog(std::string newLog) {
	_logContent.push_back(newLog);
}

void Logger::saveLog() {
	std::ofstream outputFile(LOG_FILENAME.c_str());

	for(unsigned int i = 0; i < _logContent.size(); i++) {
		outputFile << _logContent[i] << std::endl;		
	}

	outputFile.close();
}