//UI.cpp

#include <iostream>
#include <string>
#include <sstream>
#include "UI.h"
#include "task.h"
#include "DateTime.h"
#include <iomanip>


const std::string UI::CMD_UNDO = "undo";
const std::string UI::CMD_REDO = "redo";
const std::string UI::CMD_ADD = "add";
const std::string UI::CMD_ADDD = "addd";
const std::string UI::CMD_ADDT = "addt";
const std::string UI::CMD_EDIT = "edit";
const std::string UI::CMD_EDITD = "editd";
const std::string UI::CMD_EDITT = "editt";
const std::string UI::CMD_DELETE = "delete";
const std::string UI::CMD_DISPLAY = "display";
const std::string UI::CMD_EXIT = "exit";
const std::string UI::CMD_SEARCH = "search";
const std::string UI::CMD_COMPLETE = "complete";
const std::string UI::CMD_USERPROMPT= "Enter command: ";

UI::UI(){
}

void UI::ProgramLaunch() {
	std::cout << "Welcome to Calenizer!" << std::endl;
	_cmdOperation.getIncompleteTasks();
	std::cout << CMD_USERPROMPT;
	std::string command;
	std::cin >> command;
	while(command != CMD_EXIT) {
		executeCommand(command);
		std::cout << CMD_USERPROMPT;
		std::cin >> command;
	}
	exit(0);
}

UI::COMMAND_TYPE UI::determineCommand(std::string command) {
if(command == CMD_ADD) {
		return COMMAND_TYPE::ADD;
	} else if ((command==CMD_DELETE)) {
		return COMMAND_TYPE::DELETE;
	} else if ((command== CMD_DISPLAY)) {
		return COMMAND_TYPE::DISPLAY;
	} else if ((command== CMD_EXIT)) {
		return COMMAND_TYPE::EXIT;
	} else if ((command== CMD_SEARCH)) {
		return COMMAND_TYPE::SEARCH;
	} else if ((command== CMD_EDIT)) {
		return COMMAND_TYPE::EDIT;
	} else if ((command== CMD_COMPLETE)) {
		return COMMAND_TYPE::COMPLETE;
	} else if ((command == CMD_UNDO)) {
		return COMMAND_TYPE::UNDO;
	} else if ((command == CMD_REDO)) {
		return COMMAND_TYPE::REDO;
	} else if ((command == CMD_ADDD)) {
		return COMMAND_TYPE::ADDD;
	} else if ((command == CMD_ADDT)) {
		return COMMAND_TYPE::ADDT;
	} else if((command == CMD_EDITD)) {
		return COMMAND_TYPE::EDITD;
	} else if ((command == CMD_EDITT)) {
		return COMMAND_TYPE::EDITT;
	} else {
		return COMMAND_TYPE::INVALID;
	}
}

void UI::executeCommand(std::string command) {

	int index;
	std::string taskInfo;
	std::string dummy;
	std::string date;
	DateTime deadline;
	std::string date2;
	DateTime startTime;

	switch(determineCommand(command)) {

	case ADD: {	
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		_cmdOperation.addTask(taskInfo);
		_cmdOperation.getIncompleteTasks();
		break;
	}

	case ADDD: {
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		std::getline(std::cin, date);
		deadline.dataFromString(date);
		_cmdOperation.addTask(taskInfo,deadline);
		_cmdOperation.getIncompleteTasks();
		break;
	}

	case ADDT: {
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		std::getline(std::cin, date);
		startTime.dataFromString(date);
		std::getline(std::cin, date2);
		deadline.dataFromString(date2);
		_cmdOperation.addTask(taskInfo, startTime, deadline);
		_cmdOperation.getIncompleteTasks();
		break;
	}

	case EDITD: {
		std::string date1;
		DateTime dead;
		std::cin >> index;
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		std::getline(std::cin, date1);
		dead.dataFromString(date1);
		_cmdOperation.editTask(index, taskInfo, dead);
		_cmdOperation.getIncompleteTasks();
		break;
				}

	case EDITT: {
		std::string date1;
		std::string stark;
		DateTime dead;
		DateTime start;
		std::cin >> index;
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		std::getline(std::cin, stark);
		std::getline(std::cin, date1);
		dead.dataFromString(date1);
		start.dataFromString(stark);
		_cmdOperation.editTask(index, taskInfo, start, dead);
		_cmdOperation.getIncompleteTasks();
		break;
				}

	case DELETE: {
		int index;
		std::cin>> index;
		_cmdOperation.deleteTask(index);
		_cmdOperation.getIncompleteTasks();
		break;
	}

	case EDIT: {
		std::cin >> index;
		std::getline(std::cin, dummy);
		std::getline(std::cin, taskInfo);
		_cmdOperation.editTask(index, taskInfo);
		_cmdOperation.getIncompleteTasks();
		break;
			   }
	
	case SEARCH: {
		std::string searchTerm;
		std::cin >> searchTerm;
		_cmdOperation.searchTasks(searchTerm);
		break;
		break;
				 }

	case DISPLAY: {
		std::string displayType;
		std::cin >> displayType;
		if(displayType == "complete") {
		_cmdOperation.getCompleteTasks();
		} else if(displayType == "incomplete") {
			_cmdOperation.getIncompleteTasks();
		} else { 
			break;
		}
		
		break;
				 }

	case COMPLETE: {
		int index;
		std::cin>> index;
		_cmdOperation.toggleComplete(index);
		_cmdOperation.getIncompleteTasks();
		break;
				   }

	case UNDO: {
		_cmdOperation.undo();		
		_cmdOperation.getIncompleteTasks();
		break;
			   }

	case REDO: {
		_cmdOperation.redo();
		_cmdOperation.getIncompleteTasks();
		break;
			   }

	case EXIT: {
		break;
			   }

	case INVALID: {
		
		break;
				  }
	} // end switch block


}