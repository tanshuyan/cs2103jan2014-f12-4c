// Comparator.cpp
// v 1.1 
// revamped sorting algo
// added new sortbyenddate comparator
#include "Comparator.h"

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_TIMED = "TIMED";
const std::string TASK_DEADLINE = "DEADLINE";

bool Comparator::sortByCompleteness(const Task* a, const Task* b) {
	return (a->getCompleteStatus() == false && b->getCompleteStatus());
}

bool Comparator::sortByEndDate(const Task* a, const Task* b) {

	if(a->getTaskType() != TASK_FLOAT && b->getTaskType() != TASK_FLOAT) {
		return (a->getDeadline() < b->getDeadline());
	}

	if(a->getTaskType() == TASK_FLOAT) {
		return (1 < 0);
	}
	
	return (1>0);
}

bool Comparator::sortByDate(const Task* a, const Task* b) {
	if(a->getTaskType() == b->getTaskType()) {
		if(a->getTaskType() == TASK_TIMED) { 
			// a and b are timed tasks
			return (a->getStartDate() < b->getStartDate()); 
		}
		if(a->getTaskType() == TASK_DEADLINE) { 
			// a and b are deadline tasks
			return (a->getDeadline() < b->getDeadline());
		}
	}
	if(a->getTaskType() == TASK_TIMED && b->getTaskType() == TASK_DEADLINE) {
		return (a->getStartDate() < b->getDeadline());
	}
	if(a->getTaskType() == TASK_DEADLINE && b->getTaskType() == TASK_TIMED) { 
		return (a->getDeadline() < b->getStartDate());
	}
	if(a->getTaskType() == TASK_FLOAT) { 
		// a is float, at the bottom
		return (1<0);
	}
	// a and b are float, dont swap
	return (1>0);
}

bool Comparator::matchTask(const Task* a, const Task* b) {
	return ((a->getTaskType() == b->getTaskType()) &&
			(a->getTaskDesc() == b->getTaskDesc()) && 
			(a->getCompleteStatus() == b->getCompleteStatus()) &&
			(a->getDeadline() == b->getDeadline()) &&
			(a->getStartDate() == b->getStartDate()));
}