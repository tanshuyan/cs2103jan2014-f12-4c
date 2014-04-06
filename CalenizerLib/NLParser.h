//NLParser.h
//v 3.0
//Ability to read dates and times at the end of the string not marked by keywords
//Added ability to parse "until [weekday]" properly
#ifndef NLPARSER_H
#define NLPARSER_H

#include <QDateTime>
#include <QString>
#include <QRegExp>
#include "NLFunctions.h"
//remove this later
#include "DateTimeParser.h"

//All functions return false if any error occurs
class NLParser{
private:
	//remove this later
	DateTimeParser _dateTimeParser;
	NLFunctions _nlFunctions;

	QString extractDesc(QString &descString);
	//Extracts dates and times marked by keywords such as "Starting", "From" or "On" and removes them from the descString
	void extractMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled, int &dayOfWeek);
	//Extracts dates marked by words such as "Today", "Tmr" or months such as "August" and removes them from the descString
	void extractWordedDates(QString &descString, QDate &startDate, QTime &startTime);
	//Extracts dates and times unmarked by any keywords found at the end of descString and removes them from descString
	void extractUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime);
	//Attempts to contextually guess a starting time from the user input, such as "8pm meeting". Does not alter descString.
	void guessContextualTime(QString descString, QTime &startTime);

public:
	NLParser();
	void parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled, int &dayOfWeek);
};
#endif