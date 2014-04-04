// Logic.cpp
// v2.1
// changed display string to view, exit string to quit
// added the msg feedback for search
// added sort function
#include <assert.h>
#include <algorithm>
#include "Logic.h"

const std::string Logic::TASK_DEADLINE = "DEADLINE";
const std::string Logic::TASK_TIMED = "TIMED";
const std::string Logic::TASK_FLOAT = "FLOAT";

const std::string Logic::DISPLAY_ALL = "all";
const std::string Logic::DISPLAY_COMPLETE = "complete";
const std::string Logic::DISPLAY_INCOMPLETE = "incomplete";
const std::string Logic::DISPLAY_TODAY = "today";

const std::string Logic::CMD_ADD = "add";
const std::string Logic::CMD_DELETE = "delete";
const std::string Logic::CMD_DISPLAY = "view";
const std::string Logic::CMD_EDIT = "edit";
const std::string Logic::CMD_EXIT = "quit";
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
		if(displayOutput.getDisplayStatus()) {
			displayOutput.setFeedBack(_actionMsg.searchSuccessFeedback(analysedData.getDisplayType()));
		} else {
			displayOutput.setFeedBack(_actionMsg.searchFailureFeedback(analysedData.getDisplayType()));
		}
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
		displayOutput.setFeedBack(_actionMsg.invalidFeedback());
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

	if(!isValidIndex(index)) {
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
		return;
	}

	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if(!_dateTimeResolver.resolveEdit(*taskToEdit, analysedData)) {
		displayOutput.setFeedBack("input order of start and end date is wrong\n");
		return;
	} 
		
	_taskEditor.edit(*taskToEdit, analysedData);

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	displayOutput.setFeedBack(_actionMsg.editFeedback(analysedData.getTaskDesc()));
	return;
/*		return;
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
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.editFeedback(taskDesc));
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

		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.editFeedback(taskDesc));
		return;
	}

	assert(false);
	*/
}

