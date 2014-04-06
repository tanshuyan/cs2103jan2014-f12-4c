//NLFunctions.cpp
//v 3.0
//Added ability to parse "until [weekday]" properly
#include "NLFunctions.h"
QRegExp NLFunctions::RX_QUOTES("\"(.+)\"");
QRegExp NLFunctions::RX_FROM_UNTIL("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_UNTIL_FROM("\\b(?:ending|end|until|till|til|to)\\b(.+)\\b(?:starting|start|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_ON_UNTIL("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_START("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_FROM("^(?:\\s*)(?:from)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_END("\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_ON_AT_BY("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_TODAY_WORDS(DateTimeParser::RX_DAYWORDS.pattern()+"\\b(.*)", Qt::CaseInsensitive);
QRegExp NLFunctions::RX_UNMARKED_DATETIME("\\b(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec|\\d)(.+)", Qt::CaseInsensitive);

NLFunctions::NLFunctions(){
}

QString NLFunctions::extractQuotedDesc(QString &descString){
	RX_QUOTES.indexIn(descString);
	return RX_QUOTES.cap(1);
}

bool NLFunctions::searchFromUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	int pos = -1;
	bool fromStringIsValid;
	bool untilStringIsValid;
	do{
		pos = RX_FROM_UNTIL.indexIn(descString, pos+1);
		QString fromString = RX_FROM_UNTIL.cap(1);
		//removes any "from"s, since the user may have typed "starting from" or "beginning from"
		if (RX_FROM.indexIn(RX_FROM_UNTIL.cap(1)) != -1){
			fromString = RX_FROM.cap(1);
		}
		fromStringIsValid = _dateTimeParser.parseString(fromString, startDate, startTime);
		untilStringIsValid = _dateTimeParser.parseString(RX_FROM_UNTIL.cap(2), endDate, endTime, dayOfWeek);
	}while (!(fromStringIsValid && untilStringIsValid) && pos != -1);

	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_FROM_UNTIL.pos());
		descString = descString.trimmed();
		dateTimeIsUnlabelled = false;
		return true;
	}
	return false;
}

bool NLFunctions::searchUntilFrom(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	int pos = -1;
	bool fromStringIsValid;
	bool untilStringIsValid;
	RX_UNTIL_FROM.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(1), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_UNTIL_FROM.cap(2), endDate, endTime, dayOfWeek);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_UNTIL_FROM.pos());
		descString = descString.trimmed();
		dateTimeIsUnlabelled = false;
		return true;
	}
	return false;
}

bool NLFunctions::searchOnUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	int pos = -1;
	bool fromStringIsValid;
	bool untilStringIsValid;
	RX_ON_UNTIL.lastIndexIn(descString);
	fromStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(2), startDate, startTime);
	untilStringIsValid = _dateTimeParser.parseString(RX_ON_UNTIL.cap(1), endDate, endTime, dayOfWeek);
	if (fromStringIsValid && untilStringIsValid){
		descString.truncate(RX_ON_UNTIL.pos());
		descString = descString.trimmed();
		dateTimeIsUnlabelled = false;
		return true;
	}
	return false;
}

bool NLFunctions::searchFrom(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled){
	int pos = -1;
	bool fromStringIsValid;
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
		endDate = _nullDate;
		endTime = _nullTime;
		dateTimeIsUnlabelled = false;
		return true;
	}
	return false;
}

bool NLFunctions::searchUntil(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	int pos = -1;
	bool untilStringIsValid;
	RX_END.lastIndexIn(descString);
	untilStringIsValid = _dateTimeParser.parseString(RX_END.cap(1), endDate, endTime, dayOfWeek);
	if (untilStringIsValid){
		descString.truncate(RX_END.pos());
		descString = descString.trimmed();
		startDate = _nullDate;
		startTime = _nullTime;
		dateTimeIsUnlabelled = false;
		return true;
	}
	return false;
}

bool NLFunctions::searchOn(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled){
	int pos = -1;
	bool stringIsValid;
	do{
		pos = RX_ON_AT_BY.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_ON_AT_BY.cap(1), startDate, startTime);
	}while (!stringIsValid && pos != -1);

	if (stringIsValid){
		descString.truncate(RX_ON_AT_BY.pos());
		descString = descString.trimmed();
		endDate = _nullDate;
		endTime = _nullTime;
		return true;
	}
	return false;
}

bool NLFunctions::searchTodayWords(QString &descString, QDate &startDate, QTime &startTime){
	QDate foundDate;
	QTime foundTime;
	int pos = -1;
	bool stringIsValid;
	do{
		pos = RX_TODAY_WORDS.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_TODAY_WORDS.cap(0), foundDate, foundTime);
	}while (!stringIsValid && pos != -1);
	
	if (stringIsValid){
		startDate = foundDate;
		if (startTime.isNull()){
			startTime = foundTime;
		}
		descString.truncate(RX_TODAY_WORDS.pos());
		return true;
	}
	return false;
}

bool NLFunctions::searchUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime){
	QDate foundDate;
	QTime foundTime;
	int pos = -1;
	bool stringIsValid = false;
	do{
		pos = RX_UNMARKED_DATETIME.indexIn(descString, pos+1);
		stringIsValid = _dateTimeParser.parseString(RX_UNMARKED_DATETIME.cap(0), foundDate, foundTime);
		QString lalala = RX_UNMARKED_DATETIME.cap(0);
	}while (!stringIsValid && pos != -1);

	if(stringIsValid){
		if(startDate.isNull() && startTime.isNull()){
			startDate = foundDate;
			startTime = foundTime;
			descString.truncate(pos);
			return true;
		}
		if(startDate.isNull() && foundDate.isValid()){
			searchUnmarkedDate(descString, startDate, pos);
			return true;
		}
		if(startTime.isNull() && foundTime.isValid()){
			searchUnmarkedTime(descString, startTime, pos);
			return true; 
		}
	}
	return false;
}

void NLFunctions::searchUnmarkedDate(QString &descString, QDate &startDate, int pos){
	//subString contains the date and time substring
	QString subString = descString.mid(pos);
	_dateTimeParser.extractDate(subString, startDate);
	//check if the extracted date was found at the very end of the string 
	if(descString.mid(pos).startsWith(subString) || subString.isEmpty()){
		descString.truncate(pos+subString.length());
	} else{
		descString.truncate(pos);
	}
	return;
}

void NLFunctions::searchUnmarkedTime(QString &descString, QTime &startTime, int pos){
	//subString contains the date and time substring
	QString subString = descString.mid(pos);
	_dateTimeParser.extractTime(subString, startTime);
	//check if the extracted time was found at the very end of the string 
	if(descString.mid(pos).startsWith(subString) || subString.isEmpty()){
		descString.truncate(pos+subString.length());
	} else{
		descString.truncate(pos);
	}
	return;
}