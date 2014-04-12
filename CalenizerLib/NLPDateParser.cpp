//@author A0097286M

//NLPDateParser.cpp

#include "NLPDateParser.h"

NLPDateParser::NLPDateParser(){
}

void NLPDateParser::parseDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
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

QString NLPDateParser::extractDesc(QString &descString){
	//Takes out the greatest par of the desc in "quotes"
	return _nlpDateFunctions.extractQuotedDesc(descString);
}

void NLPDateParser::extractMarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlabelled, int &dayOfWeek){
	dateTimeIsUnlabelled = true;
	dayOfWeek = -1;
	//search for "from... until..." format
	if(_nlpDateFunctions.searchFromUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "until... from..." format
	if(_nlpDateFunctions.searchUntilFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "on... until..." format
	if(_nlpDateFunctions.searchOnUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "start..." format
	if(_nlpDateFunctions.searchFrom(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	//search for "end..." format
	if(_nlpDateFunctions.searchUntil(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled, dayOfWeek)){
		return;
	}
	//search for "at... on..." format
	if(_nlpDateFunctions.searchOn(descString, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled)){
		return;
	}
	return;
}

void NLPDateParser::extractWordedDates(QString &descString, QDate &startDate, QTime &startTime){
	if(startDate.isNull()){
		//Search for "Today" "Tomorrow" words that are untagged with keywords
		(_nlpDateFunctions.searchTodayWords(descString, startDate, startTime));
	}
	return;
}

void NLPDateParser::extractUnmarkedDateTime(QString &descString, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime){
	_nlpDateFunctions.searchUnmarkedDateTime(descString, startDate, startTime);
	return;
}

void NLPDateParser::guessContextualTime(QString descString, QTime &startTime){
	_nlpDateFunctions.guessContextualTime(descString, startTime);
}