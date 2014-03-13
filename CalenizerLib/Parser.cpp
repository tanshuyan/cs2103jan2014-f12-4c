#include "Parser.h"
//#include "Logic.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

const std::string Parser::MSG_INVALID = "Invalid command.\n";

//display msg
const std::string Parser::MSG_DISPLAYCOM = "displayed completed tasks";
const std::string Parser::MSG_DISPLAYINCOM = "displayed incompleted tasks";
const std::string Parser::MSG_DISPLAYTODAY = "displayed today tasks";

//search msg
const std::string Parser::MSG_SEARCH = "search completed";
//delete msg
const std::string Parser::MSG_DELETE = "all indicated tasks deleted";
//complete msg
const std::string Parser::MSG_COMPLETE = "all indicated tasks completed";
//undo msg
const std::string Parser::MSG_UNDO = "undo last action";
//redo msg
const std::string Parser::MSG_REDO = "redo last undo";

const std::string Parser::MSG_ADD = "task has been added";

const std::string Parser::MSG_EDIT = "task has been added";

const std::string Parser::CMD_ADD = "add";
const std::string Parser::CMD_EDIT = "edit";
const std::string Parser::CMD_DELETE = "delete";
const std::string Parser::CMD_DISPLAY = "display";
const std::string Parser::CMD_EXIT = "exit";
const std::string Parser::CMD_SEARCH = "search";
const std::string Parser::CMD_COMPLETE = "complete";
const std::string Parser::CMD_UNDO = "undo";
const std::string Parser::CMD_REDO = "redo";
	
const std::string Parser::KEYWORD_COMPLETE = "complete";
const std::string Parser::KEYWORD_INCOMPLETE = "incomplete";
const std::string Parser::KEYWORD_TODAY = "today";

// for timed tasks
const std::string Parser::KEYWORD_FROM = "from";
const std::string Parser::KEYWORD_TO = "to";

// for deadline tasks
const std::string Parser::KEYWORD_ON = "on";
const std::string Parser::KEYWORD_BY = "by";
const std::string Parser::KEYWORD_AT = "at";

// for edit
const std::string Parser::KEYWORD_START = "start";
const std::string Parser::KEYWORD_END = "end";

Parser::Parser() {
}

Parser::COMMAND_TYPE Parser::getCommand(std::string command) {
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
	} else {
		return COMMAND_TYPE::INVALID;
	}
}


std::string Parser::executeUserInput(std::string userInput) {
	userInput = toLower(userInput);
	std::istringstream input(userInput);
	std::string command;
	std::string dummy;
	input >> command; // the first word is always a command
	std::getline(input, dummy, ' '); // trim whitespace 
	std::string commandStatus;
	switch(getCommand(command)) {

	case ADD: {
		commandStatus = addCMD(input.str());		
		break;
	}

	case DELETE: {
		commandStatus = deleteCMD(input.str());
		break;
	}

	case EDIT: {
		commandStatus = editCMD(input.str());
		break;
			   }
	
	case SEARCH: {
		commandStatus = searchCMD(input.str());
		break;
				 }

	case DISPLAY: {
		commandStatus = displayCMD(input.str());
		break;
				 }

	case COMPLETE: {
		commandStatus = completeCMD(input.str());
		break;
				   }

	case UNDO: {
		commandStatus = undoCMD();
		break;
			   }

	case REDO: {
		commandStatus = redoCMD();
		break;
			   }

	case EXIT: {
		commandStatus = CMD_EDIT;
		break;
			   }

	case INVALID: {
		commandStatus = MSG_INVALID;
		break;
				  }
	} // end switch block

	return commandStatus;
}


std::string Parser::undoCMD() {
	// Logic::undo();
	return MSG_UNDO;
}

std::string Parser::redoCMD() {
	// Logic::redo();
	return MSG_REDO;
}


std::string Parser::searchCMD(std::string userInput) {
	std::istringstream input(userInput);
	std::string searchTerm;
	input >> searchTerm;
	while(!input.eof()) {
	//	Logic::searchTasks(searchTerm);
		input >> searchTerm;
	}
	return MSG_SEARCH;
}

