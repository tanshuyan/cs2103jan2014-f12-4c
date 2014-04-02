//v1.1
#include "calenizergui.h"

const QString CalenizerGUI::ADD_MSG = "add";
const QString CalenizerGUI::DELETE_MSG = "delete";
const QString CalenizerGUI::EDIT_MSG= "edit";
const QString CalenizerGUI::SEARCH_MSG = "search";
const QString CalenizerGUI::COMPLETE_MSG = "complete";
const QString CalenizerGUI::INCOMPLETE_MSG = "incomplete";
const QString CalenizerGUI::REDO_MSG = "redo";
const QString CalenizerGUI::UNDO_MSG = "undo";
const QString CalenizerGUI::VIEW_MSG= "view";

const std::string CalenizerGUI::STATUS_TRUE= "true\n";
const std::string CalenizerGUI::STATUS_FALSE= "false\n";

const std::string CalenizerGUI::STATUS_COMPLETE = "complete";
const std::string CalenizerGUI::STATUS_INCOMPLETE = "incomplete";
const std::string CalenizerGUI::STATUS_OVERDUE = "overdue";
const std::string CalenizerGUI::STATUS_ONGOING = "ongoing";

const std::string CalenizerGUI::CMD_DISPLAY_TODAY = "display today";

CalenizerGUI::CalenizerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->setStyleSheet ("border-style: outset;"
							"border-width: 2px;"
							"border-radius: 10px;"
							"border-color: white;"
							"padding: 2px;"
							"background-color: white");
	ui.textEdit->setStyleSheet ("border-style: outset;"
								"border-width: 2px;"
								"border-radius: 10px;"
								"border-color: white;"
								"padding: 5px;");
	ui.lineEdit->setStyleSheet ("border-style: outset;"
								"border-width: 2px;"
								"border-radius: 10px;"
								"border-color: white;"
								"padding: 2px;"
								"background-color: white");
	ui.label->setAlignment(Qt::AlignCenter);
	setStyleSheet("background-color: #DEB887;");

	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString("dd MMMM yyyy\nhh:mm");
	ui.label->setText(dateTimeString);
	initialiseTable(ui.tableWidget);
	initialiseConnections();
	initialiseTableStyle();
	//initialiseTableSize();
	
	new QShortcut(Qt::Key_Escape, this, SLOT(resetInput()));
	_g_current_row = 0;
	todayDisplay();
}

CalenizerGUI::~CalenizerGUI()
{
	
}

void CalenizerGUI::initialiseTableStyle(){
	
	//defensive coding
	//if(palette !=NULL){
		//delete palette;
	//}

	palette = new QPalette();
	palette->setColor(QPalette::WindowText,Qt::black);
	ui.label->setPalette(*palette);

	palette->setColor(QPalette::Text,Qt::black);
	ui.lineEdit->setPalette(*palette);

	ui.tableWidget->setStyleSheet("color: black;" 
								  "gridline-color: white;"
								  "background-color: white;");

	ui.textEdit->setTextColor(Qt::blue);
	//QLineEdit *line = new QLineEdit();
}

//this function not used for now - old code
void CalenizerGUI::initialiseTableSize(){
	ui.tableWidget->setColumnWidth(0,  200);
	ui.tableWidget->setColumnWidth(1,  255);
	ui.tableWidget->setColumnWidth(2,  100);
}
/*
void CalenizerGUI::displayTasks(std::vector<Task*>* displayList){
	std::stringstream output;
	int counter = 1;

	for(std::vector<Task*>::iterator iter = displayList->begin(); iter != displayList->end();){
		//Numbering
		output << counter << ". ";
		counter++;
		output << (*iter)->outputToString();
		iter++;
	}
	ui.tableWidget->setItem(0,_g_current_row, new QTableWidgetItem(QString::fromStdString(output.str())));
}
*/
void CalenizerGUI::getFeedback(DisplayOutput displayoutput)
{
	ui.textEdit->append(QString::fromStdString(displayoutput.getFeedBack()));
}

