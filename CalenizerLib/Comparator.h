// v 1.1 
// revamped sorting algo
// added new sortbyenddate comparator

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "TaskFloat.h"
#include "DateTime.h"

class Comparator {

private:

public:
	Comparator();

	static bool sortByStartDate(const Task*, const Task*);
	static bool sortByEndDate(const Task*, const Task*);
	static bool sortByCompleteness(const Task*, const Task*);
	static bool sortByTaskType(const Task*, const Task*);
};
#endif