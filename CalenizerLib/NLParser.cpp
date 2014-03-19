//NLParser.cpp
//IN PROGRESS
//v 1.3

#include "NLParser.h"

QRegExp NLParser::RX_FROM_UNTIL("\\b(?:starting|start|from(?!\\s+from)|begin|beginning)(?:\\s*+from)?\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_UNTIL_FROM("\\b(?:ending|end|until|till|til|to)\\b(.+)\\b(?:starting|start|from(?!\\s+from)|begin|beginning)(?:from)?\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_FROM("\\b(?:starting|start|from(?!\\s+from)|begin|beginning)(?:from)?\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_UNTIL("\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_AT_BY("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)", Qt::CaseInsensitive);

void NLParser::parseEdit(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime){
	QDate nullDate;
	QTime nullTime;

	//search for "from... until..." format
	RX_FROM_UNTIL.lastIndexIn(descString);
	bool fromStringIsValid = _dateTimeParser.parseString(RX_FROM_UNTIL.cap(1), startDate, startTime);
	bool untilStringIsValid = _dateTimeParser.parseString(RX_FROM_UNTIL.cap(2), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_FROM_UNTIL.pos());
		descString.trimmed();
		return;
	}

	//search for "until... from..." format
	RX_UNTIL_FROM.lastIndexIn(descString);
	bool fromStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(2), startDate, startTime);
	bool untilStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(1), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_UNTIL_FROM.pos());
		descString.trimmed();
		return;
	}

	//search for "start..." format
	RX_FROM.lastIndexIn(descString);
	bool fromStringIsValid = _dateTimeParser.parseString(RX_FROM.cap(1), startDate, startTime);
	if (fromStringIsValid){
		descString.truncate(RX_FROM.pos());
		descString.trimmed();
		endDate = nullDate;
		endTime = nullTime;
		return;
	}

	//search for "end..." format
	RX_FROM_UNTIL.lastIndexIn(descString);
	bool untilStringIsValid = _dateTimeParser.parseString(RX_UNTIL.cap(1), endDate, endTime);
	if (untilStringIsValid){
		descString.truncate(RX_UNTIL.pos());
		descString.trimmed();
		startDate = nullDate;
		startTime = nullTime;
		return;
	}

	//search for "at... on..." format
	int pos = -1;
	bool onStringIsValid = false;
	do{
		pos = RX_ON_AT_BY.indexIn(descString, pos+1);
		onStringIsValid = _dateTimeParser.parseString(RX_ON_AT_BY.cap(1), endDate, endTime);
	}while (!onStringIsValid && pos != -1);

	if (onStringIsValid){
		descString.truncate(RX_ON_AT_BY.pos());
		descString.trimmed();
		return;
	}
}


