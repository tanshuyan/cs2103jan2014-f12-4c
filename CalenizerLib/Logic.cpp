// Logic.cpp
// v2.1
// changed display string to view, exit string to quit
// added the msg feedback for search
// added sort function
#include <assert.h>
#include <algorithm>
#include "Logic.h"

Logic::Logic() {
	loadFileContent();
	_currentDisplayType.setCommand(DisplayOutput::CMD_DISPLAY);
	_currentDisplayType.setDisplayType(DisplayOutput::DISPLAY_ALL);
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

	if(analysedData.getCommand() == DisplayOutput::CMD_ADD) {
		addTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_DELETE) {
		deleteTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_EDIT) {
		editTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_DISPLAY) {
		displayTask(analysedData, displayOutput);

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_COMPLETE) { // display completed task
			displayOutput.setFeedBack(_actionMsg.displayCompleteFeedback());
		}
			
		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_INCOMPLETE) { // display incompleted task
			displayOutput.setFeedBack(_actionMsg.displayIncompleteFeedback());
		}

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_ALL) {
			displayOutput.setFeedBack(_actionMsg.displayAllFeedback());
		}

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_TODAY) {
			displayOutput.setFeedBack(_actionMsg.displayTodayFeedback());
		}

		//displayOutput.setFeedBack(_actionMsg.displayAllFeedback());
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_SEARCH) {
		displayTask(analysedData, displayOutput);
		if(displayOutput.getDisplayStatus()) {
			displayOutput.setFeedBack(_actionMsg.searchSuccessFeedback(analysedData.getDisplayType()));
		} else {
			displayOutput.setFeedBack(_actionMsg.searchFailureFeedback(analysedData.getDisplayType()));
		}
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_COMPLETE) {
		setComplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_INCOMPLETE) {
		setIncomplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_UNDO) {
		undo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_REDO) {
		redo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_EXIT) {
		displayOutput.setFeedBack(DisplayOutput::CMD_EXIT);
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_INVALID) {
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
		Task* newFloatPtr = new TaskFloat;
		newFloatPtr->setTask(false, taskDesc);
		_taskList.push_back(newFloatPtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	if((startDate.isNull() && startTime.isNull())) {
		Task* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(false, taskDesc, endDateTime);
		_taskList.push_back(newDeadlinePtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	if((endDate.isNull() && endTime.isNull())) {
		Task* newDeadlinePtr = new TaskDeadline;
		newDeadlinePtr->setTask(false, taskDesc, startDateTime);
		_taskList.push_back(newDeadlinePtr);
		sortTaskList();
		_userStorage.writeFile(_taskList);
		_History.saveHistory(_taskList);
		displayOutput.setFeedBack(_actionMsg.addFeedback(taskDesc));
		return;
	}

	Task* newTimedPtr = new TaskTimed;
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

	int removedIndexCount = 0;
	//std::vector<std::string> removedContents;
	std::string removedContent;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToDelete = indexToIterator(taskIndex);
			removedContent  = (*taskToDelete)->getTaskDesc();
			//removedContents.push_back( (*taskToDelete)->getTaskDesc() );
			removedIndexCount++;
			delete *taskToDelete;
			_taskList.erase(taskToDelete);
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) {
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
		if ( removedIndexCount == 1){
				//std::string taskDesc= removedContent;
				displayOutput.setFeedBack(_actionMsg.deleteFeedback(removedContent));
				//removedContents.pop_back();
		}
		else {
			displayOutput.setFeedBack(_actionMsg.deleteMultipleFeedback(removedIndexCount));
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
	std::string taskCompleted;
	int completeIndexCount = 0;
	//std::vector<std::string> taskCompleted;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToComplete = indexToIterator(taskIndex);
			(*taskToComplete)->setCompleteStatus(true);
			taskCompleted = (*taskToComplete)->getTaskDesc();
			completeIndexCount++;
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) { 
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
			if ( completeIndexCount == 1){
				//std::string taskDesc= removedContent;
				displayOutput.setFeedBack(_actionMsg.completeSuccessFeedback(taskCompleted));
				//removedContents.pop_back();
			}
			else {
				displayOutput.setFeedBack(_actionMsg.completeMultipleSuccessFeedback(completeIndexCount));
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
	std::string taskIncompleted;
	int incompleteIndexCount = 0;
	//std::vector<std::string> taskIncompleted;

	for(unsigned int i = index.size(); i > 0; i--) {
		taskIndex = index[i-1];
		if(isValidIndex(taskIndex)) {
			std::vector<Task*>::iterator taskToIncomplete = indexToIterator(taskIndex);
			(*taskToIncomplete)->setCompleteStatus(false);
			taskIncompleted= (*taskToIncomplete)->getTaskDesc();
			incompleteIndexCount++;
		} else {
			invalidIndex.push_back(taskIndex);
		}
	}
	
	if(!invalidIndex.empty()) {
		displayOutput.setFeedBack(_actionMsg.invalidIndexFeedback());
	} else {
			if ( incompleteIndexCount == 1){
				//std::string taskDesc= removedContent;
				displayOutput.setFeedBack(_actionMsg.incompleteSuccessFeedback(taskIncompleted));
				//removedContents.pop_back();
			}
			else {
				displayOutput.setFeedBack(_actionMsg.incompleteMultipleSuccessFeedback(incompleteIndexCount));
			}
	}

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
}

void Logic::undo(DisplayOutput& displayOutput) {
	Logger& logLogic = Logger::getInstance();

	if(_History.undo(_taskList)){
		sortTaskList();
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
		sortTaskList();
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
	for(topCutoff = _taskList.begin(); topCutoff != _taskList.end(); topCutoff++){
		if((*topCutoff)->getDeadline() < currentDateTime){
			break;
		}
	}
	std::sort(topCutoff, bottomCutoff, Comparator::sortByStartDate);
	std::sort(_taskList.begin(), _taskList.end(), Comparator::sortByCompleteness);
}

void Logic::displayTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	std::vector<std::string> displayListStatus;
	_displayList.clear();
	_displayIndexList.clear();
	if(analysedData.getCommand() == DisplayOutput::CMD_DISPLAY) {

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_COMPLETE) { // display completed task
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, true, displayListStatus);
		}
			
		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_INCOMPLETE) { // display incompleted task
			_displayStatus = _filter.search(_taskList, _displayList,_displayIndexList, false, displayListStatus);
		}

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_ALL) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, displayListStatus);
		}

		if(analysedData.getDisplayType() == DisplayOutput::DISPLAY_TODAY) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, QDate::currentDate(), displayListStatus);
		}
	}

	if(analysedData.getCommand() == DisplayOutput::CMD_SEARCH) {
		_displayStatus = _filter.search(_taskList, _displayList,  _displayIndexList, analysedData.getDisplayType(), displayListStatus);
	}

	displayOutput.setDisplayStatus(_displayStatus);
	displayOutput.displayTasks(_displayList);
	displayOutput.setDisplayListStatus(displayListStatus);
	_currentDisplayType.setCommand(analysedData.getCommand());
	_currentDisplayType.setDisplayType(analysedData.getDisplayType());
}
