//@author A0004695A

// Logger.cpp

#include "Logger.h"

const std::string Logger::LOG_FILENAME = "log.log";
const std::string Logger::LOG_WARNING = "WARNING";
const std::string Logger::LOG_ERROR = "ERROR";
const std::string Logger::LOG_INFORMATION = "INFORMATION";

Logger::Logger() {
}

void Logger::addWarningLog(std::string newLog) {
	std::string log = LOG_WARNING + " " + newLog;
	_logContent.push_back(log);
}

void Logger::addErrorLog(std::string newLog) {
	std::string log = LOG_ERROR + " " + newLog;
	_logContent.push_back(log);
}

void Logger::addInfoLog(std::string newLog) {
	std::string log = LOG_INFORMATION + " " + newLog;
	_logContent.push_back(log);
}

void Logger::saveLog() {
	std::ofstream outputFile(LOG_FILENAME.c_str());

	for(unsigned int i = 0; i < _logContent.size(); i++) {
		outputFile << _logContent[i] << std::endl;		
	}

	outputFile.close();
}