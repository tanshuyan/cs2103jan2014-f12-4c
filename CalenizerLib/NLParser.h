//NLParser.h
//v 2.0

#ifndef NLPARSER_H
#define NLPARSER_H

#include <QDateTime>
#include <QString>
#include <string>
#include <QRegExp>
#include "DateTimeParser.h"

//All functions return false if any error occurs
class NLParser{
private:
	DateTimeParser _dateTimeParser;
	
	static QRegExp RX_FROM_UNTIL;
	static QRegExp RX_UNTIL_FROM;
	static QRegExp RX_ON_UNTIL;
	static QRegExp RX_START;
	static QRegExp RX_END;
	static QRegExp RX_ON_AT_BY;
	static QRegExp RX_FROM;

public:
	NLParser();
	void parse(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled);



};
#endif