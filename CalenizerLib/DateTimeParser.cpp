//DateTimeParser.cpp
//v 2.1
#include "DateTimeParser.h"

QRegExp DateTimeParser::rxEmpty("(^\\s*$)");

QRegExp DateTimeParser::rxHourMinAP("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(?::?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourAP("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourColMin("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(?::)(?:\\s*)(\\d{2})",Qt::CaseInsensitive);

//const QRegExp rxWorded("(\\d{1,2})(?:\\s*)(:?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDashesSlashes("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:/|-|.)(\\d{1,2})(?:/|-|.)?(\\d{1,4})?",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxToday("(?:by)?(today|td|yesterday|ystd|the day after tomorrow)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxTomorrow("(?:by)?(tomorrow|tommorrow|tommorow|tmr)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxYesterday("(yesterday|ystd)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDayAfter("(?:by)?(the day after)(tomorrow|tommorrow|tommorow|tmr)",Qt::CaseInsensitive);

DateTimeParser::DateTimeParser(){
}

bool DateTimeParser::parseString(QString input, QDate &outputDate, QTime &outputTime){
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
	
	bool isInvalidDate = !extractDate(input, outputDate);
	if (isInvalidDate){
		throw (20);
	}

	return input.trimmed().isEmpty();
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

bool DateTimeParser::extractDate(QString &input, QDate &date){
	int pos;

	//check for DashesSlashes format (31/1/2014, 31-1-2014)
	pos = rxDashesSlashes.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDashesSlashes.matchedLength());
		return parseDashesSlashes(date);
	}

	return true;
}

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

bool DateTimeParser::parseDashesSlashes(QDate &date){
		
	//Get days
	int day = rxDashesSlashes.cap(1).toInt();
	//Get Months
	int month = rxDashesSlashes.cap(2).toInt();
	//Get Years
	int year = rxDashesSlashes.cap(3).toInt();

	if(rxDashesSlashes.pos(3) == -1){
		year = guessYear(day, month);
	}

	return date.setDate(year, month, day);
}

bool DateTimeParser::parseDateWords(QDate &date){
		
	//Get days
	int day = rxDashesSlashes.cap(1).toInt();
	//Get Months
	int month = rxDashesSlashes.cap(2).toInt();
	//Get Years
	int year = rxDashesSlashes.cap(3).toInt();

	if(rxDashesSlashes.pos(3) == -1){
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