std::string Parser::displayCMD(std::string userInput) {
	std::istringstream input(userInput);
	std::string displayType;
	input >> displayType;
	if (displayType == KEYWORD_COMPLETE) {
		//Logic::getCompleteTasks();
		return MSG_DISPLAYCOM;
	} else if (displayType == KEYWORD_INCOMPLETE) {
		//Logic::getIncompleteTasks();
		return MSG_DISPLAYINCOM;
	} else if(displayType == KEYWORD_TODAY) {
		//Logic::getTodayTasks();
		return MSG_DISPLAYTODAY;
	} else {
		return MSG_INVALID;
	}
}

std::string Parser::completeCMD(std::string userInput) {
	getValidIndex(userInput);
	for(unsigned int i =_validIndex.size(); i > 0; i--) {
		//Logic::toggleComplete(_validIndex[i-1]);
	}

	if(!_invalidIndex.empty()) {// have invalid index
		return invalidIndexMsg();
	} else {
		return MSG_COMPLETE;
	}
	
}

std::string Parser::deleteCMD(std::string userInput) {
	getValidIndex(userInput);
	for(unsigned int i =_validIndex.size(); i > 0; i--) { 
		//Logic::deleteTask(_validIndex[i-1]);
	}

	if(!_invalidIndex.empty()) {// have invalid index
		return invalidIndexMsg();
	} else {
		return MSG_DELETE;
	}
	
}

std::string Parser::invalidIndexMsg() {
	std::ostringstream invalidIndexOuput;
	invalidIndexOuput << "Index ";
	for(unsigned int i = 0; i < _invalidIndex.size(); i++) {
		invalidIndexOuput << _invalidIndex[i];
		if(i == (_invalidIndex.size() -1)) {
			invalidIndexOuput << " cannot be found.\n";
		} else {
			invalidIndexOuput << ", ";
		}
	}

	return invalidIndexOuput.str();
}

void Parser::getValidIndex(std::string userInput) {
	_validIndex.clear();
	_invalidIndex.clear();
	int commaPos = userInput.find_first_of(",");
	int index;
	if(commaPos == std::string::npos) { // there is no comma, only 1 task
		index = convertToIndex(userInput);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
	} else { // more than 1 index // assumes that each index is seperated by a ","
		while(commaPos != std::string::npos) {
		std::string prevString = userInput.substr(0, commaPos);
		userInput = userInput.substr(commaPos+1, userInput.size()-1);
		index = convertToIndex(prevString);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
		commaPos = userInput.find_first_of(",");
		}
		
		index = convertToIndex(userInput);
		if(isValidIndex(index)) {
			_validIndex.push_back(index);
		} else {
			_invalidIndex.push_back(index);
		}
	}
	std::sort(_validIndex.begin(), _validIndex.end()); // sorts the valid index by ascending order
}

int Parser::convertToIndex(std::string userInput) {
	std::istringstream input(userInput);
	int index;
	input >> index;
	return index;
}

bool Parser::isValidIndex(int index) {
	if (index >= 1 /*&& index <= Display::getDisplaySize()*/) { 
		return true; 
	} else { 
		return false; 
	}
}

std::string Parser::toLower(std::string userInput) {
		for(int i = 0; i < (int) userInput.size(); i++){
		userInput[i] = tolower(userInput[i]);
	}
		return userInput;
}



// from here onward, there is a need to rework and user regex for better parser


