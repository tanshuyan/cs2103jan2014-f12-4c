//AnalysedData.h

#ifndef ANALYSEDDATA_H
#define ANALYSEDDATA_H

#include <vector>
#include <string>
#include "DateTime.h"

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
	int _dayOfWeek;

public:
	AnalysedData();

	void setDateTimeUnlabelled(bool status);
	void setIndex(int index);
	void setDisplayType(std::string displayType);
	void setCommand(std::string command);
	void setTaskDesc(std::string taskDesc);
	void setStartTime(QTime startTime);
	void setEndTime(QTime endTime);
	void setEndDate(QDate endDate);
	void setStartDate(QDate startDate);
	void setIndexVector(std::vector<int> index);
	void setDayOfWeek(int dayOfWeek);

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
	int getDayOfWeek();

	bool operator==(AnalysedData other);
};
#endif