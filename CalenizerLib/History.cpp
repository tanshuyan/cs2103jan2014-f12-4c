// History.cpp
// v1.2
// changed the function for deep copies to taskDetailsToString()
// fixed a bug in undo, deep copies
// modularise functions
#include "History.h"

History::History(){
}

void History::saveHistory(std::vector<Task*> &taskList){

	// to create a deep copy of the vector <Task*> 
	_currHistory.clear();
	createDeepCopy(taskList, _currHistory);
	_prevHistorys.push(_currHistory);
	clearRedo();
}

void History::clearRedo(){
	while (!_nextHistorys.empty()){
		_deleteTaskList = _nextHistorys.top();
		for(unsigned int i = 0; i < _deleteTaskList.size(); i++) {
			delete _deleteTaskList[i];
		}
		_nextHistorys.pop();
		_deleteTaskList.clear();
	}
}

void History::createDeepCopy(std::vector<Task*> &taskList, std::vector<Task*> &copyList) {

		for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++) {
		if((*iter)->getTaskType() == TaskFloat::TASK_FLOAT) { // create a new floating task
			std::string temp;
			Task* newFloatPtr = new TaskFloat;
			temp = (*iter)->taskDetailsToString();
			newFloatPtr->stringToTask(temp);
			copyList.push_back(newFloatPtr);
		
		} else if ((*iter)->getTaskType() == TaskDeadline::TASK_DEADLINE) { // create a new deadline task	
			std::string temp;
			Task* newDeadlinePtr = new TaskDeadline;
			temp = (*iter)->taskDetailsToString();
			newDeadlinePtr->stringToTask(temp);
			copyList.push_back(newDeadlinePtr);

		} else if ((*iter)->getTaskType() == TaskTimed::TASK_TIMED) { // create a new deadline task
			std::string temp;
			Task* newTimedPtr = new TaskTimed;
			temp = (*iter)->taskDetailsToString();
			newTimedPtr->stringToTask(temp);
			copyList.push_back(newTimedPtr);
		}
	}
}

bool History::undo(std::vector<Task*> &taskList){
	if(_prevHistorys.size() == 1){
		return false;
	}
	
	_nextHistorys.push(_prevHistorys.top()); // the _currHistory and top of _prevHistory are the same because of the nature of saveHistory 
	_prevHistorys.pop();
	_currHistory = _prevHistorys.top(); 
	std::vector<Task*>::iterator iter;
	for(iter = taskList.begin(); iter != taskList.end(); iter++) {
		delete (*iter);
	}
	taskList.clear();
	createDeepCopy(_currHistory, taskList);
	return true;
}

bool History::redo(std::vector<Task*> &taskList){
	if(_nextHistorys.empty()){
		return false;
	}
	
	_prevHistorys.push(_nextHistorys.top());
	_currHistory = _nextHistorys.top();
	_nextHistorys.pop();
	std::vector<Task*>::iterator iter;
	for(iter = taskList.begin(); iter != taskList.end(); iter++) {
		delete (*iter);
	}
	taskList.clear();
	createDeepCopy(_currHistory, taskList);
	return true;
}