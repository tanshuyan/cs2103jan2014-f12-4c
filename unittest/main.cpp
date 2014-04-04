// v1.0

#include <QtTest\Qttest>
#include <QtCore/QCoreApplication>
#include <QTest>
#include <QtTest\Qttest>
#include <qobject.h>
#include <qstring.h>
#include <cstdlib>
#include "TaskStorage.h"
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "Parser.h"
#include "NLParser.h"
#include "Logic.h"
#include "DisplayOutput.h"

class CalenizerTest : public QObject {
        Q_OBJECT
private:
	
        private slots:
                // Unit Test START
				// testDeadlineTask tests the functionality of storage as well as the constructor of a deadline task
               /*
				void testDeadlineTask() {
					std::string deadlineTaskString = "cs2013 is fun\n13/02/2014 14:00\nfalse\n";
					Task* deadlineTaskPtr = new TaskDeadline;
					deadlineTaskPtr->stringToTask(deadlineTaskString);

					std::string expected = "DEADLINE\ncs2013 is fun\n13/02/2014 14:00\nfalse\n";
					QVERIFY(deadlineTaskPtr->taskToString() == expected);
					system("PAUSE");
                }
				// testTimedTask tests the functionality of storage as well as the constructor of a timed task
                void testTimedTask() {
              		std::string timedTaskString = "cs2013 is fun\n13/02/2014 14:00\n14/03/2014 15:30\nfalse\n";
					Task* timedTaskPtr = new TaskTimed;
					timedTaskPtr->stringToTask(timedTaskString);

					std::string expected = "TIMED\ncs2013 is fun\n13/02/2014 14:00\n14/03/2014 15:30\nfalse\n";
					QVERIFY(timedTaskPtr->taskToString() == expected);
					system("PAUSE");
                }
				// testFloatTask tests the functionality of storage as well as the constructor of a float task
				void testFloatTask() {
					std::string floatTaskString = "cs2013 is NO fun\nfalse\n";
					Task* floatTaskPtr = new TaskFloat;
					floatTaskPtr->stringToTask(floatTaskString);

					std::string expected = "FLOAT\ncs2013 is NO fun\nfalse\n";
					QVERIFY(floatTaskPtr->taskToString() == expected);
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

				void testNLParser_1() {
					//NLParser parser;
					system("PAUSE");
				}
				*/
				// Unit Test END

				// System testing
				//systemTest_1 tests the adding of tasks
				/*void systemTest_1() {
					Logic logic;
					DisplayOutput displayOutput1;
					DisplayOutput displayOutput2;
					DisplayOutput displayOutput3;
					std::vector<std::string> output;
					std::string testFloat = "add do cs diagram";
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
				//	displayOutput1 = logic.executeUserInput(testFloat);
					displayOutput2 = logic.executeUserInput(testDeadline);
					displayOutput3 = logic.executeUserInput(testTimed);
				//	output = displayOutput1.getDisplay();
				//	std::string expectedOutput1 = "1. FLOAT<>do cs diagram<>false\n";
				//	QVERIFY(output[0] == expectedOutput1);
					output = displayOutput2.getDisplay();
					std::string expectedOutput2 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
			 		QVERIFY(output[0] == expectedOutput2);
					output = displayOutput3.getDisplay();
					std::string expectedOutput3 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput3);
					system("PAUSE");
				}
				*/

				// systemTest_2 tests the sequence of undo and redo
				/*void systemTest_2() {
					Logic logic;
					DisplayOutput displayOutput2;
					DisplayOutput displayOutput3;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput2 = logic.executeUserInput(testDeadline);
					displayOutput3 = logic.executeUserInput(testTimed);
					displayOutput2 = logic.executeUserInput("undo");
					output = displayOutput2.getDisplay();
					std::string expectedOutput2 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput2);
					displayOutput3 = logic.executeUserInput("redo");
					output = displayOutput3.getDisplay();
					std::string expectedOutput3 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput3);
					system("PAUSE");
				}
				*/
				// systemTest_3 tests the incomplete and complete functionality (multiple completes) and the sorting algo
				/*void systemTest_3() {
					Logic logic;
					DisplayOutput displayOutput2;
					DisplayOutput displayOutput3;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput2 = logic.executeUserInput(testDeadline);
					displayOutput3 = logic.executeUserInput(testTimed);
					displayOutput2 = logic.executeUserInput("complete 1 to 2");
					output = displayOutput2.getDisplay();
					std::string expectedOutput1 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>true\n";
					std::string expectedOutput2 = "2. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>true\n";
					QVERIFY(output[0] == expectedOutput1);
					QVERIFY(output[1] == expectedOutput2);
					displayOutput3 = logic.executeUserInput("incomplete 1");
					output = displayOutput3.getDisplay();
					std::string expectedOutput3 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput3);
					system("PAUSE");
				}*/
				// systemTest_4 tests edit and delete functionality
			/*	void systemTest_4() {
					Logic logic;
					DisplayOutput displayOutput;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					std::string testTimed2 = "add unfinish homework from 22 dec to 25 dec 10pm";
					std::string testTimed3 = "add do finish homework from 22 dec to 25 dec 10pm";
					std::string testTimed4 = "add must finish homework from 22 dec to 25 dec 10pm";
					displayOutput = logic.executeUserInput(testDeadline);
					displayOutput = logic.executeUserInput(testTimed);
					displayOutput = logic.executeUserInput(testTimed2);
					displayOutput = logic.executeUserInput(testTimed3);
					displayOutput = logic.executeUserInput(testTimed4);
					displayOutput = logic.executeUserInput("edit 5 on 25 dec 11pm");
					output = displayOutput.getDisplay();
					std::string expectedOutput2 = "5. DEADLINE<>do homework<>25 Dec 2014 11:00 pm<>false\n";
					QVERIFY(output[5] == expectedOutput2);
					displayOutput = logic.executeUserInput("delete 1");
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "1. TIMED<>unfinish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					std::string expectedOutput3 = "2. DEADLINE<>do homework<>25 Dec 2014 11:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput1);
					QVERIFY(output[1] == expectedOutput3);
					system("PAUSE");
				}*/
				
				// systemTest_4 tests the search functionality of search terms and also, search terms containing tasks types
					/*void systemTest_4() {
					Logic logic;
					DisplayOutput displayOutput2;
					DisplayOutput displayOutput3;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput2 = logic.executeUserInput(testDeadline);
					displayOutput3 = logic.executeUserInput(testTimed);
					displayOutput2 = logic.executeUserInput("search do");
					output = displayOutput2.getDisplay();
					std::string expectedOutput2 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput2);
					displayOutput3 = logic.executeUserInput("search timed");
					output = displayOutput3.getDisplay();
					std::string expectedOutput3 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput3);
					system("PAUSE");
				}*/


};

QTEST_MAIN(CalenizerTest);
#include "main.moc"