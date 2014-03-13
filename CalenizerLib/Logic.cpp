// Logics.cpp

#include <string>
#include "task.h"
#include "taskDeadline.h"
#include "taskFloat.h"
#include "TaskTimed.h"
#include "Logic.h"
#include "TaskStorage.h"

const std::string Logic::TASK_DEADLINE = "DEADLINE";
const std::string Logic::TASK_TIMED = "TIMED";
const std::string Logic::TASK_FLOAT = "FLOAT";


Logic::Logic(){
	loadFileContent();
}
	
void Logic::loadFileContent() {
	_taskList = _userStorage.loadStorage();
}


void Logic::addFloatTask(std::string taskDesc){
	TaskFloat* newFloatPtr = new TaskFloat;
	newFloatPtr->setTask(TASK_FLOAT, false, taskDesc);
	_taskList.push_back(newFloatPtr);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}
	
void Logic::addDeadlineTask(std::string taskDesc, DateTime deadline) {
	TaskDeadline* newDeadlinePtr = new TaskDeadline;
	newDeadlinePtr->setTask(TASK_DEADLINE, false, taskDesc, deadline);
	_taskList.push_back(newDeadlinePtr);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::addTimedTask(std::string taskDesc, DateTime startDateTime, DateTime endDateTime) {
	TaskTimed* newTimedPtr = new TaskTimed;
	newTimedPtr->setTask(TASK_TIMED, false, taskDesc, startDateTime, endDateTime);
	_taskList.push_back(newTimedPtr);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::deleteTask(int index){
	std::vector<Task*>::iterator taskToDelete = indexToIterator(index);
	delete *taskToDelete;
	_taskList.erase(taskToDelete);
		
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::editTask(int index, std::string taskDesc) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);
	(*taskToEdit)->setTaskDesc(taskDesc);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::editTask(int index, std::string taskDesc, DateTime deadline) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);
	(*taskToEdit)->setTaskDesc(taskDesc);
	(*taskToEdit)->setDeadline(deadline);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::editTask(int index, std::string taskDesc, DateTime startDateTime, DateTime endDateTime) {
	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);
	(*taskToEdit)->setTaskDesc(taskDesc);
	(*taskToEdit)->setStartDate(startDateTime);
	(*taskToEdit)->setDeadline(endDateTime);
	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
	return;
}


void Logic::toggleComplete(int index){
	std::vector<Task*>::iterator taskToToggle = indexToIterator(index);
	if ((*taskToToggle)->getCompleteStatus()){
		(*taskToToggle)->setCompleteStatus(false);
	}
	else{
		(*taskToToggle)->setCompleteStatus(true);
	}
}

void Logic::getIncompleteTasks(){
	_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, false);
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
	if(_History.undo(_taskList)){
		_userStorage.writeStorage(_taskList);
		//_display.something();//confirmation message I haven't coded yet
	}
	else{
		//_display.something();//error message I haven't coded yet
	}
}

void Logic::redo(){
	if(_History.redo(_taskList)){
		_userStorage.writeStorage(_taskList);
		//_display.something();//confirmation message I haven't coded yet
	}
	else{
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