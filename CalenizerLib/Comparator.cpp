// Comparator.cpp
// v 1.1 
// revamped sorting algo
// added new sortbyenddate comparator
#include "Comparator.h"

bool Comparator::sortByStartDate(const Task* a, const Task* b) {
	DateTime A;
	DateTime B;
	if(a->getTaskType() == TaskDeadline::TASK_DEADLINE) {
		A = a->getDeadline();
	} else{
		A = a->getStartDate();
	}
	if(b->getTaskType() == TaskDeadline::TASK_DEADLINE) {
		B = b->getDeadline();
	} else{
		B = b->getStartDate();
	}
	return (A<B);
}

bool Comparator::sortByEndDate(const Task* a, const Task* b) {
	return (a->getDeadline() < b->getDeadline());
}

bool Comparator::sortByCompleteness(const Task* a, const Task* b) {
	int A;
	int B;
	if(a->getCompleteStatus()){
		A = 1;
	} else{
		A = 0;
	}
	if(b->getCompleteStatus()){
		B = 1;
	} else{
		B = 0;
	}
	return (A<B);
}

bool Comparator::sortByTaskType(const Task* a, const Task* b) {
	int A;
	int B;
	if(a->getTaskType() == TaskTimed::TASK_TIMED){
		A = 0;
	} else if(a->getTaskType() == TaskDeadline::TASK_DEADLINE){
		A = 1;
	} else{
		A = 2;
	}
	if(b->getTaskType() == TaskTimed::TASK_TIMED){
		B = 0;
	} else if(a->getTaskType() == TaskDeadline::TASK_DEADLINE){
		B = 1;
	} else{
		B = 2;
	}
	return (A<B);
}

//bool Comparator::matchTask(const Task* a, const Task* b) {
//	return ((a->getTaskType() == b->getTaskType()) &&
//			(a->getTaskDesc() == b->getTaskDesc()) && 
//			(a->getCompleteStatus() == b->getCompleteStatus()) &&
//			(a->getDeadline() == b->getDeadline()) &&
//			(a->getStartDate() == b->getStartDate()));
//}