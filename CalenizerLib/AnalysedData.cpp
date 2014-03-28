// AnalysedData.cpp
// v1.0
// this is an object between the interaction of Logic and Parser

#include "AnalysedData.h"

AnalysedData::AnalysedData() {
}


void AnalysedData::setDateTimeUnlabelled(bool status) {
	_dateTimeIsUnlabelled = status;
}

void AnalysedData::setIndex(int index) {
	_taskIndex = index;
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

void AnalysedData::setDisplayType(std::string displayType) {
	_displayType = displayType;
}

bool AnalysedData::getDateTimeUnlabelled() {
	return _dateTimeIsUnlabelled;
}

std::string AnalysedData::getDisplayType() {
	return _displayType;
}

int AnalysedData::getIndex() {
	return _taskIndex;
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
