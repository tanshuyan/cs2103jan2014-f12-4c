//@author A0004695A

// Comparator.h

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "TaskFloat.h"
#include "DateTime.h"

class Comparator {
public:
	Comparator();

	static bool sortByStartDate(const Task* a, const Task* b);
	static bool sortByEndDate(const Task* a, const Task* b);
	static bool sortByCompleteness(const Task* a, const Task* b);
	static bool sortByTaskType(const Task* a, const Task* b);
};
#endif