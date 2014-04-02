//NLParser.cpp
//v 2.7
//Deleted some unused code
//added ability to recognise "lasting from"
//v 2.8

#include "NLParser.h"
//rmb to remove later
#include <iostream>
QRegExp NLParser::RX_FROM_UNTIL("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_UNTIL_FROM("\\b(?:ending|end|until|till|til|to)\\b(.+)\\b(?:starting|start|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_UNTIL("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_START("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_FROM("^(?:\\s*)(?:from)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_END("\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_AT_BY("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_TODAY(DateTimeParser::RX_DAYWORDS.pattern()+"\\b(.*)", Qt::CaseInsensitive);


NLParser::NLParser(){
}

void NLParser::parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	parseMarkedDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	//
	parseTodayWords(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	
	return;
}
void NLParser::parseMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	QDate nullDate;
	QTime nullTime;
	dateTimeIsUnlablled = true;

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
		dateTimeIsUnlablled = false;
		return;
	}

	//search for "until... from..." format
	RX_UNTIL_FROM.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(1), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(2), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_UNTIL_FROM.pos());
		descString = descString.trimmed();
		dateTimeIsUnlablled = false;
		return;
	}

	//search for "on... until..." format
	RX_ON_UNTIL.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(2), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(1), endDate, endTime);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_ON_UNTIL.pos());
		descString = descString.trimmed();
		dateTimeIsUnlablled = false;
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
		dateTimeIsUnlablled = false;
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
		dateTimeIsUnlablled = false;
		return;
	}

	//search for "at... on..." format
	pos = -1;
	bool stringIsValid = false;
	do{
		pos = RX_ON_AT_BY.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_ON_AT_BY.cap(1), startDate, startTime);
	}while (!stringIsValid && pos != -1);

	if (stringIsValid){
		descString.truncate(RX_ON_AT_BY.pos());
		descString = descString.trimmed();
		endDate = nullDate;
		endTime = nullTime;
		return;
	}

	return;
}

void NLParser::parseTodayWords(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	QDate foundDate;
	QTime foundTime;
	//if(dateTimeIsUnlablled && startDate.isNull()){
	if(startDate.isNull()){
		//exit if not found
		if (RX_TODAY.indexIn(descString) == -1){
			return;
		}
		//check: if foundStartDate is found and string is empty (use parseDateTime)(accept extra time i.e. decription today 7pm at 6pm){
		int pos = -1;
		bool stringIsValid = false;
		do{
			pos = RX_TODAY.indexIn(descString, pos+1);
			QString todayString = RX_TODAY.cap(0);
			//May need to remove this
			if (RX_FROM.indexIn(RX_TODAY.cap(1)) != -1){
				todayString = RX_FROM.cap(0);
			}
			//
			stringIsValid = _dateTimeParser.parseString(todayString, foundDate, foundTime);
		}while (!stringIsValid && pos != -1);
	
		if (stringIsValid){
			startDate = foundDate;
			if (startTime.isNull()){
				startTime = foundTime;
			}
			descString.truncate(RX_TODAY.pos());
			if (RX_FROM.pos() != -1){
				dateTimeIsUnlablled = false;
			}
		}
	}
	return;
}


void NLParser::guessContextualTime(QString descString, QTime &startTime){
	if (startTime.isNull()){
		_dateTimeParser.extractTime(descString, startTime);
	}
	return;
}