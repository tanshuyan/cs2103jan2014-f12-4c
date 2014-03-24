//NLParser.cpp
//IN PROGRESS
//v 2.4

#include "NLParser.h"

QRegExp NLParser::RX_FROM_UNTIL("\\b(?:starting|start|from(?!\\s+from)|begin|beginning)\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_UNTIL_FROM("\\b(?:ending|end|until|till|til|to)\\b(.+)\\b(?:starting|start|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_UNTIL("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_START("\\b(?:starting|starting from|from(?!\\s+from)|start|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_FROM("^(?:\\s*)(?:from)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_END("\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_AT_BY("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_TODAY(DateTimeParser::RX_DAYWORDS.pattern()+"\\b(.*)", Qt::CaseInsensitive);


NLParser::NLParser(){
}

void NLParser::parse(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	QDate nullDate;
	QTime nullTime;
	dateTimeIsUnlablled = false;

	//search for "from... until..." format
	int pos = -1;
	bool fromStringIsValid = false;
	bool untilStringIsValid = false;
	do{
		pos = RX_FROM_UNTIL.indexIn(descString, pos+1);
		QString fromString = RX_FROM_UNTIL.cap(1);
		if (RX_FROM.indexIn(RX_FROM_UNTIL.cap(1)) != -1){
			fromString = RX_FROM.cap(1);
		}
		fromStringIsValid = _dateTimeParser.parseString(fromString, startDate, startTime);
		untilStringIsValid = _dateTimeParser.parseString(RX_FROM_UNTIL.cap(2), endDate, endTime);
	}while (!(fromStringIsValid && untilStringIsValid) && pos != -1);

	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_FROM_UNTIL.pos());
		descString = descString.trimmed();
		return;
	}

	//search for "until... from..." format
	RX_UNTIL_FROM.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(1), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(2), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_UNTIL_FROM.pos());
		descString = descString.trimmed();
		return;
	}

	//search for "on... until..." format
	RX_ON_UNTIL.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(2), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(1), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_ON_UNTIL.pos());
		descString = descString.trimmed();
		return;
	}

	//search for "start..." format
	pos = -1;
	fromStringIsValid = false;
	do{
		pos = RX_START.indexIn(descString, pos+1);
		QString fromString = RX_START.cap(1);
		if (RX_FROM.indexIn(RX_START.cap(1)) != -1){
			fromString = RX_FROM.cap(1);
		}
		fromStringIsValid = _dateTimeParser.parseString(fromString, startDate, startTime);
	}while (!fromStringIsValid && pos != -1);
	
	if (fromStringIsValid){
		descString.truncate(RX_START.pos());
		descString = descString.trimmed();
		endDate = nullDate;
		endTime = nullTime;
		return;
	}

	//search for "end..." format
	RX_END.lastIndexIn(descString);
	untilStringIsValid = _dateTimeParser.parseString(RX_END.cap(1), endDate, endTime);
	if (untilStringIsValid){
		descString.truncate(RX_END.pos());
		descString = descString.trimmed();
		startDate = nullDate;
		startTime = nullTime;
		return;
	}

	//search for "Today/tomorrow/etc. ..." format
	pos = -1;
	bool stringIsValid = false;
	do{
		pos = RX_TODAY.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_TODAY.cap(1), startDate, startTime);
	}while (!stringIsValid && pos != -1);

	if (stringIsValid){
		descString.truncate(RX_TODAY.pos());
		descString = descString.trimmed();
		endDate = nullDate;
		endTime = nullTime;
		dateTimeIsUnlablled = true;
		return;
	}

	//search for "at... on..." format
	pos = -1;
	stringIsValid = false;
	do{
		pos = RX_ON_AT_BY.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_ON_AT_BY.cap(1), startDate, startTime);
	}while (!stringIsValid && pos != -1);

	if (stringIsValid){
		descString.truncate(RX_ON_AT_BY.pos());
		descString = descString.trimmed();
		endDate = nullDate;
		endTime = nullTime;
		dateTimeIsUnlablled = true;
		return;
	}

	return;
}

void NLParser::guessContextualTime(QString descString, QTime &startTime){
	if (startTime.isNull()){
		//may need to ensure that this point doesn't throw exceptions
		_dateTimeParser.extractTime(descString, startTime);
	}
	return;
}