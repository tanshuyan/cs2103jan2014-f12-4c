//@author A0101843R

// AnalysedData.cpp

#include "AnalysedData.h"

AnalysedData::AnalysedData() {
	_taskIndex = -1;
	_dateTimeIsUnlabelled = true;
	_dayOfWeek = -1;
}

void AnalysedData::setDateTimeUnlabelled(bool status) {
	_dateTimeIsUnlabelled = status;
}

void AnalysedData::setIndex(int index) {
	_taskIndex = index;
}

void AnalysedData::setDisplayType(std::string displayType) {
	_displayType = displayType;
}

void AnalysedData::setCommand(std::string command) {
	_command = command;
}

void AnalysedData::setTaskDesc(std::string taskDesc) {
	_taskDesc = taskDesc;
}

void AnalysedData::setStartTime(QTime startTime) {
	_startTime = startTime;
}

void AnalysedData::setEndTime(QTime endTime) {
	_endTime = endTime;
}

void AnalysedData::setEndDate(QDate endDate) {
	_endDate = endDate;
}

void AnalysedData::setStartDate(QDate startDate) {
	_startDate = startDate;
}

void AnalysedData::setIndexVector(std::vector<int> index) {
	_index = index;
}

void AnalysedData::setDayOfWeek(int dayOfWeek) {
	_dayOfWeek = dayOfWeek;
}

bool AnalysedData::getDateTimeUnlabelled() {
	return _dateTimeIsUnlabelled;
}

int AnalysedData::getIndex() {
	return _taskIndex;
}

std::string AnalysedData::getDisplayType() {
	return _displayType;
}

std::string AnalysedData::getCommand() {
	return _command;
}

std::string AnalysedData::getTaskDesc() {
	return _taskDesc;
}

QTime AnalysedData::getStartTime() {
	return _startTime;
}

QTime AnalysedData::getEndTime() {
	return _endTime;
}

QDate AnalysedData::getStartDate() {
	return _startDate;
}

QDate AnalysedData::getEndDate() {
	return _endDate;
}

std::vector<int> AnalysedData::getIndexVector() {
	return _index;
}

int AnalysedData::getDayOfWeek() {
	return _dayOfWeek;
}

bool AnalysedData::operator==(AnalysedData other){
	if(other.getTaskDesc() != _taskDesc){
		return false;
	}
	if(other.getCommand() != _command){
		return false;
	}
	if(other.getDisplayType() != _displayType){
		return false;
	}
	if(other.getStartDate() != _startDate){
		return false;
	}
	if(other.getIndex() != _taskIndex){
		return false;
	}
	if(other.getStartTime() != _startTime){
		return false;
	}
	if(other.getEndTime() != _endTime){
		return false;
	}
	if(other.getStartDate() != _startDate){
		return false;
	}
	if(other.getStartDate() != _startDate){
		return false;
	}
	if(other.getEndDate() != _endDate){
		return false;
	}
	if(other.getIndexVector() != _index){
		return false;
	}
	if(other.getDateTimeUnlabelled() != _dateTimeIsUnlabelled){
		return false;
	}
	return true;
}