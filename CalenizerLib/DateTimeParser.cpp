//DateTimeParser.cpp

#include "DateTimeParser.h"

QRegExp DateTimeParser::RX_EMPTY("(^\\s*$)");

QRegExp DateTimeParser::RX_HOUR_MIN_AP("(?:at|on|by)?\\s*(\\d{1,2})\\s*(?::?)\\s*(\\d{2})\\s*(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_HOUR_AP("(?:at|on|by)?\\s*(\\d{1,2})\\s*(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_HOUR_COL_MIN("(?:at|on|by)?\\s*(\\d{1,2})\\s*(?::)\\s*(\\d{2})",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_AT_HOUR("(?:at|by)\\s*(\\d{1,2})($|\\s+)(?!jan|/|-|\\.|jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)",Qt::CaseInsensitive);

QRegExp DateTimeParser::RX_DASHES_SLASHES("(?:at|on|by)?\\s*(\\d{1,2})(?:/|-|\\.)(\\d{1,2})(?:/|-|\\.)?(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_DAY_SHORT_MONTH("(?:at|on|by)?\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\s*(?:of)?\\s*(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_DAY_LONG_MONTH("(?:at|on|by)?\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\s*(?:of)?\\s*(january|february|march|april|may|june|july|august|september|october|november|december)\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_SHORT_MONTH_DAY("(?:at|on|by)?\\s*(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\b\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_LONG_MONTH_DAY("(?:at|on|by)?\\s*(january|february|march|april|may|june|july|august|september|october|november|december)\\b\\s*(?:the)?\\s*(\\d{1,2})(?:st|nd|rd|th)?\\b\\s*(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_SHORT_WEEK_DAYS("(?:on|by)?\\s*(?:the|this)?\\s*(?:next|coming)?\\s*(sun|mon|tue|tues|wed|thu|thur|thurs|fri|sat)\\b",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_LONG_WEEK_DAYS("(?:on|by)?\\s*(?:the|this)?\\s*(?:next|coming)?\\s*(sunday|monday|tuesday|wednesday|thursday|friday|saturday)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_TODAY("(?:by)?\\s*(today|tdy|td)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_TOMORROW("(?:by)?\\s*(tomorrow|tommorrow|tommorow|tmr|tomolo|tml)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_YESTERDAY("(?:since)?\\s*(yesterday|ystd|ytd|yest)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_DAY_AFTER("(?:by)?\\s*(the)?\\s*(day)\\s*(after|aft)\\s*(tomorrow|tommorrow|tommorow|tmr)",Qt::CaseInsensitive);
QRegExp DateTimeParser::RX_NEXT_WEEK("(?:by)?\\s*(next|nxt)\\s*(week|wk)",Qt::CaseInsensitive);

QRegExp DateTimeParser::RX_DAYWORDS("(("+RX_TODAY.pattern()
									+")|("+RX_TOMORROW.pattern()
									+")|("+RX_YESTERDAY.pattern()
									+")|("+RX_YESTERDAY.pattern()
									+")|("+RX_DAY_AFTER.pattern()
									+")|("+RX_NEXT_WEEK.pattern()
									+")|("+RX_SHORT_WEEK_DAYS.pattern()
									+")|("+RX_LONG_WEEK_DAYS.pattern()
									+"))",Qt::CaseInsensitive);

DateTimeParser::DateTimeParser(){
}

bool DateTimeParser::parseString(QString input, QDate &outputDate, QTime &outputTime, int &dayOfWeek){
	QDate nullDate;
	QTime nullTime;
	outputDate = nullDate;
	outputTime = nullTime;
	//if the input string is empty, or only contains white spaces, the keyword is assumed to be part of the description
	if (RX_EMPTY.exactMatch(input)){
		return false;
	}
	bool isInvalidTime = !extractTime(input, outputTime);
	if (isInvalidTime){
		throw (InvalidDateTimeException("Invalid time entered"));
	}
	bool isInvalidDate = !extractDate(input, outputDate, dayOfWeek);
	if (isInvalidDate){
		throw (InvalidDateTimeException("Invalid date entered"));
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
	pos = RX_HOUR_MIN_AP.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_HOUR_MIN_AP.matchedLength());
		return parseHourMinAP(time);
	}
	//check for HourAP format (10 AM)
	pos = RX_HOUR_AP.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_HOUR_AP.matchedLength());
		return parseHourAP(time);
	}
	//check for HourColMin format (10:00)
	pos = RX_HOUR_COL_MIN.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_HOUR_COL_MIN.matchedLength());
		return parseHourColMin(time);
	}
	//check for AtHour format (at 10)
	pos = RX_AT_HOUR.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_AT_HOUR.matchedLength());
		return parseAtHour(time);
	}
	return true;
}

bool DateTimeParser::extractDate(QString &input, QDate &date, int &dayOfWeek){
	int pos;
	dayOfWeek = -1;
	//check for full month format (3rd december)
	pos = RX_DAY_LONG_MONTH.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_DAY_LONG_MONTH.matchedLength());
		return parseDayLongWordMonth(date);
	}
	//check for abbreviated month format (3rd dec)
	pos = RX_DAY_SHORT_MONTH.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_DAY_SHORT_MONTH.matchedLength());
		return parseDayShortWordMonth(date);
	}
	//check for full month format (december 3rd)
	pos = RX_LONG_MONTH_DAY.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_LONG_MONTH_DAY.matchedLength());
		return parseLongWordMonthDay(date);
	}
	//check for abbreviated month format (dec 3rd)
	pos = RX_SHORT_MONTH_DAY.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_SHORT_MONTH_DAY.matchedLength());
		return parseShortWordMonthDay(date);
	}
	//check for DashesSlashes format (31/1/2014, 31-1-2014)
	pos = RX_DASHES_SLASHES.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_DASHES_SLASHES.matchedLength());
		return parseDashesSlashes(date);
	}
	//check for short week format (sun, mon)
	pos = RX_SHORT_WEEK_DAYS.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_SHORT_WEEK_DAYS.matchedLength());
		return parseShortWeekDays(date, dayOfWeek);
	}
	//check for long week format (sunday, monday)
	pos = RX_LONG_WEEK_DAYS.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_LONG_WEEK_DAYS.matchedLength());
		return parseLongWeekDays(date, dayOfWeek);
	}
	//check for "Today" words
	pos = RX_TODAY.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_TODAY.matchedLength());
		return parseToday(date);
	}
	//check for "the day after tomorrow" words
	pos = RX_DAY_AFTER.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_DAY_AFTER.matchedLength());
		return parseDayAfter(date);
	}
	//check for "Tomorrow" words
	pos = RX_TOMORROW.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_TOMORROW.matchedLength());
		return parseTomorrow(date);
	}
	//check for "Yesterday" words
	pos = RX_YESTERDAY.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_YESTERDAY.matchedLength());
		return parseYesterday(date);
	}
	//check for "next week" words
	pos = RX_NEXT_WEEK.indexIn(input);
	if(pos != -1){
		input.remove(pos, RX_NEXT_WEEK.matchedLength());
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
	int hour = RX_HOUR_MIN_AP.cap(1).toInt();
	//Get minutes
	int minute = RX_HOUR_MIN_AP.cap(2).toInt();

 	if(hour > 12 || hour < 1 || minute < 0 || minute > 59){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (RX_HOUR_MIN_AP.cap(3).contains("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, minute, 0);
	return true;
}

bool DateTimeParser::parseHourAP(QTime &time){
	//Get hours
	int hour = RX_HOUR_AP.cap(1).toInt();
	if(hour > 12 || hour < 1){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (RX_HOUR_AP.cap(2).contains("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, 0, 0);
	return true;
}

bool DateTimeParser::parseHourColMin(QTime &time){
	//Get hours
	int hour = RX_HOUR_COL_MIN.cap(1).toInt();
	//Get minutes
	int minute = RX_HOUR_COL_MIN.cap(2).toInt();
		
	if(hour > 23 || hour < 0 || minute < 0 || minute > 59){
		return false;
	}
	//In the case that the user types anything from 1:00 to 6:00, regard it as pm
	if(RX_HOUR_COL_MIN.cap(1).size() == 1){
		if(hour >= 1 && hour <= 6){
			hour += 12;
		}
	}
	time.setHMS(hour, minute, 0);
	return true;
}

bool DateTimeParser::parseAtHour(QTime &time){
	//Get hours
	int hour = RX_AT_HOUR.cap(1).toInt();
		
	if(hour > 12 || hour < 0){
		return false;
	}
	//In the case that the user types anything from 1:00 to 6:00, regard it as pm
	if(hour >= 1 && hour <= 6){
		hour += 12;
	}
	time.setHMS(hour, 0, 0);
	return true;
}
//Date Parsers

bool DateTimeParser::parseDashesSlashes(QDate &date){
	//Get days
	int day = RX_DASHES_SLASHES.cap(1).toInt();
	//Get Months
	int month = RX_DASHES_SLASHES.cap(2).toInt();
	//Get Years
	int year = RX_DASHES_SLASHES.cap(3).toInt();
	autoCompleteYear(RX_DASHES_SLASHES.cap(3).size(), year);
	if(RX_DASHES_SLASHES.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseDayShortWordMonth(QDate &date){
	//Get days
	int day = RX_DAY_SHORT_MONTH.cap(1).toInt();
	//Get Months
	int month = QDate::fromString(RX_DAY_SHORT_MONTH.cap(2), "MMM").month();
	//Get Years
	int year = RX_DAY_SHORT_MONTH.cap(3).toInt();
	autoCompleteYear(RX_DAY_SHORT_MONTH.cap(3).size(), year);
	if (RX_DAY_SHORT_MONTH.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseDayLongWordMonth(QDate &date){
	//Get days
	int day = RX_DAY_LONG_MONTH.cap(1).toInt();
	//Get Months
	int month = QDate::fromString(RX_DAY_LONG_MONTH.cap(2), "MMMM").month();
	//Get Years
	int year = RX_DAY_LONG_MONTH.cap(3).toInt();
	autoCompleteYear(RX_DAY_LONG_MONTH.cap(3).size(), year);
	if (RX_DAY_LONG_MONTH.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseShortWordMonthDay(QDate &date){
	//Get days
	int day = RX_SHORT_MONTH_DAY.cap(2).toInt();
	//Get Months
	int month = QDate::fromString(RX_SHORT_MONTH_DAY.cap(1), "MMM").month();
	//Get Years
	int year = RX_SHORT_MONTH_DAY.cap(3).toInt();
	autoCompleteYear(RX_SHORT_MONTH_DAY.cap(3).size(), year);
	if (RX_SHORT_MONTH_DAY.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseLongWordMonthDay(QDate &date){
	//Get days
	int day = RX_LONG_MONTH_DAY.cap(2).toInt();
	//Get Months
	int month = QDate::fromString(RX_LONG_MONTH_DAY.cap(1), "MMMM").month();
	//Get Years
	int year = RX_LONG_MONTH_DAY.cap(3).toInt();
	autoCompleteYear(RX_LONG_MONTH_DAY.cap(3).size(), year);
	if (RX_LONG_MONTH_DAY.pos(3) == -1){
		year = guessYear(day, month);
	}
	return date.setDate(year, month, day);
}

bool DateTimeParser::parseShortWeekDays(QDate &date, int &dayOfWeek){
	QDate testDate = QDate::currentDate();
	int i;
	for(i=1; i<=7; ++i){
		testDate = testDate.addDays(1);
		if(testDate.toString("ddd").toLower() == RX_SHORT_WEEK_DAYS.cap(1).toLower()){
			dayOfWeek = dayOFWeekToInt(RX_SHORT_WEEK_DAYS.cap(1));
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
		if(testDate.toString("dddd").toLower() == RX_LONG_WEEK_DAYS.cap(1).toLower()){
			dayOfWeek = dayOFWeekToInt(RX_LONG_WEEK_DAYS.cap(1));
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