//@author A0097286M

//NLParser.h

#ifndef NLPDATEPARSER_H
#define NLPDATEPARSER_H

#include <QDateTime>
#include <QString>
#include <QRegExp>
#include "NLPDateFunctions.h"

class NLPDateParser{
private:
	NLPDateFunctions _nlpDateFunctions;

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
	NLPDateParser();
	void parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled, int &dayOfWeek);
};
#endif