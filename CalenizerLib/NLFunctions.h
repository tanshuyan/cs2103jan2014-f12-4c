//NLFunctions.h
//v 3.0
//Added ability to parse "until [weekday]" properly
#ifndef NLFUNCTIONS_H
#define NLFUNCTIONS_H

#include <QDateTime>
#include <QString>
#include <QRegExp>
#include "DateTimeParser.h"

//All functions return false if any error occurs
class NLFunctions{
private:
	DateTimeParser _dateTimeParser;
	const QDate _nullDate;
	const QTime _nullTime;

	static QRegExp RX_QUOTES;
	static QRegExp RX_FROM_UNTIL;
	static QRegExp RX_UNTIL_FROM;
	static QRegExp RX_ON_UNTIL;
	static QRegExp RX_START;
	static QRegExp RX_END;
	static QRegExp RX_ON_AT_BY;
	static QRegExp RX_FROM;
	static QRegExp RX_TODAY_WORDS;
	static QRegExp RX_UNMARKED_DATETIME;

	//Extracts the startDate from the position pos in the descString, and removes it from the point it was found in the string
	void searchUnmarkedDate(QString &descString, QDate &startDate, int pos);
	//Extracts the startTime from the position pos in the descString, and removes it from the point it was found in the string
	void searchUnmarkedTime(QString &descString, QTime &startTime, int pos);

public:
	NLFunctions();
	QString extractQuotedDesc(QString &descString);
	bool searchFromUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek);
	bool searchUntilFrom(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek);
	bool searchOnUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek);
	bool searchFrom(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled);
	bool searchUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek);
	bool searchOn(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled);

	bool searchTodayWords(QString &descString, QDate &startDate, QTime &startTime);
	bool searchUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime);

};
#endif