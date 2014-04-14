//@author A0094659L

// Unit Test

#include <QtTest\Qttest>
#include <QtCore/QCoreApplication>
#include <QTest>
#include <QtTest\Qttest>
#include <cstdlib>
#include <qobject.h>
#include <qstring.h>
#include "TaskStorage.h"
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "Parser.h"
#include "DisplayOutput.h"
#include "Logic.h"
#include "Message.h"

class TaskTest : public QObject {
        Q_OBJECT
private:
	
	private slots:

		// Unit Test START
		//@author A0094659L
		// constructDeadlineTask tests the functionality of storage as well as the constructor of a deadline task
		void constructDeadlineTask() {
			std::string deadlineTaskString = "do IE2150 report\n13/04/2014 14:00\nfalse\n";
			Task* deadlineTaskPtr = new TaskDeadline;
			deadlineTaskPtr->stringToTask(deadlineTaskString);

			std::string expected = "DEADLINE\ndo IE2150 report\n13/04/2014 14:00\nfalse\n";
			QVERIFY(deadlineTaskPtr->taskToString() == expected);
			delete deadlineTaskPtr;
		}
				
		// constructTimedTask tests the functionality of storage as well as the constructor of a timed task
		void constructTimedTask() {
			std::string timedTaskString = "do IE2150 report\n13/04/2014 14:00\n14/04/2014 15:30\nfalse\n";
			Task* timedTaskPtr = new TaskTimed;
			timedTaskPtr->stringToTask(timedTaskString);

			std::string expected = "TIMED\ndo IE2150 report\n13/04/2014 14:00\n14/04/2014 15:30\nfalse\n";
			QVERIFY(timedTaskPtr->taskToString() == expected);
			delete timedTaskPtr;
		}

		// constructFloatTask tests the functionality of storage as well as the constructor of a float task
		void constructFloatTask() {
			std::string floatTaskString = "do IE2150 report\nfalse\n";
			Task* floatTaskPtr = new TaskFloat;
			floatTaskPtr->stringToTask(floatTaskString);

			std::string expected = "FLOAT\ndo IE2150 report\nfalse\n";
			QVERIFY(floatTaskPtr->taskToString() == expected);
			delete floatTaskPtr;
		}
		
		void testFeedback() {
			DisplayOutput display;
			Logic test;
			display = test.executeUserInput("delete all");
			display = test.executeUserInput("add mary had a little lamb");

			std::string expected = "Added: \"mary had a little lamb\"\n";
			QVERIFY(display.getFeedBack() == expected);
			display = test.executeUserInput("delete 1 to 50");
		}
				
		void testDisplayStatus() {
			DisplayOutput display;
			Logic test;
			display.setDisplayStatus(false);
			bool expected = false;
			QVERIFY(display.getDisplayStatus() == expected);
		}		

