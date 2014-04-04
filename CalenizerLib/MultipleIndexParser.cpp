// MultipleIndexParser.cpp
// v1.0

#include "MultipleIndexParser.h"


QRegExp MultipleIndexParser::RX_TO("(\\d+)\\s*(?:to|-|until|til)\\s*(\\d+)", Qt::CaseInsensitive);

QRegExp MultipleIndexParser::RX_INDEX("(\\d+)");


MultipleIndexParser::MultipleIndexParser() {
}

std::vector<int> MultipleIndexParser::parseMultipleIndex(std::string userInput) {
	QString descString(userInput.c_str());
	_index.clear();
	int pos = 0; 
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
		for(int i = start; i <= end; i++) { // eg: 7 to 11, populate 7,8,9,10,11 and store in the vector
			_index.push_back(i);
		}
		descString.remove(pos, RX_TO.matchedLength());
		pos = RX_TO.indexIn(descString, pos);
	}
	
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













