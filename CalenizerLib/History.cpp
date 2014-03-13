// History.cpp

#include "History.h"

History::History(){
}

void History::saveHistory(std::vector<Task*> taskList){
	_prevHistorys.push(_currHistory);
	_currHistory = taskList;
	clearRedo();
}

void History::clearRedo(){
	while (!_nextHistorys.empty()){
		_nextHistorys.pop();
	}
}

bool History::undo(std::vector<Task*> &taskList){
	if(_prevHistorys.empty()){
		return false;
	}
	
	_nextHistorys.push(_currHistory);
	_currHistory = _prevHistorys.top();
	_prevHistorys.pop();

	taskList = _currHistory;
	return true;
}

bool History::redo(std::vector<Task*> &taskList){
	if(_nextHistorys.empty()){
		return false;
	}
	
	_prevHistorys.push(_currHistory);
	_currHistory = _nextHistorys.top();
	_nextHistorys.pop();

	taskList = _currHistory;
	return true;
}