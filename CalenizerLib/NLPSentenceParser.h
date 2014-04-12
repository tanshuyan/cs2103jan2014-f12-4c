//@author A0097286M

//NLPSentenceParser.h

#ifndef NLPSENTENCEPARSER_H
#define NLPSENTENCEPARSER_H

#include <QString>
#include <QRegExp>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "MultipleIndexParser.h"

class NLPSentenceParser{
private:
	MultipleIndexParser _multipleIndexParser;
	static QRegExp RX_ALL;
	static QRegExp RX_BEGIN;
	static QRegExp RX_END;
	static QRegExp RX_CONTAIN;
	static QRegExp RX_EXACT;
	static QRegExp RX_COMPLETE;
	static QRegExp RX_INCOMPLETE;

	bool search(QString inputString, QRegExp &rx);
	std::vector<int> parseAll(const std::vector<Task*> &_displayList);
	std::vector<int> parseSearchTerm(const std::vector<Task*> &_displayList, QRegExp &rx);
	std::vector<int> parseComplete(const std::vector<Task*> &_displayList);
	std::vector<int> parseIncomplete(const std::vector<Task*> &_displayList);

public:
	NLPSentenceParser();
	std::vector<int> parseSentence(QString inputString, const std::vector<Task*> &_displayList);
};
#endif