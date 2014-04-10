// Logic.cpp
// v2.3
// changed display string to view, exit string to quit
// added the msg feedback for search
// added sort function
// refactored some code

#include "Logic.h"

Logic::Logic() {
	loadFileContent();
	_currentDisplayType.setCommand(Message::CMD_DISPLAY);
	_currentDisplayType.setDisplayType(Message::DISPLAY_ALL);
}

Logic::~Logic() {
	for(unsigned int i = 0; i < _taskList.size(); i++) {
	delete _taskList[i];
	}
}
	
DisplayOutput Logic::executeUserInput(std::string userInput) {
	AnalysedData analysedData;
	DisplayOutput displayOutput;
	try{
		analysedData = _parser.parse(userInput, _displayList);
		executeCommand(analysedData, displayOutput);
	}
	catch(InvalidDateTimeException &e) {
		displayOutput.setFeedBack(e.what());
		displayTask(_currentDisplayType, displayOutput);
	}
	catch(InvalidTaskIDException &e) {
		displayOutput.setFeedBack(e.what());
		displayTask(_currentDisplayType, displayOutput);
	}
	catch(CannotUndoException &e) {
		displayOutput.setFeedBack(e.what());
		displayTask(_currentDisplayType, displayOutput);
		Logger& logLogic = Logger::getInstance();
		logLogic.addInfoLog(_actionMsg.undoFailureFeedback());
		logLogic.saveLog();
	}
	catch(CannotRedoException &e) {
		displayOutput.setFeedBack(e.what());
		displayTask(_currentDisplayType, displayOutput);
		Logger& logLogic = Logger::getInstance();
		logLogic.addInfoLog(_actionMsg.redoFailureFeedback());
		logLogic.saveLog();
	}
	return displayOutput;
}

void Logic::executeCommand(AnalysedData& analysedData, DisplayOutput& displayOutput) {
		if(analysedData.getCommand() == Message::CMD_ADD) {
		addTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_DELETE) {
		deleteTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_EDIT) {
		editTask(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_DISPLAY) {
		displayTask(analysedData, displayOutput);

		if(analysedData.getDisplayType() == Message::DISPLAY_COMPLETE) {
			displayOutput.setFeedBack(_actionMsg.displayCompleteFeedback());
		}
			
		if(analysedData.getDisplayType() == Message::DISPLAY_INCOMPLETE) {
			displayOutput.setFeedBack(_actionMsg.displayIncompleteFeedback());
		}

		if(analysedData.getDisplayType() == Message::DISPLAY_ALL) {
			displayOutput.setFeedBack(_actionMsg.displayAllFeedback());
		}

		if(analysedData.getDisplayType() == Message::DISPLAY_TODAY) {
			displayOutput.setFeedBack(_actionMsg.displayTodayFeedback());
		}
	}

	if(analysedData.getCommand() == Message::CMD_SEARCH) {
		displayTask(analysedData, displayOutput);
		if(displayOutput.getDisplayStatus()) {
			displayOutput.setFeedBack(_actionMsg.searchSuccessFeedback(analysedData.getDisplayType()));
		} else {
			displayOutput.setFeedBack(_actionMsg.searchFailureFeedback(analysedData.getDisplayType()));
		}
	}

	if(analysedData.getCommand() == Message::CMD_COMPLETE) {
		setComplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_INCOMPLETE) {
		setIncomplete(analysedData, displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_UNDO) {
		undo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_REDO) {
		redo(displayOutput);
		displayTask(_currentDisplayType, displayOutput);
	}

	if(analysedData.getCommand() == Message::CMD_EXIT) {
		displayOutput.setFeedBack(Message::CMD_EXIT);
		exit(0);
	}

	if(analysedData.getCommand() == Message::CMD_INVALID) {
		displayOutput.setFeedBack(_actionMsg.invalidFeedback());
		displayTask(_currentDisplayType, displayOutput);
	}
}

void Logic::addTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	if(!(_dateTimeResolver.resolveAdd(analysedData))) {
		displayOutput.setFeedBack(_actionMsg.invalidDateTimeFeedback());
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

void Logic::editTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	int index = analysedData.getIndex();

	if(!isValidIndex(index)) {
		throw InvalidTaskIDException(_actionMsg.invalidIndexFeedback().c_str());
		return;
	}

	std::vector<Task*>::iterator taskToEdit = indexToIterator(index);

	if(!_dateTimeResolver.resolveEdit(*taskToEdit, analysedData)) {
		displayOutput.setFeedBack(_actionMsg.invalidDateTimeFeedback());
		return;
	} 
		
	_taskEditor.edit(*taskToEdit, analysedData);

	std::string taskDesc= (*taskToEdit)->getTaskDesc();

	sortTaskList();
	_userStorage.writeFile(_taskList);
	_History.saveHistory(_taskList);
	displayOutput.setFeedBack(_actionMsg.editFeedback(taskDesc));
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

void Logic::displayTask(AnalysedData analysedData, DisplayOutput& displayOutput) {
	std::vector<std::string> displayListStatus;
	_displayList.clear();
	_displayIndexList.clear();
	if(analysedData.getCommand() == Message::CMD_DISPLAY) {

		if(analysedData.getDisplayType() == Message::DISPLAY_COMPLETE) { // display completed task
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, true, displayListStatus);
		}
			
		if(analysedData.getDisplayType() == Message::DISPLAY_INCOMPLETE) { // display incompleted task
			_displayStatus = _filter.search(_taskList, _displayList,_displayIndexList, false, displayListStatus);
		}

		if(analysedData.getDisplayType() == Message::DISPLAY_ALL) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, displayListStatus);
		}

		if(analysedData.getDisplayType() == Message::DISPLAY_TODAY) {
			_displayStatus = _filter.search(_taskList, _displayList, _displayIndexList, QDate::currentDate(), displayListStatus);
		}
	}

	if(analysedData.getCommand() == Message::CMD_SEARCH) {
		_displayStatus = _filter.search(_taskList, _displayList,  _displayIndexList, analysedData.getDisplayType(), displayListStatus);
	}

	displayOutput.setDisplayStatus(_displayStatus);
	displayOutput.displayTasks(_displayList);
	displayOutput.setDisplayListStatus(displayListStatus);
	_currentDisplayType.setCommand(analysedData.getCommand());
	_currentDisplayType.setDisplayType(analysedData.getDisplayType());
}

