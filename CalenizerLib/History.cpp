// History.cpp
// v1.1
// changed 
#include "History.h"

const std::string History::TASK_DEADLINE = "DEADLINE";
const std::string History::TASK_TIMED = "TIMED";
const std::string History::TASK_FLOAT = "FLOAT";


History::History(){
}

void History::saveHistory(std::vector<Task*> &taskList){

	// to create a deep copy of the vector <Task*> 
	_currHistory.clear();
	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++) {
		if((*iter)->getTaskType() == TASK_FLOAT) { // create a new floating task
			std::string temp;
			TaskFloat* newFloatPtr = new TaskFloat;
			temp = (*iter)->taskDetailsToString();
			std::istringstream input(temp);
			newFloatPtr->stringToTask(temp);
			_currHistory.push_back(newFloatPtr);
		
		} else if ((*iter)->getTaskType() == TASK_DEADLINE) { // create a new deadline task	
			std::string temp;
			TaskDeadline* newDeadlinePtr = new TaskDeadline;
			temp = (*iter)->taskDetailsToString();
			newDeadlinePtr->stringToTask(temp);
			_currHistory.push_back(newDeadlinePtr);

		} else if ((*iter)->getTaskType() == TASK_TIMED) { // create a new deadline task
			std::string temp;
			TaskTimed* newTimedPtr = new TaskTimed;
			temp = (*iter)->taskDetailsToString();
			newTimedPtr->stringToTask(temp);
			_currHistory.push_back(newTimedPtr);
		}
	}
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

bool History::undo(std::vector<Task*> &taskList){
	if(_prevHistorys.size()-1 == 0){
		return false;
	}
	
	_nextHistorys.push(_prevHistorys.top()); // the _currHistory and top of _prevHistory are the same because of the nature of saveHistory 
	_prevHistorys.pop();
	_currHistory = _prevHistorys.top(); 
	taskList = _currHistory;
	return true;
}

bool History::redo(std::vector<Task*> &taskList){
	if(_nextHistorys.empty()){
		return false;
	}
	
	_prevHistorys.push(_nextHistorys.top());
	_currHistory = _nextHistorys.top();
	_nextHistorys.pop();
	taskList = _currHistory;
	return true;
}