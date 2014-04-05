//AnalysedData.h
// v1.1
// Added == operator for unit test purposes
#ifndef ANALYSEDDATA_H
#define ANALYSEDDATA_H

#include "DateTime.h"
#include <vector>
#include <string>

class AnalysedData{
private:
	std::string _taskDesc;
	std::string _command;
	std::string _displayType;
	int _taskIndex;
	QTime _startTime;
	QTime _endTime;
	QDate _startDate;
	QDate _endDate;
	std::vector<int> _index;
	bool _dateTimeIsUnlabelled;

public:
	AnalysedData();

	void setDateTimeUnlabelled(bool);
	void setIndex(int);
	void setDisplayType(std::string);
	void setCommand(std::string);
	void setTaskDesc(std::string);
	void setStartTime(QTime);
	void setEndTime(QTime);
	void setEndDate(QDate);
	void setStartDate(QDate);
	void setIndexVector(std::vector<int>);

	bool getDateTimeUnlabelled();
	int getIndex();
	std::string getDisplayType();
	std::string getCommand();
	std::string getTaskDesc();
	QTime getStartTime();
	QTime getEndTime();
	QDate getStartDate();
	QDate getEndDate();
	std::vector<int> getIndexVector();

	bool operator==(AnalysedData other);

};
#endif