void Logic::undo(DisplayOutput& displayOutput) {
	if(_History.undo(_taskList)){
		sortTaskList();
		_userStorage.writeFile(_taskList);
		displayOutput.setFeedBack(_actionMsg.undoSuccessFeedback());
	}
	else{
		throw CannotUndoException(_actionMsg.undoFailureFeedback().c_str());
	}
}

void Logic::redo(DisplayOutput& displayOutput) {
	if(_History.redo(_taskList)){
		sortTaskList();
		_userStorage.writeFile(_taskList);
		displayOutput.setFeedBack(_actionMsg.redoSuccessFeedback());
	}
	else{
		throw CannotRedoException(_actionMsg.redoFailureFeedback().c_str());
	}
}

std::vector<Task*>::iterator Logic::indexToIterator(int index){
	std::vector<std::vector<Task*>::iterator>::iterator iter = _displayIndexList.begin();
	for(int i=1; i!=index; i++){
		iter++;
	}
	return *iter;
}

bool Logic::isValidIndex(int index) {
	if (index >= 1 && index <= _displayList.size()) { 
		return true; 
	} else { 
		return false; 
	}
}

void Logic::loadFileContent() {
	_taskList.clear();
	sortTaskList();
	_userStorage.loadFile(_taskList);
	_History.saveHistory(_taskList);
}

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
	std::vector<Task*>::iterator topCutoff;
	// find the tasklist vector for the first task which is not overdue
	for(topCutoff = _taskList.begin(); topCutoff != _taskList.end(); topCutoff++){
		if((*topCutoff)->getDeadline() < currentDateTime){
			break;
		}
	}
	std::sort(topCutoff, bottomCutoff, Comparator::sortByStartDate);
	std::sort(_taskList.begin(), _taskList.end(), Comparator::sortByCompleteness);
}

