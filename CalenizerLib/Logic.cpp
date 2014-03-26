// Logic.cpp
// v1.2

#include <string>
#include <assert.h>
#include "task.h"
#include "taskDeadline.h"
#include "taskFloat.h"
#include "TaskTimed.h"
#include "Logic.h"
#include "TaskStorage.h"
#include "Logger.h"
#include <iostream>

const std::string Logic::TASK_DEADLINE = "DEADLINE";
const std::string Logic::TASK_TIMED = "TIMED";
const std::string Logic::TASK_FLOAT = "FLOAT";


Logic::Logic(){
	loadFileContent();
}

Logic::~Logic() {
	for(unsigned int i = 0; i < _taskList.size(); i++) {
	delete _taskList[i];
	}
}
	
void Logic::loadFileContent() {
	_taskList.clear();
	_userStorage.loadFile(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::addTask(std::string taskDesc){
	TaskFloat* newFloatPtr = new TaskFloat;
	newFloatPtr->setTask(TASK_FLOAT, false, taskDesc);
	_taskList.push_back(newFloatPtr);
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}
	
void Logic::addTask(std::string taskDesc, DateTime deadline) {
	TaskDeadline* newDeadlinePtr = new TaskDeadline;
	newDeadlinePtr->setTask(TASK_DEADLINE, false, taskDesc, deadline);
	_taskList.push_back(newDeadlinePtr);
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::addTask(std::string taskDesc, DateTime startDateTime, DateTime endDateTime) {
	TaskTimed* newTimedPtr = new TaskTimed;
	newTimedPtr->setTask(TASK_TIMED, false, taskDesc, startDateTime, endDateTime);
	_taskList.push_back(newTimedPtr);
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

//TODO: the function doesnt support the ability to convert deadline to timed yet
void Logic::editTask(int index, DateTime dateTime) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);
	if((*taskToEdit)->getTaskType() == TASK_FLOAT) { // if task is a float, convert it into a deadline task
		std::string taskContent = (*taskToEdit)->taskToString();
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->stringToTask(taskContent);
		newDeadlinePtr->setTaskType(TASK_DEADLINE);
		newDeadlinePtr->setDeadline(dateTime);
		delete *taskToEdit; // delete the old float task
		_taskList.erase(taskToEdit); // delete the pointer to task
		_taskList.push_back(newDeadlinePtr);
	} else {
		(*taskToEdit)->setDeadline(dateTime);
	}
	
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

//TODO: this function doesnt support the checking of deadline time with the timed input
void Logic::editTask(int index, DateTime startDateTime, DateTime endDateTime) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if(((*taskToEdit)->getTaskType() == TASK_FLOAT) || ((*taskToEdit)->getTaskType() == TASK_DEADLINE)) { // if task is a float or deadline, convert it into a timed task
		std::string taskContent = (*taskToEdit)->taskToString();
		TaskTimed* newTimedPtr = new TaskTimed;
		newTimedPtr->stringToTask(taskContent);
		newTimedPtr->setTaskType(TASK_TIMED);
		newTimedPtr->setStartDate(startDateTime);
		newTimedPtr->setDeadline(endDateTime);
		delete *taskToEdit; // delete the old float/deadline task
		_taskList.erase(taskToEdit); // delete the pointer to task
		_taskList.push_back(newTimedPtr);
	} else {
		(*taskToEdit)->setStartDate(startDateTime);
		(*taskToEdit)->setDeadline(endDateTime);
	}
	
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::editTask(int index, std::string taskDesc) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);
	(*taskToEdit)->setTaskDesc(taskDesc);
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

// edit deadline task and allows float tasks to convert to deadline tasks
void Logic::editTask(int index, std::string taskDesc, DateTime deadline) {	
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if((*taskToEdit)->getTaskType() == TASK_FLOAT) { // if task is a float, convert it into a deadline task
		std::string taskContent = (*taskToEdit)->taskToString();
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->stringToTask(taskContent);
		newDeadlinePtr->setTaskType(TASK_DEADLINE);
		newDeadlinePtr->setTaskDesc(taskDesc);
		newDeadlinePtr->setDeadline(deadline);
		delete *taskToEdit; // delete the old float task
		_taskList.erase(taskToEdit); // delete the pointer to task
		_taskList.push_back(newDeadlinePtr);
		
	} else {
		(*taskToEdit)->setTaskDesc(taskDesc);
		(*taskToEdit)->setDeadline(deadline);
	}
	
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::editTask(int index, std::string taskDesc, DateTime startDateTime, DateTime endDateTime) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if(((*taskToEdit)->getTaskType() == TASK_FLOAT) || ((*taskToEdit)->getTaskType() == TASK_DEADLINE)) { // if task is a float or deadline, convert it into a timed task
		std::string taskContent = (*taskToEdit)->taskToString();
		TaskTimed* newTimedPtr = new TaskTimed;
		newTimedPtr->stringToTask(taskContent);
		newTimedPtr->setTaskType(TASK_TIMED);
		newTimedPtr->setTaskDesc(taskDesc);
		newTimedPtr->setStartDate(startDateTime);
		newTimedPtr->setDeadline(endDateTime);
		delete *taskToEdit; // delete the old float/deadline task
		_taskList.erase(taskToEdit); // delete the pointer to task
		_taskList.push_back(newTimedPtr);
	} else {
		(*taskToEdit)->setTaskDesc(taskDesc);
		(*taskToEdit)->setStartDate(startDateTime);
		(*taskToEdit)->setDeadline(endDateTime);
	}
	
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

bool Logic::isValidIndex(int index) {
	if (index >= 1 && index <= _displayList.size()) { 
		return true; 
	} else { 
		return false; 
	}
}

void Logic::deleteTask(std::vector<int> index){
	int taskIndex;
	std::vector<int> invalidIndex;
	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToDelete = indexToIterator(taskIndex);
			delete *taskToDelete;
			_taskList.erase(taskToDelete);
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::setComplete(std::vector<int> index){
	int taskIndex;
	std::vector<int> invalidIndex;
	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToComplete = indexToIterator(taskIndex);
			(*taskToComplete)->setCompleteStatus(true);
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::setIncomplete(std::vector<int> index){
	int taskIndex;
	std::vector<int> invalidIndex;
	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToIncomplete = indexToIterator(taskIndex);
			(*taskToIncomplete)->setCompleteStatus(false);
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::getIncompleteTasks(){
	_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, false);
	_display.displayTasks(_displayList);
	Logger& logLogic = Logger::getInstance();
	logLogic.addLog("display incomplete\n");

}

void Logic::getTasks() {
	_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList);
	_display.displayTasks(_displayList);
}

void Logic::getCompleteTasks(){
	_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, true);
	_display.displayTasks(_displayList);		
}
	
void Logic::searchTasks(std::string searchTerm){
	_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, searchTerm);
	_display.displayTasks(_displayList);	
}

void Logic::undo(){
	Logger& logLogic = Logger::getInstance();

	if(_History.undo(_taskList)){
		_userStorage.writeStorage(_taskList);
		//_display.something();//confirmation message I haven't coded yet
	}
	else{
		logLogic.addLog("undo failed\n");
		//_display.something();//error message I haven't coded yet
	}
}

void Logic::redo(){
	Logger& logLogic = Logger::getInstance();
	if(_History.redo(_taskList)){
		_userStorage.writeStorage(_taskList);
		//_display.something();//confirmation message I haven't coded yet
	}
	else{
		logLogic.addLog("redo failed\n");
		//_display.something();//error message I haven't coded yet
	}
}

std::vector<Task*>::iterator Logic::indexToIterator(int index){
	std::vector<std::vector<Task*>::iterator>::iterator iter = _displayIndexList.begin();
	for(int i=1; i!=index; i++){
		iter++;
	}
	return *iter;
}

/*
unsigned int Logic::getDisplaySize() {
	return _displayList.size();
}*/