std::string Parser::editCMD(std::string userInput) {
	std::istringstream input(userInput);
	int index;
	std::string remainUserInput;
	input >> index;
	if(isValidIndex(index)) { // index is valid
		std::getline(input, remainUserInput, ' '); // trim whitespace
		std::getline(input,remainUserInput);

		int keywordStart;
		int keywordEnd;

		keywordStart = remainUserInput.rfind(KEYWORD_START);
		keywordEnd = remainUserInput.rfind(KEYWORD_END);
	
		if(keywordStart == std::string::npos) {
			if(keywordEnd == std::string::npos) { // change task desc
				// Logic::editTask(index, remainUserInput);
				return MSG_EDIT;
			} else { // start is not present, end is present
				if(keywordEnd == 0) {// end is the first word, only changing endDate
					std::string endDate;
					endDate = remainUserInput.substr(keywordEnd + 4, remainUserInput.size()-1);
					//_endDate = setDate(endDate);
					// Logic::editTask(index, _endDate); // editTask need to take in the index and check if its floating task, if it is, then it need to be deleted and a deadline task to be recreated
					return MSG_EDIT;
				} else { 
					if(keywordEnd != (remainUserInput.size() -3)) { // will edit taskdesc and enddate as end isnt the last word
					std::string endDate;
					std::string taskDesc;
					taskDesc = remainUserInput.substr(0, keywordEnd -1);
					endDate = remainUserInput.substr(keywordEnd + 4, remainUserInput.size()-1);
					//_endDate = setDate(endDate);
					// Logic::editTask(index, taskDesc, _endDate);
					return MSG_EDIT;
				} else { // end is the lastword, edit taskdesc only
					//Logic::editTask(index, remainUserInput; 
					return MSG_EDIT;
					}
			}
			}
		}
		else { // start is present, not compared with end yet
			if(keywordEnd == std::string::npos) { // end isnt present
				if(keywordStart == 0) { // only changing startDate
					std::string startDate;
					startDate = remainUserInput.substr(keywordStart + 6, remainUserInput.size()-1);
					//_startDate = setDate(startDate);
					// Logic::editTask(index, _startDate); // editTask need to check if its floating task or deadline task, if it is, then it need to be deleted and create a new timed task
					return MSG_EDIT;
				} else { // will edit taskdesc also
					if(keywordStart != (remainUserInput.size() - 5)) {
					std::string taskDesc;
					std::string startDate;
					startDate = remainUserInput.substr(keywordStart + 6, remainUserInput.size()-1);
					taskDesc = remainUserInput.substr(0, keywordStart -1);
					//_startDate = setDate(startDate);
					// Logic::editTask(index, taskDesc, _startDate); // need to check also
					return MSG_EDIT;
					} else { // start is the last word == change taskDesc
						// Logic::editTask(index, remainUserInput);
						return MSG_EDIT;
					}
				}
			} else { // both start and end are present
				if(keywordStart == 0) { // start is at the beginning 
					if( (keywordStart < keywordEnd) && (keywordEnd != remainUserInput.size() -3)) { // end is not the last word
						std::string startDate;
						std::string endDate; 
						startDate = remainUserInput.substr(keywordStart +6, keywordEnd-keywordStart-6);
						endDate = remainUserInput.substr(keywordEnd+4, remainUserInput.size()-1);
						//_startDate = setDate(startDate);
						//_endDate = setDate(startDate);
						//Logic::editTask(index, _startDate, _endDate); // need to check for respectively task type..
						return MSG_EDIT;
					} else { // end comes before start / end is last word, edit taskdesc
						//Logic::editTask(index, remainUserInput);
						return MSG_EDIT;
					}
				} else { // start is not the starting word, edit task desc also
					if( (keywordStart < keywordEnd) && (keywordEnd != remainUserInput.size() -3)) { // end is not the last word
						std::string taskDesc;
						std::string startDate;
						std::string endDate;
						taskDesc = remainUserInput.substr(0, keywordStart-1); 
						startDate = remainUserInput.substr(keywordStart +6, keywordEnd-keywordStart-6);
						endDate = remainUserInput.substr(keywordEnd+4, remainUserInput.size()-1);
						//_startDate = setDate(startDate);
						//_endDate = setDate(startDate);
						// Logic::editTask(index, taskDesc, _startDate, _endDate);
						return MSG_EDIT;
					} else { // end is the last word / end comes before start / edit taskdesc
						//Logic::editTask(index, remainUserInput);
						return MSG_EDIT;
					}
				}
			}

		}
	} else {
		return invalidIndexMsg();
	}
	}



std::string Parser::addCMD(std::string userInput) {
	_taskDesc.clear();
	int i = 1;
	if(isTimedTask(userInput)) {
		// _startDate = setDate(_taskDesc[i];
		// _endDate = setDate(_taskDesc[i+1];
		// Logic::addTimedTask(_taskDesc[i-1], _startDate, _endDate);
		return MSG_ADD;
	} else if(isDeadlineTask(userInput)) {
		if(_taskDesc.size() == 3) {
		// _endDate = setDate(_taskDesc[i];
		// _endTime = setDate(_taskDesc[i+1];
		// Logic::addDeadlineTask(_taskDesc[i-1], _endDate, _endTime);
		return MSG_ADD;
		} else if(_taskDesc.size() == 2) {
			// _endDate = setDate(_taskDesc[i];
			// Logic::addDeadlineTask(_taskDesc[i-1], _endDate);
		return MSG_ADD;
		}
	} else {
		// Logic::addFloatingTask(userInput);
		return MSG_ADD;
	}

}

