//UILoader.h

#pragma once
#ifndef UILoader_H
#define UILoader_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "taskStorage.h"
#include "task.h"
#include "Parser.h"

class UILoader {
private:
	
	static const std::string CMD_EXIT;
	static const std::string CMD_USERPROMPT;

	std::istringstream _inputStream;
	//Logic _cmdOperation;
	std::vector<Task> _todayTasks;
	std::vector<Task> _allTasks;
	Parser _parser;

public:
	UILoader();
	void ProgramLaunch();
	void getTaskList(std::vector<Task>&);
};

#endif