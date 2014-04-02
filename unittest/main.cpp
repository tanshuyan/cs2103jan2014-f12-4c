// v1.0

#include <QtTest\Qttest>
#include <QtCore/QCoreApplication>
#include <QTest>
#include <QtTest\Qttest>
#include <qobject.h>
#include "taskStorage.h"
#include "Task.h"
#include "NLParser.h"
#include "Parser.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include <cstdlib>

class TaskTest : public QObject {
        Q_OBJECT
private:
        private slots:

                // Unit Test START

                void testDeadlineTask() {
					NLParser parser;
					std::string deadlineTaskString = "DEADLINE\ncs2013 is fun\n13/02/2014 14:00\nfalse\n";
					TaskDeadline* deadlineTaskPtr = new TaskDeadline;
					deadlineTaskPtr->stringToTask(deadlineTaskString);

					std::string expected = "DEADLINE cs2013 is fun 13/02/2014 14:00 false\n";
					QVERIFY(deadlineTaskPtr->outputToString() == expected);
					system("PAUSE");
                }

                void testTimedTask() {
              		std::string timedTaskString = "TIMED\ncs2013 is fun\n13/02/2014 14:00\n14/03/2014 15:30\nfalse\n";
					TaskTimed* timedTaskPtr = new TaskTimed;
					timedTaskPtr->stringToTask(timedTaskString);

					std::string expected = "TIMED cs2013 is fun 13/02/2014 14:00 14/03/2014 15:30 false\n";
					QVERIFY(timedTaskPtr->outputToString() == expected);
					system("PAUSE");
                }

				void testFloatTask() {
					std::string floatTaskString = "FLOAT\ncs2013 is NO fun\nfalse\n";
					TaskFloat* floatTaskPtr = new TaskFloat;
					floatTaskPtr->stringToTask(floatTaskString);

					std::string expected = "FLOAT cs2013 is NO fun false\n";
					QVERIFY(floatTaskPtr->outputToString() == expected);
					system("PAUSE");
				}
				
				// Unit Test END

};

QTEST_MAIN(TaskTest);
#include "main.moc"