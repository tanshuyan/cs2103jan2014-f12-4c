//@author A0004695A

// Logger.h

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Logger {

private:
	std::vector<std::string> _logContent;
	Logger();
	static const std::string LOG_FILENAME;
	static const std::string LOG_WARNING;
	static const std::string LOG_ERROR;
	static const std::string LOG_INFORMATION;

public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}
	
	void addWarningLog(std::string newLog);
	void addErrorLog(std::string newLog);
	void addInfoLog(std::string newLog);
	void saveLog();
};
#endif