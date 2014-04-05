//NLParser.cpp
//v 3.0
//Ability to read dates and times at the end of the string not marked by keywords

#include "NLParser.h"
QRegExp NLParser::RX_QUOTES("\"(.+)\"");
QRegExp NLParser::RX_FROM_UNTIL("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_UNTIL_FROM("\\b(?:ending|end|until|till|til|to)\\b(.+)\\b(?:starting|start|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_UNTIL("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_START("\\b(?:starting|start|lasting|from(?!\\s+from)|begin|beginning)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_FROM("^(?:\\s*)(?:from)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_END("\\b(?:ending|end|until|till|til|to)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_ON_AT_BY("\\b(?:at(?!\\s+(on|at|by))|on(?!\\s+(on|at|by))|by(?!\\s+(on|at|by)))\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_BARE_MONTHS("(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\b(.+)", Qt::CaseInsensitive);
QRegExp NLParser::RX_TODAY(DateTimeParser::RX_DAYWORDS.pattern()+"\\b(.*)", Qt::CaseInsensitive);
QRegExp NLParser::RX_BARE_DATETIME("\\b\\d\\b(.+)", Qt::CaseInsensitive);


NLParser::NLParser(){
}

void NLParser::parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled){
	QString desc = extractDesc(descString);
	extractMarkedDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled);
	extractWordedDates(descString, startDate, startTime);
	extractUnmarkedDateTime(descString, startDate, startTime, endDate, endTime);
	guessContextualTime(descString, startTime);

	if(!desc.isEmpty()){
		descString = desc;
	}
	return;
}

QString NLParser::extractDesc(QString &descString){
	//Takes out the greatest par of the desc in "quotes"
	return _nlFunctions.extractQuotedDesc(descString);
}

void NLParser::extractMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled){
	dateTimeIsUnlabelled = true;

	//search for "from... until..." format
	if(_nlFunctions.searchFromUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "until... from..." format
	if(_nlFunctions.searchUntilFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "on... until..." format
	if(_nlFunctions.searchOnUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "start..." format
	if(_nlFunctions.searchFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "end..." format
	if(_nlFunctions.searchUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "at... on..." format
	if(_nlFunctions.searchOn(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}

	return;
}

void NLParser::extractWordedDates(QString &descString, QDate &startDate, QTime &startTime){
	if(startDate.isNull()){
		//Search for "Today" "Tomorrow" words that are untagged with keywords
		(_nlFunctions.searchTodayWords(descString, startDate, startTime));
	}
	return;
}

void NLParser::extractUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime){
	_nlFunctions.searchUnmarkedDateTime(descString, startDate, startTime);
	return;
}

void NLParser::guessContextualTime(QString descString, QTime &startTime){
	if (startTime.isNull()){
		_dateTimeParser.extractTime(descString, startTime);
	}
	return;
}