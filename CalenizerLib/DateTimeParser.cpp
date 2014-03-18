//DateTimeParser.cpp
//v 1.5
#include "DateTimeParser.h"

QRegExp DateTimeParser::rxEmpty("(^\\s*$)");
QRegExp DateTimeParser::rxOn("\\b(on|by|at)\\b",Qt::CaseInsensitive);

QRegExp DateTimeParser::rxHourMinAP("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(?::?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourAP("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxHourColMin("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:\\s*)(?::)(?:\\s*)(\\d{2})",Qt::CaseInsensitive);

//const QRegExp rxWorded("(\\d{1,2})(?:\\s*)(:?)(?:\\s*)(\\d{2})(?:\\s*)(am|pm)",Qt::CaseInsensitive);
QRegExp DateTimeParser::rxDashesSlashes("(?:at|on|by)?(?:\\s*)(\\d{1,2})(?:/|-|.)(\\d{1,2})(?:/|-|.)?(\\d{1,4})?",Qt::CaseInsensitive);

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

	//check for HourMinAP format (1000 AM)
	pos = rxHourMinAP.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourMinAP.matchedLength());
		return parseHourMinAP(rxHourMinAP, time);
	}

	//check for HourAP format (10 AM)
	pos = rxHourAP.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourAP.matchedLength());
		return parseHourAP(rxHourAP, time);
	}

	//check for HourColMin format (10:00)
	pos = rxHourColMin.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxHourColMin.matchedLength());
		return parseHourColMin(rxHourColMin, time);
	}
	return false;
}

bool DateTimeParser::extractDate(QString &input, QDate &date){
	int pos;

	//check for DashesSlashes format (31/1/2014, 31-1-2014)
	pos = rxDashesSlashes.indexIn(input);
	if(pos != -1){
		input.remove(pos, rxDashesSlashes.matchedLength());
		return parseDashesSlashes(rxDashesSlashes, date);
	}
	return false;
}

bool DateTimeParser::parseHourMinAP(QRegExp &rxHourMinAP, QTime &time){
	
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

bool DateTimeParser::parseHourAP(QRegExp &rxHourColMin, QTime &time){
	
	//Get hours
	int hour = rxHourColMin.cap(1).toInt();
	
	if(hour > 12 || hour < 1){
		return false;
	}
	if(hour == 12){
		hour = 0;
	}
	if (rxHourColMin.cap(2).contains("pm", Qt::CaseInsensitive)){
		hour += 12;
	}
	time.setHMS(hour, 0, 0);
	return true;
}

bool DateTimeParser::parseHourColMin(QRegExp &rxHourColMin, QTime &time){
	
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

bool DateTimeParser::parseDashesSlashes(QRegExp &rxDashesSlashes, QDate &date){
		
	//Get days
	int day = rxDashesSlashes.cap(1).toInt();
	//Get Months
	int month = rxDashesSlashes.cap(2).toInt();;
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