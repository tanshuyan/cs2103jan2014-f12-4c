//NLParser.cpp
//v 3.0
//Ability to read dates and times at the end of the string not marked by keywords
//Added ability to parse "until [weekday]" properly

#include "NLParser.h"

NLParser::NLParser(){
}

void NLParser::parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	QString desc = extractDesc(descString);
	extractMarkedDateTime(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek);
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

void NLParser::extractMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	dateTimeIsUnlabelled = true;
	dayOfWeek = -1;
	//search for "from... until..." format
	if(_nlFunctions.searchFromUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "until... from..." format
	if(_nlFunctions.searchUntilFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "on... until..." format
	if(_nlFunctions.searchOnUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "start..." format
	if(_nlFunctions.searchFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "end..." format
	if(_nlFunctions.searchUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
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