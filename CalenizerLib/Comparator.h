// v 1.0

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

	static bool sortTimedTask(const Task*, const Task*);
	static bool sortDeadlineTask(const Task*, const Task*);
	static bool sortByDate(const Task*, const Task*);
	static bool sortByCompleteness(const Task*, const Task*);
	static bool matchTask(const Task*, const Task*);
};
#endif