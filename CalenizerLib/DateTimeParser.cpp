//DateTimeParser.cpp
//v 3.0
//Added ablity to parse "July 4th" format
//Added ability to parse "until [weekday]" properly
#include "DateTimeParser.h"

QRegExp DateTimeParser::rxEmpty("(^\\s*$)");

QRegExp DateTimeParser::rxHourMinAP("(?:at|on|by)?\\s*(\\d{1,2})\\s*(?::?)\\s*(\\d{2})\\s*(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourAP("(?:at|on|by)?\\s*(\\d{1,2})\\s*(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourColMin("(?:at|on|by)?\\s*(\\d{1,2})\\s*(?::)\\s*(\\d{2})",Qt::CaseInsensitive);

QRegExp DateTimeParser::rxDashesSlashes("(?:at|on|by)?\\s*(\\d{1,2})(?:/|-|\.)(\\d{1,2})(?:/|-|\.)?(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDayShortWordMonth("(?:at|on|by)?\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\s*(?:of)?\\s*(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDayLongWordMonth("(?:at|on|by)?\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\s*(?:of)?\\s*(january|february|march|april|may|june|july|august|september|october|november|december)\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxShortWordMonthDay("(?:at|on|by)?\\s*(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\b\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxLongWordMonthDay("(?:at|on|by)?\\s*(january|february|march|april|may|june|july|august|september|october|november|december)\\b\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxShortWeekDays("(?:on|by)?\\s*(?:the|this)?\\s*(?:next|coming)?\\s*(sun|mon|tue|tues|wed|thu|thur|thurs|fri|sat)\\b",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxLongWeekDays("(?:on|by)?\\s*(?:the|this)?\\s*(?:next|coming)?\\s*(sunday|monday|tuesday|wednesday|thursday|friday|saturday)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxToday("(?:by)?\\s*(today|tdy|td)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxTomorrow("(?:by)?\\s*(tomorrow|tommorrow|tommorow|tmr)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxYesterday("(?:since)?\\s*(yesterday|ystd)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDayAfter("(?:by)?\\s*(the)?\\s*(day)\\s*(after)\\s*(tomorrow|tommorrow|tommorow|tmr)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxNextWeek("(?:by)?\\s*(next|nxt)\\s*(week|wk)",Qt::CaseInsensitive);

QRegExp DateTimeParser::RX_DAYWORDS("(("+rxToday.pattern()
									+")|("+rxTomorrow.pattern()
									+")|("+rxYesterday.pattern()
									+")|("+rxYesterday.pattern()
									+")|("+rxDayAfter.pattern()
									+")|("+rxNextWeek.pattern()
									+")|("+rxShortWeekDays.pattern()
									+")|("+rxLongWeekDays.pattern()
									+"))",Qt::CaseInsensitive);

DateTimeParser::DateTimeParser(){
}

bool DateTimeParser::parseString(QString input, QDate &outputDate, QTime &outputTime, int &dayOfWeek){
	QDate nullDate;
	QTime nullTime;
	outputDate = nullDate;
	outputTime = nullTime;
	//if the input string is empty, or only contains white spaces, the keyword is assumed to be part of the description
	if (rxEmpty.exactMatch(input)){
		return false;
	}
	bool isInvalidTime = !extractTime(input, outputTime);
	if (isInvalidTime){
		throw (10);
	}
	bool isInvalidDate = !extractDate(input, outputDate, dayOfWeek);
	if (isInvalidDate){
		throw (20);
	}
	bool isTaskDesc = !input.trimmed().isEmpty();
	if (isTaskDesc){
		outputDate = nullDate;
		outputTime = nullTime;
		return false;
	}
	return true;
}

bool DateTimeParser::parseString(QString input, QDate &outputDate, QTime &outputTime){
	int dummy;
	return parseString(input, outputDate, outputTime, dummy);
}

bool DateTimeParser::extractTime(QString &input, QTime &time){
	int pos;
	//check for HourMinAP format (1000 AM)
	pos = rxHourMinAP.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourMinAP.matchedLength());
		return parseHourMinAP(time);
	}
	//check for HourAP format (10 AM)
	pos = rxHourAP.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourAP.matchedLength());
		return parseHourAP(time);
	}
	//check for HourColMin format (10:00)
	pos = rxHourColMin.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourColMin.matchedLength());
		return parseHourColMin(time);
	}
	return true;
}

bool DateTimeParser::extractDate(QString &input, QDate &date, int &dayOfWeek){
	int pos;
	dayOfWeek = -1;
	//check for full month format (3rd december)
	pos = rxDayLongWordMonth.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDayLongWordMonth.matchedLength());
		return parseDayLongWordMonth(date);
	}
	//check for abbreviated month format (3rd dec)
	pos = rxDayShortWordMonth.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDayShortWordMonth.matchedLength());
		return parseDayShortWordMonth(date);
	}
	//check for full month format (december 3rd)
	pos = rxLongWordMonthDay.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxLongWordMonthDay.matchedLength());
		return parseLongWordMonthDay(date);
	}
	//check for abbreviated month format (dec 3rd)
	pos = rxShortWordMonthDay.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxShortWordMonthDay.matchedLength());
		return parseShortWordMonthDay(date);
	}
	//check for DashesSlashes format (31/1/2014, 31-1-2014)
	pos = rxDashesSlashes.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDashesSlashes.matchedLength());
		return parseDashesSlashes(date);
	}
	//check for short week format (sun, mon)
	pos = rxShortWeekDays.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxShortWeekDays.matchedLength());
		return parseShortWeekDays(date, dayOfWeek);
	}
	//check for long week format (sunday, monday)
	pos = rxLongWeekDays.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxLongWeekDays.matchedLength());
		return parseLongWeekDays(date, dayOfWeek);
	}
	//check for "Today" words
	pos = rxToday.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxToday.matchedLength());
		return parseToday(date);
	}
	//check for "the day after tomorrow" words
	pos = rxDayAfter.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDayAfter.matchedLength());
		return parseDayAfter(date);
	}
	//check for "Tomorrow" words
	pos = rxTomorrow.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxTomorrow.matchedLength());
		return parseTomorrow(date);
	}
	//check for "Yesterday" words
	pos = rxYesterday.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxYesterday.matchedLength());
		return parseYesterday(date);
	}
	//check for "next week" words
	pos = rxNextWeek.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxNextWeek.matchedLength());
		return parseNextWeek(date, dayOfWeek);
	}
	return true;
}

