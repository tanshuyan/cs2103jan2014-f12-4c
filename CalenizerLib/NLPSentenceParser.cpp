//NLPSentenceParser.cpp
//v 1.0

#include "NLPSentenceParser.h"

QRegExp NLPSentenceParser::RX_ALL("^\\s*(?:all)\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_BEGIN("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:begin|beginning|start|starting)\\s*(?:with)?\\s*\"(.+)\"\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_END("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:end|ending)\\s*(?:with|in)?\\s*\"(.+)\"\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_CONTAIN("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:contains?|containing|with)\\s*\"(.+)\"\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_EXACT("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:are)?\\s*(?:match|matches|matching|containing)?(?:only)?\\s*\"(.+)\"\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_COMPLETE("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:are)?\\s*(?:completed?)\\s*$", Qt::CaseInsensitive);
QRegExp NLPSentenceParser::RX_INCOMPLETE("^\\s*(?:all)?\\s*(?:the)?\\s*(?:tasks?|events?)?\\s*(?:that)?\\s*(?:are)?\\s*(?:incompleted?|not+\\s+complete)\\s*$", Qt::CaseInsensitive);

NLPSentenceParser::NLPSentenceParser(){
}

std::vector<int> NLPSentenceParser::parseSentence(QString inputString, const std::vector<Task*> &_displayList){
	if(search(inputString, RX_ALL)){
		return parseAll(_displayList);
	}
	if(search(inputString, RX_BEGIN)){
		QRegExp rx("(^" + QRegExp::escape(RX_BEGIN.cap(1).trimmed()) + ")", Qt::CaseInsensitive);
		return parseSearchTerm(_displayList, rx);
	}
	if(search(inputString, RX_END)){
		QRegExp rx("(" + QRegExp::escape(RX_END.cap(1).trimmed()) + "$)", Qt::CaseInsensitive);
		return parseSearchTerm(_displayList, rx);
	}
	if(search(inputString, RX_CONTAIN)){
		QRegExp rx("(" + QRegExp::escape(RX_CONTAIN.cap(1).trimmed()) + ")", Qt::CaseInsensitive);
		QString lalala = RX_BEGIN.cap(1).trimmed();
		return parseSearchTerm(_displayList, rx);
	}
	if(search(inputString, RX_EXACT)){
		QRegExp rx("(^" + QRegExp::escape(RX_EXACT.cap(1).trimmed()) + "$)", Qt::CaseInsensitive);
		return parseSearchTerm(_displayList, rx);
	}
	if(search(inputString, RX_COMPLETE)){
		return parseComplete(_displayList);
	}
	if(search(inputString, RX_INCOMPLETE)){
		return parseIncomplete(_displayList);
	}
	throw SentenceFailedToParse();
	return;
}

bool NLPSentenceParser::search(QString inputString, QRegExp &rx){
	if(rx.indexIn(inputString) != -1){
		return true;
	}
	return false;
}

std::vector<int> NLPSentenceParser::parseAll(const std::vector<Task*> &_displayList){
	std::vector<int> indexList;
	for(int i = 1; i <= _displayList.size(); i++) {
		indexList.push_back(i);
	}
	return indexList;
}

std::vector<int> NLPSentenceParser::parseSearchTerm(const std::vector<Task*> &_displayList, QRegExp &rx){
	std::vector<int> indexList;
	int i = 1;
	for(std::vector<Task*>::const_iterator iter = _displayList.begin(); iter != _displayList.end(); iter++) {
		if(rx.indexIn((*iter)->getTaskDesc().c_str()) != -1){
			indexList.push_back(i);
		}
		i++;
	}
	return indexList;
}

std::vector<int> NLPSentenceParser::parseComplete(const std::vector<Task*> &_displayList){
	std::vector<int> indexList;
	int i = 1;
	for(std::vector<Task*>::const_iterator iter = _displayList.begin(); iter != _displayList.end(); iter++) {
		if((*iter)->getCompleteStatus() == true){
			indexList.push_back(i);
		}
		i++;
	}
	return indexList;
}

std::vector<int> NLPSentenceParser::parseIncomplete(const std::vector<Task*> &_displayList){
	std::vector<int> indexList;
	int i = 1;
	for(std::vector<Task*>::const_iterator iter = _displayList.begin(); iter != _displayList.end(); iter++) {
		if((*iter)->getCompleteStatus() == false){
			indexList.push_back(i);
		}
		i++;
	}
	return indexList;
}