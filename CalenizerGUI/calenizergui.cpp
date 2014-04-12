//@author A0101843R

// Calenizer.h

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
const QString CalenizerGUI::QUIT_MSG= "quit";
const std::string CalenizerGUI::EMPTY_STRING = "";

const std::string CalenizerGUI::STATUS_TRUE= "true\n";
const std::string CalenizerGUI::STATUS_FALSE= "false\n";

const std::string CalenizerGUI::STATUS_COMPLETE = "Complete";
const std::string CalenizerGUI::STATUS_INCOMPLETE = "Incomplete";
const std::string CalenizerGUI::STATUS_OVERDUE = "Overdue";
const std::string CalenizerGUI::STATUS_ONGOING = "Ongoing";

const std::string CalenizerGUI::CMD_DISPLAY_ALL = "view all";

CalenizerGUI::CalenizerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initialiseTable(ui.tableWidget);
	initialiseConnections();
	displayAll();
	initialiseTableStyle();
	initialiseShortcuts();
}

CalenizerGUI::~CalenizerGUI()
{

}

void CalenizerGUI::updateDateTime(){
	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString("dd MMMM yyyy\nhh:mm ap");
	ui.label->setText(dateTimeString);
}

void CalenizerGUI:: initialiseConnections() {
	connect(ui.lineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkAlphabet()));
	connect(ui.lineEdit, SIGNAL(Qt::Key_Escape), this, SLOT(resetInput()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(run()));
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateDateTime()));
	timer->start(1);
}

void CalenizerGUI::initialiseShortcuts(){
	new QShortcut(Qt::Key_Escape, this, SLOT(resetInput()));
	new QShortcut(Qt::Key_Up, this, SLOT(scrollUp()));
	new QShortcut(Qt::Key_Down, this, SLOT(scrollDown()));
}

void CalenizerGUI::initialiseTableStyle(){

	palette = new QPalette();
	palette->setColor(QPalette::WindowText,Qt::black);
	ui.label->setPalette(*palette);

	palette->setColor(QPalette::Text,Qt::black);
	ui.lineEdit->setPalette(*palette);

	ui.tableWidget->setStyleSheet("color: black;" 
								  "gridline-color: white;"
								  "background-color: white;");
	ui.tableWidget->setShowGrid(false);

	ui.textEdit->setTextColor(Qt::black);

	ui.label->setStyleSheet ("border-color: white;"
							"padding: 2px;");

	ui.textEdit->setStyleSheet ("border-style: outset;"
								"border-width: 2px;"
								"border-radius: 10px;"
								"border-color: white;");

	ui.lineEdit->setStyleSheet ("border-style: outset;"
								"border-width: 2px;"
								"border-radius: 10px;"
								"border-color: white;"
								"padding: 2px;"
								"background-color: white");

	ui.calendarWidget->setStyleSheet("color: black");
	ui.calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

	ui.tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { border: none; background:white; width:10px; margin: 0px 0px 0px 0px; }"
	"QScrollBar::handle:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    min-height: 0px;"
    ""
    "}"
	"QScrollBar::add-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    height: px;"
    "    subcontrol-position: bottom;"
    "    subcontrol-origin: margin;"
    "}"
	"QScrollBar::sub-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    height: 0px;"
    "    subcontrol-position: top;"
    "    subcontrol-origin: margin;"
    "}");

	ui.textEdit->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { border: 1px solid white; background:white; width:10px; margin: 0px 0px 0px 0px; }"
	"QScrollBar::handle:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    min-height: 0px;"
    ""
    "}"
	"QScrollBar::add-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    height: px;"
    "    subcontrol-position: bottom;"
    "    subcontrol-origin: margin;"
    "}"
	"QScrollBar::sub-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
    "    height: 0px;"
    "    subcontrol-position: top;"
    "    subcontrol-origin: margin;"
    "}");

	ui.label->setAlignment(Qt::AlignCenter);

	setStyleSheet("background-color:#EEF5F8;");
}

//this function get the feedback message from every action that the user carried out
void CalenizerGUI::getFeedback(DisplayOutput displayoutput){
	QString str = QString::fromStdString(displayoutput.getFeedBack());
	if (checkWord(str)) {
		ui.textEdit->setTextColor( QColor( "red" ) );
	}
	else {
		ui.textEdit->setTextColor( QColor( "black" ) );
	}

	ui.textEdit->append(str);
}

