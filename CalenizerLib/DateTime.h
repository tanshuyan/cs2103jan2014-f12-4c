//DateTime.h
//v 1.4
//removed guessYear (the dateTimeParser already had a function that did that job)
//added an overload to the constructor

#ifndef DATETIME_H
#define DATETIME_H

#include <QDateTime>
#include <QString>
#include <string>
#include <QRegExp>


class DateTime{
private:
	QDate _date;
	QTime _time;

public:
	DateTime();
	DateTime(QDate, QTime);

	//returns false if date is invalid
	bool setDate(int day, int month, int year);
	//returns false if time is invalid
	bool setTime(int hour, int min);
	bool setDate(QDate);
	bool setTime(QTime);

	QDate getDate();
	QTime getTime();
	
	void setCurrDateTime();

	//returns date in format 16 Jul 2014
	//set bool to "true" if you want the date to display as "Today", "Tomorrow", or "Yesterday"
	std::string dateToString(bool displayTodayAsWord=false);
	//returns day in format Tue
	std::string dayToString();
	//returns time in format 1:09 pm
	std::string timeToString();

	std::string dataToString();
	void dataFromString(std::string data);

	//to sort the dates and check for clashes
	bool operator==(DateTime datetimeToCompare);
	bool operator!=(DateTime datetimeToCompare);
	bool operator<(DateTime datetimeToCompare);
	bool operator>(DateTime datetimeToCompare);

};
#endif