bool DateTimeParser::extractDate(QString &input, QDate &date){
	int dummy;
	return extractDate(input, date, dummy);
}

//Time Parsers

bool DateTimeParser::parseHourMinAP(QTime &time){
	//Get hours
	int hour = rxHourMinAP.cap(1).toInt();
	//Get minutes
	int minute = rxHourMinAP.cap(2).toInt();

 	if(hour > 12 || hour < 1 || minute < 0 || minute > 59){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (rxHourMinAP.cap(3).contains("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, minute, 0);
	return true;
}

bool DateTimeParser::parseHourAP(QTime &time){
	//Get hours
	int hour = rxHourAP.cap(1).toInt();
	if(hour > 12 || hour < 1){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (rxHourAP.cap(2).contains("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, 0, 0);
	return true;
}

bool DateTimeParser::parseHourColMin(QTime &time){
	//Get hours
	int hour = rxHourColMin.cap(1).toInt();
	//Get minutes
	int minute = rxHourColMin.cap(2).toInt();
		
	if(hour > 23 || hour < 0 || minute < 0 || minute > 59){
		return false;
	}
	time.setHMS(hour, minute, 0);
	return true;
}

//Date Parsers

bool DateTimeParser::parseDashesSlashes(QDate &date){
	//Get days
	int day = rxDashesSlashes.cap(1).toInt();
	//Get Months
	int month = rxDashesSlashes.cap(2).toInt();
	//Get Years
	int year = rxDashesSlashes.cap(3).toInt();
	autoCompleteYear(rxDashesSlashes.cap(3).size(), year);
	if(rxDashesSlashes.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseDayShortWordMonth(QDate &date){
	//Get days
	int day = rxDayShortWordMonth.cap(1).toInt();
	//Get Months
	int month = QDate::fromString(rxDayShortWordMonth.cap(2), "MMM").month();
	//Get Years
	int year = rxDayShortWordMonth.cap(3).toInt();
	autoCompleteYear(rxDayShortWordMonth.cap(3).size(), year);
	if (rxDayShortWordMonth.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseDayLongWordMonth(QDate &date){
	//Get days
	int day = rxDayLongWordMonth.cap(1).toInt();
	//Get Months
	int month = QDate::fromString(rxDayLongWordMonth.cap(2), "MMMM").month();
	//Get Years
	int year = rxDayLongWordMonth.cap(3).toInt();
	autoCompleteYear(rxDayLongWordMonth.cap(3).size(), year);
	if (rxDayLongWordMonth.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseShortWordMonthDay(QDate &date){
	//Get days
	int day = rxShortWordMonthDay.cap(2).toInt();
	//Get Months
	int month = QDate::fromString(rxShortWordMonthDay.cap(1), "MMM").month();
	//Get Years
	int year = rxShortWordMonthDay.cap(3).toInt();
	autoCompleteYear(rxShortWordMonthDay.cap(3).size(), year);
	if (rxShortWordMonthDay.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseLongWordMonthDay(QDate &date){
	//Get days
	int day = rxLongWordMonthDay.cap(2).toInt();
	//Get Months
	int month = QDate::fromString(rxLongWordMonthDay.cap(1), "MMMM").month();
	//Get Years
	int year = rxLongWordMonthDay.cap(3).toInt();
	autoCompleteYear(rxLongWordMonthDay.cap(3).size(), year);
	if (rxLongWordMonthDay.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseShortWeekDays(QDate &date, int &dayOfWeek){
	QDate testDate = QDate::currentDate();
	int i;
	for(i=1; i<=7; ++i){
		testDate = testDate.addDays(1);
		if(testDate.toString("ddd").toLower() == rxShortWeekDays.cap(1).toLower()){
			dayOfWeek = dayOFWeekToInt(rxShortWeekDays.cap(1));
			dayOfWeek = i;
			date = testDate;
			return true;
		}
	}
	return false;
}

bool DateTimeParser::parseLongWeekDays(QDate &date, int &dayOfWeek){
	QDate testDate = QDate::currentDate();
	int i;
	for(i=1; i<=7; ++i){
		testDate = testDate.addDays(1);
		if(testDate.toString("dddd").toLower() == rxLongWeekDays.cap(1).toLower()){
			dayOfWeek = dayOFWeekToInt(rxLongWeekDays.cap(1));
			date = testDate;
			return true;
		}
	}
	return false;
}

bool DateTimeParser::parseToday(QDate &date){
	//Today
	date = QDate::currentDate();
	return true;
}

bool DateTimeParser::parseTomorrow(QDate &date){		
	//Tomorrow
	date = QDate::currentDate().addDays(1);
	return true;
}

bool DateTimeParser::parseYesterday(QDate &date){		
	//Yesterday
	date = QDate::currentDate().addDays(-1);
	return true;
}

bool DateTimeParser::parseDayAfter(QDate &date){		
	//The day after tomorrow
	date = QDate::currentDate().addDays(2);
	return true;
}

bool DateTimeParser::parseNextWeek(QDate &date, int &dayOfWeek){		
	//Next Week
	dayOfWeek = 0;
	date = QDate::currentDate().addDays(7);
	return true;
}

int DateTimeParser::guessYear(int &day, int &month){
	QDate testDate;
	int tempDay = day;
	int tempMonth = month;
	int currYear = testDate.currentDate().year();

	if(day == 29 && month == 2){
		if(testDate.currentDate().month() <= 2 && (currYear) % 4 != 0){
			day = 28;
			tempDay = 28;
		}
		if(testDate.currentDate().month() > 2 && (currYear+1) % 4 != 0){
			day = 28;
			tempDay = 28;
		}
	}
	testDate.setDate(currYear, tempMonth, tempDay);
	if(testDate.isValid() && testDate.operator>=(testDate.currentDate())){
		return currYear;
	}
	return currYear+1;
}

void DateTimeParser::autoCompleteYear(int size, int &year){
	if(size == 2 || size == 1){
		year+=2000;
	}
	return;
}

int DateTimeParser::dayOFWeekToInt(QString dayOfWeek){
	for(int i=1; i<8; i++){
		if(QDate::longDayName(i).toLower() == dayOfWeek.toLower()){
			return i;
		}
	}
	return -1;
}