bool CalenizerGUI:: checkWord(QString input){
	return (input.contains("invalid", Qt::CaseInsensitive));
}

//this function get the vector of string to be displayed and separate it individually according to each category in the column
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
		} else {
			duration = "";
		}

		std::string status = displayoutput.getDisplayListStatus().at(row);

		QTableWidgetItem *taskDesc = new QTableWidgetItem(QString::fromStdString(desc));
		QTableWidgetItem *taskDuration = new QTableWidgetItem(QString::fromStdString(duration));
		QTableWidgetItem *taskStatus = new QTableWidgetItem(QString::fromStdString(status));
		
		ui.tableWidget->setItem(row, 0, taskDesc);
		ui.tableWidget->setItem(row, 1, taskDuration);
		ui.tableWidget->setItem(row, 2, taskStatus);
		
		if(status == STATUS_COMPLETE) {
			taskDesc->setBackgroundColor(QColor(235,227,205));
				taskDuration->setBackgroundColor(QColor(235,227,205));
				taskStatus->setBackgroundColor(QColor(235,227,205));
		}
		
		if(status == STATUS_OVERDUE) {
				taskDesc->setBackgroundColor(QColor(255,181,194));
				taskDuration->setBackgroundColor(QColor(255,181,194));
				taskStatus->setBackgroundColor(QColor(255,181,194));
		}

		if(status == STATUS_ONGOING) {
				taskDesc->setBackgroundColor(QColor(230,240,147));
				taskDuration->setBackgroundColor(QColor(230,240,147));
				taskStatus->setBackgroundColor(QColor(230,240,147));
		}
}

void CalenizerGUI::run(){
	std::string userInput = ui.lineEdit->text().toStdString();

	DisplayOutput displayoutput= _g_logic.executeUserInput(userInput);
	getFeedback(displayoutput);

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());

	for(int row=0; row<displayoutput.getDisplay().size(); row++){
		getTask(displayoutput,row);
		ui.tableWidget->verticalHeader()->setSectionResizeMode(row, QHeaderView::Fixed);
	}	

	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString("dd MMMM yyyy\nhh:mm ap");
	ui.label->setText(dateTimeString);

	ui.lineEdit->clear();
}

void CalenizerGUI::displayAll() {
	DisplayOutput displayoutput= _g_logic.executeUserInput(CMD_DISPLAY_ALL);
	getFeedback(displayoutput);

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());

	for(int row=0; row<displayoutput.getDisplay().size(); row++){
		getTask(displayoutput,row);
		ui.tableWidget->verticalHeader()->setSectionResizeMode(row, QHeaderView::Fixed);
	}
}

//this function check the first alphabet that user type and auto complete when the command is valid
void CalenizerGUI::checkAlphabet() {

	std::string text = ui.lineEdit->text().toStdString();

	if(text == EMPTY_STRING) {
	} else {
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
			ui.lineEdit->setText(UNDO_MSG);
		} else if (text.at(0) == 'v' && text.length() <= 5) {
			ui.lineEdit->setText(VIEW_MSG + " ");
		} else if (text.at(0) == 'q' && text.length() <= 5) {
			ui.lineEdit->setText(QUIT_MSG);
		}
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

	table->setColumnWidth(TASK_DESC, 280);
	table->setColumnWidth(TASK_DURATION, 300);
	table->setColumnWidth(TASK_STATUS,90);
	table->horizontalHeader()->setStretchLastSection(true);
}

void CalenizerGUI::initialiseTable(QTableWidget *table) {
	setColumnWidth(table);
	fixColumnWidth(table);
	table->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
	table->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
	table->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void CalenizerGUI::fixColumnWidth(QTableWidget *table) {
	
	for(unsigned int col = 0 ; col < 3; col++) {
		table->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
	}

}

void CalenizerGUI::scrollUp() {
	ui.tableWidget->verticalScrollBar()->setSliderPosition(ui.tableWidget->verticalScrollBar()->sliderPosition() - ui.tableWidget->verticalScrollBar()->pageStep());
}

void CalenizerGUI::scrollDown() {
	ui.tableWidget->verticalScrollBar()->setSliderPosition(ui.tableWidget->verticalScrollBar()->sliderPosition() + ui.tableWidget->verticalScrollBar()->pageStep());
}