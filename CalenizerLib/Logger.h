// v 1.0

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger {

private:
	std::vector<std::string> _logContent;
	Logger();

public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void addLog(std::string);
	void saveLog();

};
#endif