//NLPSentenceParser.h
//v 1.0
#ifndef NLPSENTENCEPARSER_H
#define NLPSENTENCEPARSER_H

#include <QString>
#include <QRegExp>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "MultipleIndexParser.h"
//#include "NLPSentenceFunctions.h"

class NLPSentenceParser{
private:
	MultipleIndexParser _multipleIndexParser;
	static QRegExp RX_ALL;
	static QRegExp RX_BEGIN;
	static QRegExp RX_END;
	static QRegExp RX_CONTAIN;
	static QRegExp RX_EXACT;

	bool search(QString inputString, QRegExp &rx);
	std::vector<int> parseAll(const std::vector<Task*> &_displayList);
	std::vector<int> parseSearchTerm(const std::vector<Task*> &_displayList, QRegExp &rx);
	
public:
	NLPSentenceParser();
	std::vector<int> parseSentence(QString inputString, const std::vector<Task*> &_displayList);
};
#endif