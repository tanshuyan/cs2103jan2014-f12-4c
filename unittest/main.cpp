// v1.0

#include <QtTest\Qttest>
#include <QtCore/QCoreApplication>
#include <QTest>
#include <QtTest\Qttest>
#include <qobject.h>
#include <qstring.h>
#include "taskStorage.h"
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "Parser.h"
#include "NLParser.h"
#include <cstdlib>

class TaskTest : public QObject {
        Q_OBJECT
private:
	
        private slots:

                // Unit Test START

                void testDeadlineTask() {
					std::string deadlineTaskString = "cs2013 is fun\n13/02/2014 14:00\nfalse\n";
					TaskDeadline* deadlineTaskPtr = new TaskDeadline;
					deadlineTaskPtr->stringToTask(deadlineTaskString);

					std::string expected = "cs2013 is fun 13/02/2014 14:00 false\n";
					QVERIFY(deadlineTaskPtr->outputToString() == expected);
					system("PAUSE");
                }

                void testTimedTask() {
              		std::string timedTaskString = "cs2013 is fun\n13/02/2014 14:00\n14/03/2014 15:30\nfalse\n";
					TaskTimed* timedTaskPtr = new TaskTimed;
					timedTaskPtr->stringToTask(timedTaskString);

					std::string expected = "cs2013 is fun 13/02/2014 14:00 14/03/2014 15:30 false\n";
					QVERIFY(timedTaskPtr->outputToString() == expected);
					system("PAUSE");
                }

				void testFloatTask() {
					std::string floatTaskString = "cs2013 is NO fun\nfalse\n";
					TaskFloat* floatTaskPtr = new TaskFloat;
					floatTaskPtr->stringToTask(floatTaskString);

					std::string expected = "cs2013 is NO fun false\n";
					QVERIFY(floatTaskPtr->outputToString() == expected);
					system("PAUSE");
				}
				
				//NLParser Unit Tests
				void testParser() {
					Parser parser;
					AnalysedData expectedOutput;
					//test input
					std::string testString = "event";
					AnalysedData output = parser.addCMD(testString);
					//expected output
					expectedOutput.setCommand("add");
					expectedOutput.setTaskDesc("event");
					QDate startDate;
					expectedOutput.setStartDate(startDate);
					QTime startTime;
					expectedOutput.setStartTime(startTime);

					QVERIFY(output == expectedOutput);
					system("PAUSE");
				}

				void testParser_2() {
					Parser parser;
					AnalysedData expectedOutput;
					//test input
					std::string testString = "event";
					AnalysedData output = parser.addCMD(testString);
					//expected output
					expectedOutput.setCommand("add");
					expectedOutput.setTaskDesc("event");
					QDate startDate;
					expectedOutput.setStartDate(startDate);
					QTime startTime;
					expectedOutput.setStartTime(startTime);
					QVERIFY(output == expectedOutput);
					system("PAUSE");
				}

				void testParser_3() {
					Parser parser;
					AnalysedData expectedOutput;
					//test input
					std::string testString = "event on 4th dec at 4:30pm";
					AnalysedData output = parser.addCMD(testString);
					//expected output
					expectedOutput.setCommand("add");
					expectedOutput.setTaskDesc("event");
					QDate startDate(2014,12,4);
					expectedOutput.setStartDate(startDate);
					QTime startTime(16,30);
					expectedOutput.setStartTime(startTime);
					expectedOutput.setDateTimeUnlabelled(true);
					QVERIFY(output == expectedOutput);
					system("PAUSE");
				}

				// Unit Test END

};

QTEST_MAIN(TaskTest);
#include "main.moc"