void CalenizerGUI::getTask(DisplayOutput displayoutput, int row){

		std::string initialString = displayoutput.getDisplay().at(row);
		int startIndex = initialString.find_first_of("<>");

		int pos = initialString.find("<>", initialString.find("<>") + 1);
		std::string desc = initialString.substr(startIndex+2,pos-(startIndex+2));

		startIndex = pos+1;
		int lastIndex = initialString.find("<>", startIndex);

		std::string duration;
		if(lastIndex != initialString.npos){
			duration = initialString.substr(pos+2,lastIndex-(pos+2));
			//status = initialString.substr(lastIndex+2);
		} else {
			duration = "";
			//status = initialString.substr(startIndex+1);
		}

		std::string status = displayoutput.getDisplayListStatus().at(row);

		QTableWidgetItem *taskDesc = new QTableWidgetItem(QString::fromStdString(desc));
		QTableWidgetItem *taskDuration = new QTableWidgetItem(QString::fromStdString(duration));
		QTableWidgetItem *taskStatus = new QTableWidgetItem(QString::fromStdString(status));
		
		ui.tableWidget->setItem(row, 0, taskDesc);
		ui.tableWidget->setItem(row, 1, taskDuration);
		ui.tableWidget->setItem(row, 2, taskStatus);
		
		if(status == STATUS_COMPLETE) {
			taskDesc->setBackgroundColor(Qt::lightGray);
				taskDuration->setBackgroundColor(Qt::lightGray);
				taskStatus->setBackgroundColor(Qt::lightGray);
		}
		
		if(status == STATUS_OVERDUE) {
				taskDesc->setBackgroundColor(QColor(255,100,100));
				taskDuration->setBackgroundColor(QColor(255,100,100));
				taskStatus->setBackgroundColor(QColor(255,100,100));
		}

		if(status == STATUS_ONGOING) {
				taskDesc->setBackgroundColor(Qt::yellow);
				taskDuration->setBackgroundColor(Qt::yellow);
				taskStatus->setBackgroundColor(Qt::yellow);
		}
}

void CalenizerGUI:: initialiseConnections() {
	connect(ui.lineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkAlphabet()));
	connect(ui.lineEdit, SIGNAL(Qt::Key_Escape), this, SLOT(resetInput()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(run()));
}

void CalenizerGUI::run()
{
	std::string userInput = ui.lineEdit->text().toStdString();

	DisplayOutput displayoutput= _g_logic.executeUserInput(userInput);
	getFeedback(displayoutput);

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());

	for(int row=0; row<displayoutput.getDisplay().size(); row++){
		getTask(displayoutput,row);
	}	

	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString("dd MMMM yyyy\nhh:mm");
	ui.label->setText(dateTimeString);

	ui.lineEdit->clear();
}

void CalenizerGUI::todayDisplay() {
	DisplayOutput displayoutput= _g_logic.executeUserInput(CMD_DISPLAY_TODAY);
	getFeedback(displayoutput);

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());

	for(int row=0; row<displayoutput.getDisplay().size(); row++){
		getTask(displayoutput,row);
	}
}

void CalenizerGUI::checkAlphabet() {
	std::string text = ui.lineEdit->text().toStdString();
	if(text.at(0) == 'a' && text.length() <= 4) {
		ui.lineEdit->setText(ADD_MSG + " ");
	} else if (text.at(0) == 'c' && text.length() <= 9) {
		ui.lineEdit->setText(COMPLETE_MSG + " ");
	} else if (text.at(0) == 'd' && text.length() <= 7) {
		ui.lineEdit->setText(DELETE_MSG + " ");
	} else if (text.at(0) == 'e' && text.length() <= 5) {
		ui.lineEdit->setText(EDIT_MSG + " ");
	} else if (text.at(0) == 'i' && text.length() <= 11) {
		ui.lineEdit->setText(INCOMPLETE_MSG + " ");
	} else if (text.at(0) == 'r') {
		ui.lineEdit->setText(REDO_MSG);
	} else if (text.at(0) == 's' && text.length() <= 7) {
		ui.lineEdit->setText(SEARCH_MSG + " ");
	} else if (text.at(0) == 'u') {
		ui.lineEdit->setText(UNDO_MSG + " ");
	} else if (text.at(0) == 'v' && text.length() <= 5) {
		ui.lineEdit->setText(VIEW_MSG + " ");
	} 
}

void CalenizerGUI::resetInput(){
	ui.lineEdit->setText("");
}

void CalenizerGUI::setColumnWidth(QTableWidget *table) {
	QStringList tableHeader;
	tableHeader << "Task Description" << "Duration" << "Status";
	table->setColumnCount(3);
	table->setHorizontalHeaderLabels(tableHeader);

	table->setColumnWidth(TASK_DESC, 250);
	table->setColumnWidth(TASK_DURATION, 200);
	table->setColumnWidth(TASK_STATUS,200);
}

void CalenizerGUI::initialiseTable(QTableWidget *table) {
	setColumnWidth(table);
	fixColumnWidth(table);
}

void CalenizerGUI::fixColumnWidth(QTableWidget *table) {
	
	for(unsigned int col = 0 ; col < 3; col++) {
		table->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
	}
}