bool Parser::isDeadlineTask(std::string userInput) {
	int keywordOn;
	int keywordBy;
	int keywordAt;

	keywordOn = userInput.rfind(KEYWORD_ON);
	keywordBy = userInput.rfind(KEYWORD_BY);
	keywordAt = userInput.rfind(KEYWORD_AT);

	if(keywordOn == std::string::npos) { // on not there
		if(keywordBy == std::string::npos) { // by not there
			if(keywordAt == std::string::npos) { // at not there
				return false;
			} else { // on and by not there, at is there format at _____
				if(keywordAt != (userInput.size()-2)) {
				std::string taskDesc;
				std::string endDate;
				taskDesc = userInput.substr(0, keywordAt - 1);
				endDate = userInput.substr(keywordAt + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				return true;
				} else {
					return false;
				}
			}
		} else { // on not there, by is there, at not compared yet
			if((keywordBy < keywordAt) && (keywordAt!= (userInput.size()-2))) {// by comes before at, at is present format by ____ at _____
				std::string taskDesc;
				std::string endDate;
				taskDesc = userInput.substr(0, keywordAt - 1);
				endDate = userInput.substr(keywordAt + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				return true;
			} else { // on not there, by is there, at is not present or before by format by____
				if(keywordBy != (userInput.size()-2)) {
				std::string taskDesc;
				std::string endDate;
				taskDesc = userInput.substr(0, keywordBy - 1);
				endDate = userInput.substr(keywordBy + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				return true;
				} else {
						return false;
					}
				}
			} 
	}else { // on is there, not compared with by or at
			if((keywordOn > keywordAt) && (keywordOn > keywordBy) && (keywordOn != (userInput.size()-2))) { // on is the last occurence format on ____
				std::string taskDesc;
				std::string endDate;
				taskDesc = userInput.substr(0, keywordOn - 1);
				endDate = userInput.substr(keywordOn + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				return true;
			} else if((keywordOn < keywordAt) && (keywordAt > keywordBy) && (keywordOn > keywordBy) && (keywordAt != (userInput.size()-2))) { // format is on ___ at ____
				std::string taskDesc;
				std::string endDate;
				std::string endTime;
				taskDesc = userInput.substr(0, keywordOn - 1);
				endDate = userInput.substr(keywordOn + 3, keywordAt-keywordOn-4);
				endTime = userInput.substr(keywordAt + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				_taskDesc.push_back(endTime);
				return true;
			} else if((keywordOn < keywordBy) && (keywordBy > keywordAt) && (keywordOn > keywordAt) && (keywordBy != (userInput.size()-2))) { // format is on ___ by ____
				std::string taskDesc;
				std::string endDate;
				std::string endTime;
				taskDesc = userInput.substr(0, keywordOn - 1);
				endDate = userInput.substr(keywordOn + 3, keywordBy-keywordOn-4);
				endTime = userInput.substr(keywordBy + 3, userInput.size()-1);
				_taskDesc.push_back(taskDesc);
				_taskDesc.push_back(endDate);
				_taskDesc.push_back(endTime);
				return true;
			} else { // none of the format
					return false;
				}
	}

}


bool Parser::isTimedTask(std::string userInput) {
	int keywordTo;
	int keywordFrom;
	keywordFrom = userInput.rfind(KEYWORD_FROM);
	keywordTo = userInput.rfind(KEYWORD_TO);

	if(keywordFrom == std::string::npos ||keywordTo == std::string::npos || keywordFrom <= keywordTo) {
		return false;
	} else {
		if(keywordTo != (userInput.size()-2)) { // to is not the last word
		std::string startDate;
		std::string endDate;
		std::string taskDesc;
		taskDesc = userInput.substr(0, keywordFrom - 1); // from beginning to before " from "
		startDate =userInput.substr(keywordFrom + 5, keywordTo - keywordFrom - 6); // from between "from " to before "to"
		endDate = userInput.substr(keywordTo + 3, userInput.size()-1); // from after "to " to end of string
		_taskDesc.push_back(taskDesc);
		_taskDesc.push_back(startDate);
		_taskDesc.push_back(endDate);
		return true;
		}
		else {
			return false;
		}
	}
}
