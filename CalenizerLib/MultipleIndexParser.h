//MultipleIndexParser.h
//v 1.0

#ifndef MULTIPLEINDEXPARSER_H
#define MULTIPLEINDEXPARSER_H

#include <string>
#include <QRegExp>
#include <vector>
#include <algorithm>
//All functions return false if any error occurs
class MultipleIndexParser{
private:

	static QRegExp RX_TO;
	static QRegExp RX_INDEX;
	std::vector<int> _index;

public:
	MultipleIndexParser();
	std::vector<int> parseMultipleIndex(std::string);
};
#endif