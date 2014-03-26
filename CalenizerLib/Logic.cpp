// Logic.cpp
// v1.2

#include "Logic.h"
#include <assert.h>

const std::string Logic::TASK_DEADLINE = "DEADLINE";
const std::string Logic::TASK_TIMED = "TIMED";
const std::string Logic::TASK_FLOAT = "FLOAT";

const std::string Logic::DISPLAY_ALL = "all";
const std::string Logic::DISPLAY_COMPLETE = "complete";
const std::string Logic::DISPLAY_INCOMPLETE = "incomplete";
const std::string Logic::DISPLAY_TODAY = "today";

const std::string Logic::CMD_ADD = "add";
const std::string Logic::CMD_DELETE = "delete";
const std::string Logic::CMD_DISPLAY = "display";
const std::string Logic::CMD_EDIT = "edit";
const std::string Logic::CMD_EXIT = "exit";
const std::string Logic::CMD_SEARCH = "search";
const std::string Logic::CMD_COMPLETE = "complete";
const std::string Logic::CMD_INCOMPLETE = "incomplete";
const std::string Logic::CMD_UNDO = "undo";
const std::string Logic::CMD_REDO = "redo";
const std::string Logic::CMD_INVALID = "invalid";

/* add
	if (dateTimeIsUnlabelled || (endDate.isNull() && endTime.isNull())){
		//user did not specify if date/time was a start date or an end date
	//	_logic.addTask(descString.toStdString(), startDate, startTime);
	}
	else{
//		_logic.addTask(descString.toStdString(), startDate, startTime, endDate, endTime);
	}

	*/

/* edit
	if (dateTimeIsUnlabelled){
		//user did not specify if date/time was a start date or an end date
		analysedData.setTaskDesc(descString.toStdString());
		analysedData.setStartDate(startDate);
		analysedData.setStartTime(startTime);
		analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
		//_logic.editTask(index, descString.toStdString(), startDate, startTime);

	}
	else{
		analysedData.setTaskDesc(descString.toStdString());
		analysedData.setStartDate(startDate);
		analysedData.setStartTime(startTime);
		analysedData.setEndDate(endDate);
		analysedData.setEndTime(endTime);
		analysedData.setDateTimeUnlabelled(dateTimeIsUnlabelled);
		//_logic.editTask(index, descString.toStdString(), startDate, startTime, endDate, endTime);
	}
*/


Logic::Logic() {
	loadFileContent();
	_currentDisplayType.setCommand(CMD_DISPLAY);
	_currentDisplayType.setDisplayType(DISPLAY_ALL);
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


DisplayOutput Logic::executeUserInput(std::string userInput) {
	AnalysedData analysedData;
	DisplayOutput displayOutput;
	analysedData = _parser.parse(userInput);

	if(analysedData.getCommand() == CMD_ADD) {
		addTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_DELETE) {
		deleteTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_EDIT) {
		editTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_DISPLAY) {
		displayTask(analysedData, displayOutput);
	}

	if(analysedData.getCommand() == CMD_SEARCH) {
		displayTask(analysedData, displayOutput);
	}

	if(analysedData.getCommand() == CMD_COMPLETE) {
		setComplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_INCOMPLETE) {
		setIncomplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_UNDO) {
		undo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_REDO) {
		redo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == CMD_EXIT) {
		displayOutput.setFeedBack(CMD_EXIT);
	}

	if(analysedData.getCommand() == CMD_INVALID) {
		displayOutput.setFeedBack("Invalid command\n");
		displayTask(_currentDisplayType, displayOutput);
	}

	return displayOutput;
}

bool Logic::isValidIndex(int index) {
	if (index >= 1 && index <= _displayList.size()) { 
		return true; 
	} else { 
		return false; 
	}
}

void Logic::editTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	int index = analysedData.getIndex();
	std::string taskDesc = analysedData.getTaskDesc();
	QDate startDate = analysedData.getStartDate();
	QDate endDate = analysedData.getEndDate();
	QTime startTime = analysedData.getStartTime();
	QTime endTime = analysedData.getEndTime();
	DateTime startDateTime;
	startDateTime.setDate(startDate);
	startDateTime.setTime(startTime);
	
	DateTime endDateTime;
	endDateTime.setDate(endDate);
	endDateTime.setTime(endTime);

	if(!isValidIndex(index)) {
		displayOutput.setFeedBack("invalid index\n");
		return;
	}

	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if((*taskToEdit)->getTaskType() == TASK_FLOAT) {
		if(!taskDesc.empty()) {
		(*taskToEdit)->setTaskDesc(taskDesc);
		}
		
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task editted\n");
		return;
	}

	if((*taskToEdit)->getTaskType() == TASK_DEADLINE) {
		if(!taskDesc.empty()) {
			(*taskToEdit)->setTaskDesc(taskDesc);
		}
		if(startDate.isValid() || startTime.isValid()) {
			(*taskToEdit)->setDeadline(startDateTime);
		} else if(endDate.isValid() || endTime.isValid()) {
			(*taskToEdit)->setDeadline(endDateTime);
		}
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task editted\n");
		return;
	}
	
	if((*taskToEdit)->getTaskType() == TASK_TIMED) {
		if(!taskDesc.empty()) {
			(*taskToEdit)->setTaskDesc(taskDesc);
		}
		if(startDate.isValid() || startTime.isValid()) {
			(*taskToEdit)->setDeadline(startDateTime);
		}
		if(endDate.isValid() || endTime.isValid()) {
			(*taskToEdit)->setDeadline(endDateTime);
		}
		
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task editted\n");
		return;
	}

	assert(false);
	return;
}