		//@author A0097286M
		//Parser Unit Tests
		//Tests ability to ignore non-valid keywords (i.e. the "from" and "to" in this test case)
		//Tests ability to recognise "today"
		//Tests ability to trim whitespaces from the start and end of descriptions
		//Tests ability to recognise that the date has a start/end date labelled
		void addSingleStartTime() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "  get food from macdonalds to eat    today at 10am";
			AnalysedData output = parser.addCMD(testString);
			//expected output
			expectedOutput.setCommand("add");
			expectedOutput.setTaskDesc("get food from macdonalds to eat");
			QDate startDate = QDate::currentDate();
			expectedOutput.setStartDate(startDate);
			QTime startTime(10,0);
			expectedOutput.setStartTime(startTime);
			expectedOutput.setDateTimeUnlabelled(true);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to ignore non-date terms (i.e. on 10th street)
		//Tests ability to take in worded months
		//Tests ability to take in start time, start date, end time, end date
		//Tests ability to auto-complete the year when not given
		void addStartAndEnd() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "meet friend on 10th street on 16th august 10:04 pm until aug 18 at 6:59";
			AnalysedData output = parser.addCMD(testString);
			//expected output
			expectedOutput.setCommand("add");
			expectedOutput.setTaskDesc("meet friend on 10th street");
			QDate startDate(2014,8,16);
			expectedOutput.setStartDate(startDate);
			QTime startTime(22,04);
			expectedOutput.setStartTime(startTime);
			QDate endDate(2014,8,18);
			expectedOutput.setEndDate(endDate);
			QTime endTime(18,59);
			expectedOutput.setEndTime(endTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to take in a fully specified date in slash format
		//Tests ability to recognise "at 8" as 8am
		//Tests ability to recognise date as an unlabelled date (it is not clearly marked as a start or end date)
		void addSlashFormat() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "event on 4/12/2015 at 8";
			AnalysedData output = parser.addCMD(testString);
			//expected output
			expectedOutput.setCommand("add");
			expectedOutput.setTaskDesc("event");
			QDate startDate(2015,12,4);
			expectedOutput.setStartDate(startDate);
			QTime startTime(8,0);
			expectedOutput.setStartTime(startTime);
			expectedOutput.setDateTimeUnlabelled(true);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to parse a sentence with no valid date or time
		//Tests ability to extract a quoted sentence and make it the description
		//Tests ability to treat nested quotes as part of the larger quoted sentence
		void addWithQuotes() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "not part of the desc \"meeting on \"imports\" from 8.01 warehouse\" from today NOT";
			AnalysedData output = parser.addCMD(testString);
			//expected output
			expectedOutput.setCommand("add");
			expectedOutput.setTaskDesc("meeting on \"imports\" from 8.01 warehouse");
			expectedOutput.setDateTimeUnlabelled(true);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to recognise "tmr"
		//Tests ability to recognise that the date has a start/end date labelled
		void editSingleStartTime() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "1 get homework done  at 12pm tmr";
			AnalysedData output = parser.editCMD(testString);
			//expected output
			expectedOutput.setCommand("edit");
			expectedOutput.setIndex(1);
			expectedOutput.setTaskDesc("get homework done");
			QDate startDate = QDate::currentDate().addDays(1);
			expectedOutput.setStartDate(startDate);
			QTime startTime(12,0);
			expectedOutput.setStartTime(startTime);
			expectedOutput.setDateTimeUnlabelled(true);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to ignore non-date terms (i.e. on 10th street)
		//Tests ability to take in worded months
		//Tests ability to take in start time, start date, end time, end date
		//Tests ability to auto-complete the year when not given
		void editStartAndEnd() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "1 meet boss on 10th story until 18 november 2016 at 02:59 from 10:04 16th november 15";
			AnalysedData output = parser.editCMD(testString);
			//expected output
			expectedOutput.setCommand("edit");
			expectedOutput.setIndex(1);
			expectedOutput.setTaskDesc("meet boss on 10th story");
			QDate startDate(2015,11,16);
			expectedOutput.setStartDate(startDate);
			QTime startTime(10,04);
			expectedOutput.setStartTime(startTime);
			QDate endDate(2016,11,18);
			expectedOutput.setEndDate(endDate);
			QTime endTime(2,59);
			expectedOutput.setEndTime(endTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}
		//Tests ability to take in a fully specified date in dash format
		//Tests ability to recognise "at 3" as 3pm (office hours)
		//Tests ability to recognise date as an unlabelled date (it is not clearly marked as a start or end date)
		//Tests ability to read the index to be edited
		void editSlashFormat() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "22 from to event at 3 on 12-5-2013";
			AnalysedData output = parser.editCMD(testString);
			//expected output
			expectedOutput.setCommand("edit");
			expectedOutput.setTaskDesc("from to event");
			QDate startDate(2013,5,12);
			expectedOutput.setStartDate(startDate);
			QTime startTime(15,0);
			expectedOutput.setStartTime(startTime);
			expectedOutput.setIndex(22);
			expectedOutput.setDateTimeUnlabelled(true);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to read time and date when there are quotes
		//Tests ability to extract a quoted sentence and make it the description
		//Tests ability to treat nested quotes as part of the larger quoted sentence
		//Tests ability to read the index to be edited, in the case with quotes
		void editWithQuotes() {
			Parser parser;
			AnalysedData expectedOutput;
			//test input
			std::string testString = "9 \"meeting on \"imports\"\" from 1/1 at 5:30 until 2/1 at 5";
			AnalysedData output = parser.editCMD(testString);
			//expected output
			expectedOutput.setCommand("edit");
			expectedOutput.setTaskDesc("meeting on \"imports\"");
			expectedOutput.setIndex(1);
			QDate startDate(2015,1,1);
			expectedOutput.setStartDate(startDate);
			QTime startTime(17,30);
			expectedOutput.setStartTime(startTime);
			QDate endDate(2015,1,2);
			expectedOutput.setEndDate(endDate);
			QTime endTime(17,00);
			expectedOutput.setEndTime(endTime);
			expectedOutput.setIndex(9);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to parse multiple indexes
		void deleteMultipleIndex() {
			Parser parser;
			AnalysedData expectedOutput;
			std::vector<Task*> displayList;
			//test input
			std::string testString = "1, 3,5 9-11";
			AnalysedData output = parser.deleteCMD(testString, displayList);
			//expected output
			expectedOutput.setCommand("delete");
			std::vector<int> index;
			index.push_back(1);
			index.push_back(3);
			index.push_back(5);
			index.push_back(9);
			index.push_back(10);
			index.push_back(11);
			expectedOutput.setIndexVector(index);
			QVERIFY(output == expectedOutput);
		}

		//DateTimeResolver tests
		//Tests ability to correctly deduce missing start time field
		void resolveAddMissingStartTime() {
			DateTimeResolver dateTimeResolver;
			AnalysedData output;
			AnalysedData expectedOutput;
			//test input
			output.setCommand("add");
			QDate startDate(2015,12,4);
			output.setStartDate(startDate);
			QDate endDate(2015,12,5);
			output.setEndDate(endDate);
			QTime endTime(6,00);
			output.setEndTime(endTime);
			output.setDateTimeUnlabelled(false);
			dateTimeResolver.resolveAdd(output);
			//expected output
			expectedOutput.setCommand("add");
			QDate exStartDate(2015,12,4);
			expectedOutput.setStartDate(exStartDate);
			QTime exStartTime(6,00);
			expectedOutput.setStartTime(exStartTime);
			QDate exEndDate(2015,12,5);
			expectedOutput.setEndDate(exEndDate);
			QTime exEndTime(6,00);
			expectedOutput.setEndTime(exEndTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}

		//Tests ability to correctly deduce missing start date field
		void resolveAddMissingStartDate() {
			DateTimeResolver dateTimeResolver;
			AnalysedData output;
			AnalysedData expectedOutput;
			//test input
			output.setCommand("add");
			QTime startTime(23,59);
			output.setStartTime(startTime);
			QDate endDate(2015,12,5);
			output.setEndDate(endDate);
			QTime endTime(6,00);
			output.setEndTime(endTime);
			output.setDateTimeUnlabelled(false);
			dateTimeResolver.resolveAdd(output);
			//expected output
			expectedOutput.setCommand("add");
			QDate exStartDate = QDate::currentDate();
			expectedOutput.setStartDate(exStartDate);
			QTime exStartTime(23,59);
			expectedOutput.setStartTime(exStartTime);
			QDate exEndDate(2015,12,5);
			expectedOutput.setEndDate(exEndDate);
			QTime exEndTime(6,00);
			expectedOutput.setEndTime(exEndTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}
		
		//Tests ability to correctly deduce missing time fields
		void resolveAddMissingTimes() {
			DateTimeResolver dateTimeResolver;
			AnalysedData output;
			AnalysedData expectedOutput;
			//test input
			output.setCommand("add");
			QTime startTime(23,59);
			output.setStartTime(startTime);
			QTime endTime(0,0);
			output.setEndTime(endTime);
			output.setDateTimeUnlabelled(false);
			dateTimeResolver.resolveAdd(output);
			//expected output
			expectedOutput.setCommand("add");
			QDate exStartDate = QDate::currentDate();
			expectedOutput.setStartDate(exStartDate);
			QTime exStartTime(23,59);
			expectedOutput.setStartTime(exStartTime);
			QDate exEndDate = QDate::currentDate().addDays(1);
			expectedOutput.setEndDate(exEndDate);
			QTime exEndTime(0,0);
			expectedOutput.setEndTime(exEndTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}
		//Tests ability to correctly deduce missing date fields
		void resolveAddMissingDate() {
			DateTimeResolver dateTimeResolver;
			AnalysedData output;
			AnalysedData expectedOutput;
			//test input
			output.setCommand("add");
			QDate startDate(2015,12,4);
			output.setStartDate(startDate);
			QDate endDate(2015,12,5);
			output.setEndDate(endDate);
			output.setDateTimeUnlabelled(false);
			dateTimeResolver.resolveAdd(output);
			//expected output
			expectedOutput.setCommand("add");
			QDate exStartDate(2015,12,4);
			expectedOutput.setStartDate(exStartDate);
			QTime exStartTime(00,00);
			expectedOutput.setStartTime(exStartTime);
			QDate exEndDate(2015,12,5);
			expectedOutput.setEndDate(exEndDate);
			QTime exEndTime(23,59);
			expectedOutput.setEndTime(exEndTime);
			expectedOutput.setDateTimeUnlabelled(false);
			QVERIFY(output == expectedOutput);
		}
		// Unit Test END

		//@author A0004695A
		// System testing
		// this series of system test will require an empty CalenizerStorage.txt file to pass
		// delete function is called at the end of every system testing to clear the CalenizerStorage.txt for the next system test

		// addTest tests the functionality adding of tasks
		// addTest tests the functionality inherent sorting of display list 
		// addTest tests the functionality function of delete all
		void addTest() {
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
			displayOutput = logic.executeUserInput("delete all");
			QVERIFY(displayOutput.getDisplay().size() == 0);
		}
				
		// undoRedoTest tests the the functionality of undo and redo
		// undoRedoTest tests the functionality to complete "incomplete"
		// undoRedoTest tests the functionality to delete tasks containing "searchterm"
		void undoRedoTest() {
			Logic logic;
			DisplayOutput displayOutput;
			std::vector<std::string> output;
			std::string testDeadline = "add do homework on 23 may 10pm";
			std::string testTimed = "add finish homework from 22 may to 25 may 10pm";
			displayOutput = logic.executeUserInput(testDeadline);
			displayOutput = logic.executeUserInput(testTimed);
			displayOutput = logic.executeUserInput("undo");
			output = displayOutput.getDisplay();
			std::string expectedOutput1 = "1. DEADLINE<>do homework<>23 May 2014 10:00 pm<>false\n";
			QVERIFY(output[0] == expectedOutput1);
			displayOutput = logic.executeUserInput("redo");
			output = displayOutput.getDisplay();
			std::string expectedOutput2 = "2. TIMED<>finish homework<>22 May 2014 10:00 pm to 25 May 2014 10:00 pm<>false\n";
			QVERIFY(output[1] == expectedOutput2);
			displayOutput = logic.executeUserInput("complete incomplete");
			displayOutput = logic.executeUserInput("undo");
			displayOutput = logic.executeUserInput("complete 1");
			displayOutput = logic.executeUserInput("undo");
			QVERIFY(output[0] == expectedOutput1);
			displayOutput = logic.executeUserInput("delete tasks contain \"homework\"");
		}
				
		// completeIncompleteTest tests the functionality of multiple incomplete and complete 
		// completeIncompleteTest tests the functionality of resolveAdd to auto fill in time when user doesnt specify
		// completeIncompleteTest tests the functionality to delete multiple indexes
		void completeIncompleteTest() {
			Logic logic;
			DisplayOutput displayOutput;
			std::vector<std::string> output;
			std::string testDeadline = "add do internship report on 23 june 10pm";
			std::string testTimed = "add finish reservist from 22 july to 25 july";
			displayOutput = logic.executeUserInput(testDeadline);
			displayOutput = logic.executeUserInput(testTimed);
			displayOutput = logic.executeUserInput("complete 1 to 3");
			output = displayOutput.getDisplay();
			std::string expectedOutput1 = "1. DEADLINE<>do internship report<>23 Jun 2014 10:00 pm<>true\n";
			std::string expectedOutput2 = "2. TIMED<>finish reservist<>22 Jul 2014 12:00 am to 25 Jul 2014 11:59 pm<>true\n";
			QVERIFY(output[0] == expectedOutput1);
			QVERIFY(output[1] == expectedOutput2);
			displayOutput = logic.executeUserInput("incomplete contain \"do\"");
			output = displayOutput.getDisplay();
			std::string expectedOutput3 = "1. DEADLINE<>do internship report<>23 Jun 2014 10:00 pm<>false\n";
			QVERIFY(output[0] == expectedOutput3);
			displayOutput = logic.executeUserInput("delete 1 to 50");
		}

		// editDeleteTest tests the functionality of shifting the duration of timed tasks (using "on")
		// editDeleteTest tests the functionality of editing end dates and start dates
		// editDeleteTest tests the functionality of delete incomplete
		// editDeleteTest tests the sorting algo in ranking the tasks 
		void editDeleteTest() {
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
			// pushes back the duration of the task for timed task
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
			displayOutput = logic.executeUserInput("delete incomplete");
		}
		
		//@author A0101843R
		// searchDisplayTest tests the search functionality of search terms and also, search terms containing tasks types, and deleting on current display, doesnt affect those not in the current display criteria
		void searchDisplayTest() {
			Logic logic;
			DisplayOutput displayOutput;
			std::vector<std::string> output;
			std::string testDeadline = "add do homework on 23/12/2014 10pm";
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
		}
		
		// stopSystemTest uses system pause to pause the programme for the developer to see the results of the tests
		void stopSystemTest() {
			system("PAUSE");
		}

		// End of system testing
};

QTEST_MAIN(TaskTest);
#include "main.moc"
