//DateTimeParser.h
//v 3.0
//Added ablity to parse "July 4th" format
#ifndef DATETIMEPARSER_H
#define DATETIMEPARSER_H

#include <QDateTime>
#include <QString>
#include <string>
#include <QRegExp>
#include "DateTime.h"

class DateTimeParser{
private:
	QDate _date;
	QTime _time;
	
	static QRegExp rxEmpty;

	static QRegExp rxHourMinAP;
	static QRegExp rxHourAP;
	static QRegExp rxHourColMin;
	static QRegExp rxAtHourMin;

	static QRegExp rxDashesSlashes;
	static QRegExp rxWeekDays;
	static QRegExp rxDayShortWordMonth;
	static QRegExp rxDayLongWordMonth;
	static QRegExp rxShortWordMonthDay;
	static QRegExp rxLongWordMonthDay;
	static QRegExp rxShortWeekDays;
	static QRegExp rxLongWeekDays;
	static QRegExp rxToday;
	static QRegExp rxTomorrow;
	static QRegExp rxYesterday;
	static QRegExp rxDayAfter;
	static QRegExp rxNextWeek;

	//Parsing functions for all supported time formats
	//Posts: return true if valid time is found

	//e.g. 10:00PM, 1000Pm, 10 : 00 pm	(13:00 pm not accepted)
	bool parseHourMinAP(QTime &time);
	//e.g. 10PM, 10Pm, 10 pm			(13 pm not accepted)
	bool parseHourAP(QTime &time);
	//e.g. 10:00, 10 : 00				(24:00 not accepted)
	bool parseHourColMin(QTime &time);


	//parsing functions for all supported date formats
	//Posts: return true if valid date is found

	//any combination of DD or D, MM or M, YY or YYYY, in that order (e.g. 31/1/2014, 1-12-14), year is optional
	bool parseDashesSlashes(QDate &date);
	bool parseDayShortWordMonth(QDate &date);
	bool parseDayLongWordMonth(QDate &date);
	bool parseShortWordMonthDay(QDate &date);
	bool parseLongWordMonthDay(QDate &date);
	bool parseShortWeekDays(QDate &date, int &dayOfWeek);
	bool parseLongWeekDays(QDate &date, int &dayOfWeek);
	bool parseToday(QDate &date);
	bool parseTomorrow(QDate &date);
	bool parseYesterday(QDate &date);
	bool parseDayAfter(QDate &date);
	bool parseNextWeek(QDate &date, int &dayOfWeek);
	

public:
	DateTimeParser();
	static QRegExp RX_DAYWORDS;
	
	//sets date or time to null if no valid date or time is found respectively
	//Post: returns false if string is suspected to be part of desc, and date and time will be set to null
	bool parseString(QString input, QDate &outputDate, QTime &outputTime);
	//Overloaded function that records the day of the week as well. Used for strings marked as end dates.
	bool parseString(QString input, QDate &outputDate, QTime &outputTime, int &dayOfWeek);

	//Post: returns false if an invalid time found
	bool extractTime(QString &input, QTime &time);
	//Post: returns false if an invalid date is found
	bool extractDate(QString &input, QDate &date, int &dayOfWeek);

	//Post: returns a year that assumes the day and month are upcoming dates
	//Changes 29 Feb to 28 Feb if upcoming Feb has no 29th.
	int guessYear(int &day, int &month);

	void autoCompleteYear(int size, int &year);
};
#endif