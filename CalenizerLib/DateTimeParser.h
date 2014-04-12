//@author A0097286M

//DateTimeParser.h

#ifndef DATETIMEPARSER_H
#define DATETIMEPARSER_H

#include <QDateTime>
#include <QString>
#include <string>
#include <QRegExp>
#include "DateTime.h"
#include "Message.h"
#include "Exception.h"

class DateTimeParser{
private:
	static QRegExp RX_EMPTY;

	static QRegExp RX_HOUR_MIN_AP;
	static QRegExp RX_HOUR_AP;
	static QRegExp RX_HOUR_COL_MIN;
	static QRegExp RX_AT_HOUR;

	static QRegExp RX_DASHES_SLASHES;
	static QRegExp RX_DAY_SHORT_MONTH;
	static QRegExp RX_DAY_LONG_MONTH;
	static QRegExp RX_SHORT_MONTH_DAY;
	static QRegExp RX_LONG_MONTH_DAY;
	static QRegExp RX_SHORT_WEEK_DAYS;
	static QRegExp RX_LONG_WEEK_DAYS;
	static QRegExp RX_TODAY;
	static QRegExp RX_TOMORROW;
	static QRegExp RX_YESTERDAY;
	static QRegExp RX_DAY_AFTER;
	static QRegExp RX_NEXT_WEEK;

	//Parsing functions for all supported time formats
	//Posts: return true if valid time is found

	//e.g. 10:00PM, 1000Pm, 10 : 00 pm	(13:00 pm not accepted)
	bool parseHourMinAP(QTime &time);
	//e.g. 10PM, 10Pm, 10 pm			(13 pm not accepted)
	bool parseHourAP(QTime &time);
	//e.g. 10:00, 10 : 00				(24:00 not accepted)
	bool parseHourColMin(QTime &time);
	//e.g. at 10
	bool parseAtHour(QTime &time);

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
	
	//Post: returns a year that assumes the day and month are upcoming dates. Changes 29 Feb to 28 Feb if upcoming Feb has no 29th.
	int guessYear(int &day, int &month);
	void autoCompleteYear(int size, int &year);
	int dayOFWeekToInt(QString dayOfWeek);

public:
	DateTimeParser();
	static QRegExp RX_DAYWORDS;
	
	//Sets date or time to null if no valid date or time is found respectively. Used primarily for end dates.
	//Post: returns false if string is suspected to be part of desc, and date and time will be set to null
	//Records the day of the week as well. Mon is 1, Sun is 7, "Next Week" is 0, and "No indicated day" is -1. 
	bool parseString(QString input, QDate &outputDate, QTime &outputTime, int &dayOfWeek);
	//Overloaded function that does not require dayOfWeek field. Used primarily for start dates.
	bool parseString(QString input, QDate &outputDate, QTime &outputTime);
	//Post: returns false if an invalid time found
	bool extractTime(QString &input, QTime &time);
	//Post: returns false if an invalid date is found
	bool extractDate(QString &input, QDate &date, int &dayOfWeek);
	//Overloaded function that does not require dayOfWeek field
	bool extractDate(QString &input, QDate &date);
};
#endif