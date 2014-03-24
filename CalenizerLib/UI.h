//UI.h
// for testing purposes
// v1.0
#pragma once
#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "TaskStorage.h"
#include "Task.h"
#include "Logic.h"

class UI {
private:
	

	enum COMMAND_TYPE {
		ADD, ADDD, ADDT, DELETE, SEARCH, SORT, EXIT, INVALID, EDIT, EDITD, EDITT, EDIT1, EDIT2, COMPLETE, DISPLAY, UNDO, REDO
	};

	static const std::string CMD_EDIT1;
	static const std::string CMD_EDIT2;
	static const std::string CMD_ADD;
	static const std::string CMD_EDIT;
	static const std::string CMD_DELETE;
	static const std::string CMD_DISPLAY;
	static const std::string CMD_EXIT;
	static const std::string CMD_SEARCH;
	static const std::string CMD_COMPLETE;
	static const std::string CMD_EDITT;
	static const std::string CMD_EDITD;
	static const std::string CMD_ADDT;
	static const std::string CMD_ADDD;
	static const std::string CMD_UNDO;
	static const std::string CMD_REDO;
	static const std::string CMD_USERPROMPT;

	std::istringstream _inputStream;
	Logic _cmdOperation;

public:
	UI();
	void ProgramLaunch();
	COMMAND_TYPE determineCommand(std::string);
	void executeCommand(std::string);

};

#endif