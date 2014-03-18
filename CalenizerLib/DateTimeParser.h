//DateTimeParser.h
//v 1.5

#ifndef DATETIMEPARSER_H
#define DATETIMEPARSER_H

#include <QDateTime>
#include <QString>
#include <string>
#include <QRegExp>
#include "DateTime.h"

//All functions return false if any error occurs
class DateTimeParser{
private:
	QDate _date;
	QTime _time;
	
	static QRegExp rxEmpty;
	static QRegExp rxOn;

	static QRegExp rxHourMinAP;
	static QRegExp rxHourAP;
	static QRegExp rxHourColMin;
	static QRegExp rxAtHourMin;

	static QRegExp rxDashesSlashes;

	//parsing functions for all supported time formats
	//e.g. 10:00PM, 1000Pm, 10 : 00 pm	(13:00 pm not accepted)
	bool parseHourMinAP(QRegExp &rxHourMinAP, QTime &time);
	//e.g. 10PM, 10Pm, 10 pm			(13 pm not accepted)
	bool parseHourAP(QRegExp &rxHourAP, QTime &time);
	//e.g. 10:00, 10 : 00				(24:00 not accepted)
	bool parseHourColMin(QRegExp &rxHourColMin, QTime &time);
	//e.g. at 10:00, at 10				(24:00 not accepted)

	//parsing functions for all supported date formats
	//any combination of DD or D, MM or M, YY or YYYY, in that order (e.g. 31/1/2014, 1-12-14)
	//year is optional
	bool parseDashesSlashes(QRegExp &rxDashesSlashes, QDate &date);

public:
	DateTimeParser();

	//returns false if anything aside from date or time is found in string, or if string is blank (string should then be treated as part of desc)
	//sets date or time to null if no valid date or time is found
	bool parseString(std::string inputString, QDate &outputDate, QTime &outputTime);
	
	//returns false if no valid time found
	bool extractTime(QString &input, QTime &time);
	//returns false if no valid date found
	bool extractDate(QString &input, QDate &date);

	//attempts to guess year (logic needs looking over, will change day and month if date is found invalid)
	int guessYear(int &day, int &month);

};
#endif