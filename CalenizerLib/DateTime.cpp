//DateTime.cpp

#include "DateTime.h"

DateTime::DateTime(){
}

DateTime::DateTime(QDate date, QTime time){
	_date = date;
	_time = time;
}

bool DateTime::setDate(int day, int month, int year){
	return _date.setDate(year, month, day);
}

bool DateTime::setTime(int hour, int min=0){
	return _time.setHMS(hour, min, 0);
}

bool DateTime::setDate(QDate date){
	return _date.setDate(date.year(), date.month(), date.day());
}

bool DateTime::setTime(QTime time){
	return _time.setHMS(time.hour(), time.minute(), 0);
}

QDate DateTime::getDate(){
	return _date;
}

QTime DateTime::getTime(){
	return _time;
}

void DateTime::setCurrDateTime(){
	_date = QDate::currentDate();
	_time = QTime::currentTime();
	return;
}

std::string DateTime::dateToString(bool displayTodayAsWord){
	if(displayTodayAsWord && _date == _date.currentDate()){
		return "Today";
	}
	if(displayTodayAsWord && _date == (_date.currentDate()).addDays(1)){
		return "Tomorrow";
	}
	if(displayTodayAsWord && _date == (_date.currentDate()).addDays(-1)){
		return "Yesterday";
	}
	QString format="dd MMM yyyy";
	QString output=_date.toString(format);
	return output.toStdString();
}

std::string DateTime::dayToString(){
	QString format="ddd";
	QString output=_date.toString(format);
	return output.toStdString();
}

std::string DateTime::timeToString(){
	QString format="h:mm ap";
	QString output=_time.toString(format);
	return output.toStdString();
}

std::string DateTime::dataToString(){
	std::string dateString = _date.toString("dd/MM/yyyy").toStdString();
	std::string timeString = _time.toString("hh:mm").toStdString();

	return dateString + " " + timeString;
}

void DateTime::dataFromString(std::string data){
	QRegExp rxDate("(\\d{2})(/)(\\d{2})(/)(\\d{4})(\\s)");
	QString dataStr(data.c_str());
	QString dateString;
	QString timeString;

	int pos = rxDate.indexIn(dataStr);
	int len = rxDate.matchedLength();
	if(pos != -1){
		dateString = dataStr.mid(pos, len);
		dataStr.remove(pos, len);
	}

	_date = QDate::fromString(dateString, "dd/MM/yyyy ");
	timeString = dataStr;
	_time = QTime::fromString(timeString, "hh:mm");

	return;
}

//to arrange the dates during sorting and also to check for clashes
//To coder: remember to compare year, then month, then day.
bool DateTime::operator==(DateTime datetimeToCompare){
	if(_date.operator==(datetimeToCompare.getDate()) && _time.operator==(datetimeToCompare.getTime())){
		return true;
	}
	return false;
}
bool DateTime::operator!=(DateTime datetimeToCompare){
	if(_date.operator!=(datetimeToCompare.getDate()) || _time.operator!=(datetimeToCompare.getTime())){
		return true;
	}
	return false;
}
bool DateTime::operator<(DateTime datetimeToCompare){
	if(_date.operator<(datetimeToCompare.getDate())){
		return true;
	}
	if(_date.operator==(datetimeToCompare.getDate()) && _time.operator<(datetimeToCompare.getTime())){
		return true;
	}
	return false;
}

bool DateTime::operator>(DateTime datetimeToCompare){
	if(_date.operator>(datetimeToCompare.getDate())){
		return true;
	}
	if(_date.operator==(datetimeToCompare.getDate()) && _time.operator>(datetimeToCompare.getTime())){
		return true;
	}
	return false;
}