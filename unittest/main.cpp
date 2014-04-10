// v1.1
// added system testing
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
#include "DisplayOutput.h"
#include "Logic.h"
#include "Message.h"
#include <cstdlib>

class TaskTest : public QObject {
        Q_OBJECT
private:
	
        private slots:

                // Unit Test START
				// testDeadlineTask tests the functionality of storage as well as the constructor of a deadline task
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
				/*
                void testFeedback(){
                    DisplayOutput display;
                    //std::string command;
                    Logic test;
                    display = test.executeUserInput("add mary had a little lamb");

                    std::string expected = "Added: \"mary had a little lamb\"\n";
                    QVERIFY(display.getFeedBack() == expected);
                    system("PAUSE");
                }*/

				/*
				 void testDisplayStatus(){
                    DisplayOutput display;
                    display.setDisplayStatus(false);
                    bool expected = "false";
                    QVERIFY(display.getDisplayStatus() == expected);
                    system("PAUSE");
                }
				*/



				// Unit Test END

				// System testing
				// systemTest_1 tests the adding of tasks, and the inherent sorting
				void systemTest_1() {
					Logic logic;
					DisplayOutput displayOutput;
					std::vector<std::string> output;
					std::string testFloat = "add do cs diagram";
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput = logic.executeUserInput(testFloat);
					displayOutput = logic.executeUserInput(testDeadline);
					displayOutput = logic.executeUserInput(testTimed);
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "3. FLOAT<>do cs diagram<>false\n";
					QVERIFY(output[2] == expectedOutput1);
					std::string expectedOutput2 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
			 		QVERIFY(output[0] == expectedOutput2);
					std::string expectedOutput3 = "2. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[1] == expectedOutput3);
					displayOutput = logic.executeUserInput("delete 1 to 50");
					system("PAUSE");
				}
				
				// systemTest_2 tests the sequence of undo and redo
				void systemTest_2() {
					Logic logic;
					DisplayOutput displayOutput;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput = logic.executeUserInput(testDeadline);
					displayOutput = logic.executeUserInput(testTimed);
					displayOutput = logic.executeUserInput("undo");
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput1);
					displayOutput = logic.executeUserInput("redo");
					output = displayOutput.getDisplay();
					std::string expectedOutput2 = "2. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[1] == expectedOutput2);
					displayOutput = logic.executeUserInput("complete 1");
					displayOutput = logic.executeUserInput("undo");
					displayOutput = logic.executeUserInput("complete 1");
					displayOutput = logic.executeUserInput("undo");
					QVERIFY(output[0] == expectedOutput1);
					displayOutput = logic.executeUserInput("delete 1 to 50");
					system("PAUSE");
				}
				// systemTest_3 tests the incomplete and complete functionality (multiple completes) and the sorting algo
				void systemTest_3() {
					Logic logic;
					DisplayOutput displayOutput;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput = logic.executeUserInput(testDeadline);
					displayOutput = logic.executeUserInput(testTimed);
					displayOutput = logic.executeUserInput("complete 1 to 2");
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>true\n";
					std::string expectedOutput2 = "2. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>true\n";
					QVERIFY(output[0] == expectedOutput1);
					QVERIFY(output[1] == expectedOutput2);
					displayOutput = logic.executeUserInput("incomplete 1");
					output = displayOutput.getDisplay();
					std::string expectedOutput3 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput3);
					displayOutput = logic.executeUserInput("delete 1 to 50");
					system("PAUSE");
				}
				// systemTest_4 tests edit and delete functionality
				void systemTest_4() {
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
					displayOutput = logic.executeUserInput("edit 1 on 25 dec 11pm");
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "5. DEADLINE<>do homework<>25 Dec 2014 11:00 pm<>false\n";
					QVERIFY(output[4] == expectedOutput1);
					displayOutput = logic.executeUserInput("delete 1");
					displayOutput = logic.executeUserInput("edit 1 on 25 dec 11pm");
					displayOutput = logic.executeUserInput("edit 1 start 23 dec");
					displayOutput = logic.executeUserInput("edit 2 end 24 dec");
					output = displayOutput.getDisplay();
					expectedOutput1 = "1. TIMED<>must finish homework<>22 Dec 2014 10:00 pm to 24 Dec 2014 10:00 pm<>false\n";
					std::string expectedOutput2 = "2. TIMED<>do finish homework<>23 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					std::string expectedOutput3 = "3. DEADLINE<>do homework<>25 Dec 2014 11:00 pm<>false\n";
					std::string expectedOutput4 = "4. TIMED<>unfinish homework<>25 Dec 2014 11:00 pm to 28 Dec 2014 11:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput1);
					QVERIFY(output[1] == expectedOutput2);
					QVERIFY(output[2] == expectedOutput3);
					QVERIFY(output[3] == expectedOutput4);
					displayOutput = logic.executeUserInput("delete 1 to 50");
					system("PAUSE");
				}
				
					// systemTest_5 tests the search functionality of search terms and also, search terms containing tasks types, and deleting on current display, doesnt affect those not in the current display criteria
					void systemTest_5() {
					Logic logic;
					DisplayOutput displayOutput;
					std::vector<std::string> output;
					std::string testDeadline = "add do homework on 23 dec 10pm";
					std::string testTimed = "add finish homework from 22 dec to 25 dec 10pm";
					displayOutput = logic.executeUserInput(testDeadline);
					displayOutput = logic.executeUserInput(testTimed);
					displayOutput = logic.executeUserInput("search do");
					output = displayOutput.getDisplay();
					std::string expectedOutput1 = "1. DEADLINE<>do homework<>23 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput1);
					displayOutput = logic.executeUserInput("search timed");
					output = displayOutput.getDisplay();
					std::string expectedOutput2 = "1. TIMED<>finish homework<>22 Dec 2014 10:00 pm to 25 Dec 2014 10:00 pm<>false\n";
					QVERIFY(output[0] == expectedOutput2);
					displayOutput = logic.executeUserInput("delete 1");
					//delete will only the existing displaylist "search timed" that the user is on, deadline task which is not in the display is unaffected
					QVERIFY(displayOutput.getDisplay().size() == 0);
					displayOutput = logic.executeUserInput("view");
					QVERIFY(displayOutput.getDisplay().size() == 1);
					displayOutput = logic.executeUserInput("delete 1 to 50");
					system("PAUSE");
				}


};

QTEST_MAIN(TaskTest);
#include "main.moc"