void Logic::addTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	std::string taskDesc = analysedData.getTaskDesc();
	QDate startDate = analysedData.getStartDate();
	QDate endDate = analysedData.getEndDate();
	QTime startTime = analysedData.getStartTime();
	QTime endTime = analysedData.getEndTime();
	DateTime startDateTime;
	startDateTime.setDate(startDate);
	startDateTime.setTime(startTime);
	
	DateTime endDateTime;
	endDateTime.setDate(endDate);
	endDateTime.setTime(endTime);
	
	if(startDate.isNull() && endDate.isNull() && startTime.isNull() && endTime.isNull()) { // floating task
		TaskFloat* newFloatPtr = new TaskFloat;
		newFloatPtr->setTask(TASK_FLOAT, false, taskDesc);
		_taskList.push_back(newFloatPtr);
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task added\n");
		return;
	}

	if((startDate.isNull() && startTime.isNull())) {
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(TASK_DEADLINE, false, taskDesc, endDateTime);
		_taskList.push_back(newDeadlinePtr);
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task added\n");
		return;
	}

	if((endDate.isNull() && endTime.isNull())) {
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(TASK_DEADLINE, false, taskDesc, startDateTime);
		_taskList.push_back(newDeadlinePtr);
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack("task added\n");
		return;
	}

	TaskTimed* newTimedPtr = new TaskTimed;
	newTimedPtr->setTask(TASK_TIMED, false, taskDesc, startDateTime, endDateTime);
	_taskList.push_back(newTimedPtr);
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	displayOutput.setFeedBack("task added\n");
	return;
}

void Logic::deleteTask(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
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
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		displayOutput.setFeedBack(invalidIndex);
	} else {
		displayOutput.setFeedBack("all tasks deleted\n");
	}

	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::setComplete(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
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
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		displayOutput.setFeedBack(invalidIndex);
	} else {
		displayOutput.setFeedBack("all tasks completed\n");
	}

	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::setIncomplete(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
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
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		displayOutput.setFeedBack(invalidIndex);
	} else {
		displayOutput.setFeedBack("all tasks incompleted\n");
	}

	_userStorage.writeStorage(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::undo(DisplayOutput& displayOutput) {
	Logger& logLogic = Logger::getInstance();

	if(_History.undo(_taskList)){
		_userStorage.writeStorage(_taskList);
		displayOutput.setFeedBack("undo done\n");
	}
	else{
		displayOutput.setFeedBack("undo failed\n");
	}
}

void Logic::redo(DisplayOutput& displayOutput) {
	Logger& logLogic = Logger::getInstance();
	if(_History.redo(_taskList)){
		_userStorage.writeStorage(_taskList);
		displayOutput.setFeedBack("redo done\n");
	}
	else{
		displayOutput.setFeedBack("redo failed\n");
	}
}

std::vector<Task*>::iterator Logic::indexToIterator(int index){
	std::vector<std::vector<Task*>::iterator>::iterator iter = _displayIndexList.begin();
	for(int i=1; i!=index; i++){
		iter++;
	}
	return *iter;
}

void Logic::displayTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	
	if(analysedData.getCommand() == CMD_DISPLAY) {

		if(analysedData.getDisplayType() == DISPLAY_COMPLETE) { // display completed task
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, true);
		}
			
		if(analysedData.getDisplayType() == DISPLAY_INCOMPLETE) { // display incompleted task
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, false);
		}

		if(analysedData.getDisplayType() == DISPLAY_ALL) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList);
		}

		if(analysedData.getDisplayType() == DISPLAY_TODAY) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, QDate::currentDate());
		}
	}

	if(analysedData.getCommand() == CMD_SEARCH) {
		_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, analysedData.getDisplayType());
	}
	
	if(analysedData.getCommand() == CMD_DISPLAY || analysedData.getCommand() == CMD_SEARCH) {
		displayOutput.setFeedBack("displayed all relevant tasks\n");
	}
	displayOutput.displayTasks(_displayList);
	_currentDisplayType.setCommand(analysedData.getCommand());
	_currentDisplayType.setDisplayType(analysedData.getDisplayType());
	
}
