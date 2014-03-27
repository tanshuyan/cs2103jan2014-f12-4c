//UI.h
// for testing purposes
// v1.1
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
#include "Logic.h"
#include "UIDisplay.h"

class UI {
private:
	
	Logic _logic;
	std::istringstream _inputStream;

	static const std::string CMD_EXIT;
	DisplayOutput _displayOutput;

public:
	UI();
	void ProgramLaunch();

};

#endif