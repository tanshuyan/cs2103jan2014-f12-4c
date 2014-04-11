// Comparator.cpp

#include "Comparator.h"

const int RANK_ZERO = 0;
const int RANK_ONE = 1;
const int RANK_TWO = 2;

bool Comparator::sortByStartDate(const Task* a, const Task* b) {
	DateTime dateTimeA;
	DateTime dateTimeB;
	if(a->getTaskType() == TaskDeadline::TASK_DEADLINE) {
		dateTimeA = a->getDeadline();
	} else{
		dateTimeA = a->getStartDate();
	}
	if(b->getTaskType() == TaskDeadline::TASK_DEADLINE) {
		dateTimeB = b->getDeadline();
	} else{
		dateTimeB = b->getStartDate();
	}
	return (dateTimeA < dateTimeB);
}

bool Comparator::sortByEndDate(const Task* a, const Task* b) {
	return (a->getDeadline() < b->getDeadline());
}

bool Comparator::sortByCompleteness(const Task* a, const Task* b) {
	int rankA;
	int rankB;
	if(a->getCompleteStatus()){
		rankA = RANK_ONE;
	} else{
		rankA = RANK_ZERO;
	}
	if(b->getCompleteStatus()){
		rankB = RANK_ONE;
	} else{
		rankB = RANK_ZERO;
	}
	return (rankA < rankB);
}

bool Comparator::sortByTaskType(const Task* a, const Task* b) {
	int rankA;
	int rankB;
	if(a->getTaskType() == TaskTimed::TASK_TIMED){
		rankA = RANK_ZERO;
	} else if(a->getTaskType() == TaskDeadline::TASK_DEADLINE){
		rankA = RANK_ONE;
	} else{
		rankA = RANK_TWO;
	}
	if(b->getTaskType() == TaskTimed::TASK_TIMED){
		rankB = RANK_ZERO;
	} else if(b->getTaskType() == TaskDeadline::TASK_DEADLINE){
		rankB = RANK_ONE;
	} else{
		rankB = RANK_TWO;
	}
	return (rankA < rankB);
}