void Logic::addTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	if(!(_dateTimeResolver.resolveAdd(analysedData))) {
		displayOutput.setFeedBack("input order of start and end date is wrong\n");
		return;
	} 

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
		newFloatPtr->setTask(false, taskDesc);
		_taskList.push_back(newFloatPtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	if((startDate.isNull() && startTime.isNull())) {
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(false, taskDesc, endDateTime);
		_taskList.push_back(newDeadlinePtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	if((endDate.isNull() && endTime.isNull())) {
		TaskDeadline* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(false, taskDesc, startDateTime);
		_taskList.push_back(newDeadlinePtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	TaskTimed* newTimedPtr = new TaskTimed;
	newTimedPtr->setTask(false, taskDesc, startDateTime, endDateTime);
	_taskList.push_back(newTimedPtr);
	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
	return;
}

void Logic::deleteTask(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
	std::vector<int> invalidIndex;

	std::vector<std::string> removedContents;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToDelete = indexToIterator(taskIndex);

			removedContents.push_back( (*taskToDelete)->getTaskDesc() );

			delete *taskToDelete;
			_taskList.erase(taskToDelete);
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		//displayOutput.setFeedBack(invalidIndex);
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
		//displayOutput.setFeedBack(_actionMsg.deleteFeedback("lalalaIWANTTOSLEEPALREADY"));
		while( removedContents.size() != 0)
		{
			std::string taskDesc= removedContents[0];
			displayOutput.setFeedBack(_actionMsg.deleteFeedback(taskDesc));
			removedContents.pop_back();
		}
	}

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	return;
}

void Logic::setComplete(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
	std::vector<int> invalidIndex;

	std::vector<std::string> taskCompleted;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToComplete = indexToIterator(taskIndex);
			(*taskToComplete)->setCompleteStatus(true);
			taskCompleted.push_back( (*taskToComplete)->getTaskDesc() );
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		//displayOutput.setFeedBack(invalidIndex);
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
		//displayOutput.setFeedBack(_actionMsg.completeSuccessFeedback("lalalaIWANTTOSLEEPALREADY"));

		while( taskCompleted.size() != 0)
		{
			std::string taskDesc= taskCompleted[0];
			displayOutput.setFeedBack(_actionMsg.completeSuccessFeedback(taskDesc));
			taskCompleted.pop_back();
		}

	}

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::setIncomplete(AnalysedData analysedData, DisplayOutput& displayOutput){
	int taskIndex;
	std::vector<int> index;
	index = analysedData.getIndexVector();
	std::vector<int> invalidIndex;

	std::vector<std::string> taskIncompleted;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToIncomplete = indexToIterator(taskIndex);
			(*taskToIncomplete)->setCompleteStatus(false);
			taskIncompleted.push_back( (*taskToIncomplete)->getTaskDesc() );
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) { // invalid tasks inputted
		//displayOutput.setFeedBack(invalidIndex);
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
		//displayOutput.setFeedBack(_actionMsg.incompleteSuccessFeedback("lalalaIWANTTOSLEEPALREADY"));

		while( taskIncompleted.size() != 0)
		{
			std::string taskDesc= taskIncompleted[0];
			displayOutput.setFeedBack(_actionMsg.incompleteSuccessFeedback(taskDesc));
			taskIncompleted.pop_back();
		}

	}

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::undo(DisplayOutput& displayOutput) {
	Logger& logLogic = Logger::getInstance();

	if(_History.undo(_taskList)){
		_userStorage.writeFile(_taskList);
		displayOutput.setFeedBack(_actionMsg.undoSuccessFeedback());
	}
	else{
		displayOutput.setFeedBack(_actionMsg.undoFailureFeedback());
	}
}

void Logic::redo(DisplayOutput& displayOutput) {
	Logger& logLogic = Logger::getInstance();
	if(_History.redo(_taskList)){
		_userStorage.writeFile(_taskList);
		displayOutput.setFeedBack(_actionMsg.redoSuccessFeedback());
	}
	else{
		displayOutput.setFeedBack(_actionMsg.undoFailureFeedback());
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
void Logic::mergeSortedList(std::vector<Task*> &sortedDisplayList, std::vector<Task*> &timedList, std::vector<Task*> &deadlineList, std::vector<Task*> &floatList) {
	std::vector<Task*>::iterator timedIter = timedList.begin();
	std::vector<Task*>::iterator deadlineIter = deadlineList.begin();
	std::vector<Task*>::iterator floatIter = floatList.begin();
	while(timedIter != timedList.end() && deadlineIter != deadlineList.end()) {
		if((*timedIter)->getStartDate() < (*deadlineIter)->getDeadline()) { // timed task started earlier than deadline task
			sortedDisplayList.push_back(*timedIter);
			timedIter++;
		} else {
			sortedDisplayList.push_back(*deadlineIter);
			deadlineIter++;
		}
	}
	while(timedIter != timedList.end()) {
		sortedDisplayList.push_back(*timedIter);
			timedIter++;
	}
	while(deadlineIter != deadlineList.end()) {
		sortedDisplayList.push_back(*deadlineIter);
		deadlineIter++;
	}
	while(floatIter != floatList.end()) {
		sortedDisplayList.push_back(*floatIter);
		floatIter++;
	}
}
*/
/*
void Logic::orderSortedList(std::vector<Task*> &sortedTaskList, std::vector<Task*> &sortedList) {
	std::vector<Task*>::iterator iter;
	sortedTaskList.clear();
	for(iter = sortedList.begin(); iter!=sortedList.end(); iter++) { 
		if((*iter)->getCompleteStatus() == false) { 
			sortedTaskList.push_back(*iter);
		}
	}
	// pushes the remaining completed tasks to the back of vector in sorted order
	for(iter = sortedList.begin(); iter!=sortedList.end(); iter++) { 
		if((*iter)->getCompleteStatus() == true) { 
			sortedTaskList.push_back(*iter);
		}
	}
}
*/

//This could be a new class? sorter or something
void Logic::sortTaskList() {

	std::sort(_taskList.begin(), _taskList.end(), Comparator::sortByTaskType);
	//Everything from bottomCutoff onwards are floating tasks
	std::vector<Task*>::iterator bottomCutoff;
	for(bottomCutoff = _taskList.begin(); bottomCutoff != _taskList.end(); bottomCutoff++){
		if((*bottomCutoff)->getTaskType() == TaskFloat::TASK_FLOAT){
			break;
		}
	}
	std::sort(_taskList.begin(), bottomCutoff, Comparator::sortByEndDate);
	DateTime currentDateTime;
	currentDateTime.setCurrDateTime();
	//Everything before topCutoff are overdue tasks
	std::vector<Task*>::iterator topCutoff = _taskList.begin();
	// find the tasklist vector for the first task which is not overdue
	while(topCutoff != _taskList.end() && (*topCutoff)->getDeadline() < currentDateTime) {
		topCutoff++;
	}
	std::sort(topCutoff, bottomCutoff, Comparator::sortByStartDate);
	std::sort(_taskList.begin(), _taskList.end(), Comparator::sortByCompleteness);
}

void Logic::displayTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	std::vector<std::string> displayListStatus;
	_displayList.clear();
	_displayIndexList.clear();
	if(analysedData.getCommand() == CMD_DISPLAY) {

		if(analysedData.getDisplayType() == DISPLAY_COMPLETE) { // display completed task
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, true, displayListStatus);
		}
			
		if(analysedData.getDisplayType() == DISPLAY_INCOMPLETE) { // display incompleted task
			_displayStatus = _filter.search(_taskList, _displayList,_displayIndexList, false, displayListStatus);
		}

		if(analysedData.getDisplayType() == DISPLAY_ALL) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, displayListStatus);
		}

		if(analysedData.getDisplayType() == DISPLAY_TODAY) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, QDate::currentDate(), displayListStatus);
		}
	}

	if(analysedData.getCommand() == CMD_SEARCH) {
		_displayStatus = _filter.search(_taskList, _displayList,  _displayIndexList, analysedData.getDisplayType(), displayListStatus);
	}

	displayOutput.setDisplayStatus(_displayStatus);
	displayOutput.displayTasks(_displayList);
	displayOutput.setDisplayListStatus(displayListStatus);
	_currentDisplayType.setCommand(analysedData.getCommand());
	_currentDisplayType.setDisplayType(analysedData.getDisplayType());
}
