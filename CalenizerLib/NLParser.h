//NLParser.h
//v 3.0
//Ability to read dates and times at the end of the string not marked by keywords

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

	static QRegExp RX_QUOTES;
	static QRegExp RX_FROM_UNTIL;
	static QRegExp RX_UNTIL_FROM;
	static QRegExp RX_ON_UNTIL;
	static QRegExp RX_START;
	static QRegExp RX_END;
	static QRegExp RX_ON_AT_BY;
	static QRegExp RX_FROM;
	static QRegExp RX_BARE_MONTHS;
	static QRegExp RX_BARE_DATETIME;
	static QRegExp RX_TODAY;

	QString extractDesc(QString &descString);
	//Extracts dates and times marked by keywords such as "Starting", "From" or "On" and removes them from the descString
	void extractMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled);
	//Extracts dates marked by words such as "Today", "Tmr" or months such as "August" and removes them from the descString
	void extractWordedDates(QString &descString, QDate &startDate, QTime &startTime);
	//Extracts dates and times unmarked by any keywords found at the end of descString and removes them from descString
	void extractUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime);
	//Attempts to contextually guess a starting time from the user input, such as "8pm meeting". Does not alter descString.
	void guessContextualTime(QString descString, QTime &startTime);

public:
	NLParser();
	void parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled);
};
#endif