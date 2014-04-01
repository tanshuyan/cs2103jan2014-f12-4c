// Comparator.cpp
// v1.0

#include "Comparator.h"

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_TIMED = "TIMED";
const std::string TASK_DEADLINE = "DEADLINE";

bool Comparator::sortTimedTask(const Task* a, const Task* b) {
	return (a->getStartDate() < b->getStartDate()); 
}

bool Comparator::sortDeadlineTask(const Task* a, const Task* b) {
	return (a->getDeadline() < b->getDeadline());
}

bool Comparator::sortByCompleteness(const Task* a, const Task* b) {
	return (a->getCompleteStatus() == false && b->getCompleteStatus());
	/*
	if(a->getCompleteStatus() && b->getCompleteStatus() == false) {
		//return (a->getCompleteStatus() && b->getCompleteStatus());
		return (1<0);
	}
	return (1>0);*/
}

bool Comparator::sortByDate(const Task* a, const Task* b) {
	if(a->getTaskType() == b->getTaskType()) {
		if(a->getTaskType() == TASK_TIMED) { // a and b are timed tasks
			return (a->getStartDate() < b->getStartDate()); 
		}
		if(a->getTaskType() == TASK_DEADLINE) { // a and b are deadline tasks
			return (a->getDeadline() < b->getDeadline());
		}
		//if(a->getTaskType() == TASK_FLOAT) { // a and b are floating tasks
		//	return true;
		//}
	}
	if(a->getTaskType() == TASK_TIMED && b->getTaskType() == TASK_DEADLINE) {
		return (a->getStartDate() < b->getDeadline());
	}
	if(a->getTaskType() == TASK_DEADLINE && b->getTaskType() == TASK_TIMED) { 
		return (a->getDeadline() < b->getStartDate());
	}
	if(a->getTaskType() == TASK_FLOAT) { // a is float, at the bottom
		return (1<0);
	}
	//if(b->getTaskType() == TASK_FLOAT) { 
	//	return true;
	//}
	return (1>0);
}

bool Comparator::matchTask(const Task* a, const Task* b) {
	return ((a->getTaskType() == b->getTaskType()) &&
			(a->getTaskDesc() == b->getTaskDesc()) && 
			(a->getCompleteStatus() == b->getCompleteStatus()) &&
			(a->getDeadline() == b->getDeadline()) &&
			(a->getStartDate() == b->getStartDate()));
}