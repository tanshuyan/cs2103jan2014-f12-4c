//DateTimeParser.cpp
//v 1.2
#include "DateTimeParser.h"

QRegExp DateTimeParser::rxEmpty("(^\\s*$)");
QRegExp DateTimeParser::rxOn("\\b(on|by|at)\\b",Qt::CaseInsensitive);

QRegExp DateTimeParser::rxHourMinAP("(\\d{1,2})(?:\\s*)(:?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourAP("(\\d{1,2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourColMin("(\\d{1,2})(?:\\s*)(:)(?:\\s*)(\\d{2})",Qt::CaseInsensitive);

//const QRegExp rxWorded("(\\d{1,2})(?:\\s*)(:?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDashesSlashes("(\\d{1,2})(/|-)(\\d{1,2})(/|-)?(\\d{1,4})?",Qt::CaseInsensitive);

QRegExp DateTimeParser::rxHourDigits("(\\d{1,2})");
QRegExp DateTimeParser::rxMinuteDigits("(\\d{1,2})");

QRegExp DateTimeParser::rxDayDigits("\\d{1,2}");
QRegExp DateTimeParser::rxMonthDigits("\\d{1,2}");
QRegExp DateTimeParser::rxYearDigits("\\d{1,4}");

DateTimeParser::DateTimeParser(){
}

bool DateTimeParser::parseString(std::string inputString, QDate &outputDate, QTime &outputTime){
	QString input(inputString.c_str());
	QDate nullDate;
	QTime nullTime;

	//if the input string is empty, or only contains white spaces, the keyword is assumed to be part of the description
	if (rxEmpty.exactMatch(input)){
		outputDate = nullDate;
		outputTime = nullTime;
		return false;
	}
	
	while(rxOn.indexIn(input) != -1){
		input.remove(rxOn.pos(), rxOn.matchedLength());
	}

	bool timeIsValid = extractTime(input, outputTime);
	if (!timeIsValid){
		outputTime = nullTime;
	}
	
	bool dateIsValid = extractDate(input, outputDate);
	if (!dateIsValid){
		outputDate = nullDate;
	}

	return input.trimmed().isEmpty();
}

bool DateTimeParser::extractTime(QString &input, QTime &time){
	int pos;
	int len;
	QString timeStr;

	//check for HourMinAP format (1000 AM)
	pos = rxHourMinAP.indexIn(input);
	if(pos != -1){
		timeStr = rxHourMinAP.cap();
		input.remove(pos, rxHourMinAP.matchedLength());
		return parseHourMinAP(timeStr, time);
	}

	//check for HourAP format (10 AM)
	pos = rxHourAP.indexIn(input);
	if(pos != -1){
		timeStr = rxHourAP.cap();
		input.remove(pos, rxHourAP.matchedLength());
		return parseHourAP(timeStr, time);
	}

	//check for HourColMin format (10:00)
	pos = rxHourColMin.indexIn(input);
	if(pos != -1){
		timeStr = rxHourColMin.cap();
		input.remove(pos, rxHourColMin.matchedLength());
		return parseHourColMin(timeStr, time);
	}
	return false;
}

bool DateTimeParser::extractDate(QString &input, QDate &date){

	int pos;
	QString dateStr;

	//check for DashesSlashes format (31/1/2014, 31-1-2014)
	pos = rxDashesSlashes.indexIn(input);
	if(pos != -1){
		dateStr = rxDashesSlashes.cap();
		input.remove(pos, rxDashesSlashes.matchedLength());
		return parseDashesSlashes(dateStr, date);
	}
	return false;
}

bool DateTimeParser::parseHourMinAP(QString &timeStr, QTime &time){
	
	//Get minutes
	int minute;
	getRxFromBack(timeStr, minute, rxMinuteDigits);
		
	//Get hours
	int hour;
	getRxFromFront(timeStr, hour, rxHourDigits);

 	if(hour > 12 || hour < 1 || minute < 0 || minute > 59){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (timeStr.endsWith("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, minute, 0);
	return true;
}

bool DateTimeParser::parseHourAP(QString &timeStr, QTime &time){
		
	//Get hours
	int hour;
	getRxFromFront(timeStr, hour, rxHourDigits);
	
	if(hour > 12 || hour < 1){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (timeStr.endsWith("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, 0, 0);
	return true;
}

bool DateTimeParser::parseHourColMin(QString &timeStr, QTime &time){
	
	//Get minutes
	int minute;
	getRxFromBack(timeStr, minute, rxMinuteDigits);
		
	//Get hours
	int hour;
	getRxFromFront(timeStr, hour, rxHourDigits);
		
	if(hour > 23 || hour < 0 || minute < 0 || minute > 59){
		return false;
	}
	time.setHMS(hour, minute, 0);
	return true;
}

/*
bool DateTimeParser::parseAtHour(QString &timeStr, QTime &time){
	QRegExp rxHourDigits("(\\d{1,2})");
	QRegExp rxMinuteDigits("(\\d{2})");
	//only used for checking toInt conversions
	bool *ok;
	
	//Get minutes
	int minPos = rxMinuteDigits.lastIndexIn(timeStr);	
	int minute = timeStr.mid(minPos, 2).toInt(ok);
	//qt_assert *ok is true, meaning toInt conversion is success
	timeStr.remove(minPos, 2);
		
	//Get hours
	int hourPos = rxHourDigits.indexIn(timeStr);	
	int hour = timeStr.mid(hourPos, rxHourDigits.matchedLength()).toInt(ok);
	//qt_assert *ok is true, meaning toInt conversion is success
		
	if(hour > 23 || hour < 1 || minute < 0 || minute > 59){
		return false;
	}
		
	time.setHMS(hour, minute, 0);
	return true;
}
*/

bool DateTimeParser::parseDashesSlashes(QString &dateStr, QDate &date){
		
	//Get days
	int day;
	getRxFromFront(dateStr, day, rxDayDigits);

	//Get Months
	int month;
	getRxFromFront(dateStr, month, rxMonthDigits);

	//Get Years
	int year;
	getRxFromFront(dateStr, year, rxYearDigits);

	if(rxYearDigits.matchedLength() == -1){
		year = guessYear(day, month);
	}

	return date.setDate(year, month, day);
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

bool DateTimeParser::getRxFromFront(QString &str, int &number, QRegExp &rx){ 
	//for checking toInt conversions
	bool *ok = false;

	int pos = rx.indexIn(str);	
	number = rx.cap().toInt(ok);
	//assert *ok is true, meaning toInt conversion is success
	str.remove(pos, rx.matchedLength());

	if (rx.matchedLength() == -1){
		return false;
	}
	return true;
}

bool DateTimeParser::getRxFromBack(QString &str, int &number, QRegExp &rx){ 
	//for checking toInt conversions
	bool *ok = false;

	int pos = rx.lastIndexIn(str);	
	number = rx.cap().toInt(ok);
	//assert *ok is true, meaning toInt conversion is success
	str.remove(pos, rx.matchedLength());

	if (rx.matchedLength() == -1){
		return false;
	}
	return true;
}