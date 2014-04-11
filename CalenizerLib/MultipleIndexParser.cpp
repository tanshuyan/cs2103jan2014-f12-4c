// MultipleIndexParser.cpp

#include "MultipleIndexParser.h"

QRegExp MultipleIndexParser::RX_NEGATIVE_INDEX("(?:^|\\D)\\s*(-\\d+)", Qt::CaseInsensitive);
QRegExp MultipleIndexParser::RX_TO("(\\d+)\\s*(?:to|-|until|til)\\s*(\\d+)", Qt::CaseInsensitive);
QRegExp MultipleIndexParser::RX_INDEX("\\b(\\d+)\\b");

const QString ZERO_INDEX = "0";

MultipleIndexParser::MultipleIndexParser() {
}

std::vector<int> MultipleIndexParser::parseMultipleIndex(QString descString) {
	_index.clear();
	//Search for negative indexes and turn them zeroes
	int pos = 0; 
	pos = RX_NEGATIVE_INDEX.indexIn(descString, pos);
	while(pos != -1){
		descString.replace(RX_NEGATIVE_INDEX.pos(1), RX_NEGATIVE_INDEX.cap(1).length(), ZERO_INDEX);
		pos = RX_NEGATIVE_INDEX.indexIn(descString, pos);
	}
	//Search for "index to index" format
	pos = 0;
	pos = RX_TO.indexIn(descString, pos);
	while(pos != -1){
		int start = RX_TO.cap(1).toInt();
		int end = RX_TO.cap(2).toInt();
		if(start > end)
		{
			//swap
			int temp = start;
			start = end;
			end = temp;
		}
		// eg: 7 to 11, populate 7,8,9,10,11 and store in the vector
		for(int i = start; i <= end; i++) {
			_index.push_back(i);
		}
		descString.remove(pos, RX_TO.matchedLength());
		pos = RX_TO.indexIn(descString, pos);
	}
	//Search for lone indexes
	pos = 0;
	pos = RX_INDEX.indexIn(descString, pos);
	while(pos != -1){
		int index = RX_INDEX.cap(1).toInt();
		_index.push_back(index);
		descString.remove(pos, RX_INDEX.matchedLength());
		pos = RX_INDEX.indexIn(descString, pos);
	}
	
	std::sort(_index.begin(), _index.end()); 
	// create a unique vector
	_index.erase(std::unique(_index.begin(), _index.end()), _index.end()); 
	return _index;
}













