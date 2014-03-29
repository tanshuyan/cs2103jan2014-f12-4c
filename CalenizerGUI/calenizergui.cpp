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

const std::string CalenizerGUI::CMD_DISPLAY_TODAY = "display today";

CalenizerGUI::CalenizerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initialiseConnections();
	todayDisplay();
	initialiseTableStyle();
	initialiseTableSize();
	_g_current_row = 0;
}

CalenizerGUI::~CalenizerGUI()
{
	
}

void CalenizerGUI::initialiseTableStyle(){
	
	//defensive coding
	if(palette !=NULL){
		delete palette;
	}

	palette = new QPalette();
	palette->setColor(QPalette::WindowText,Qt::black);
	ui.label->setPalette(*palette);

	palette->setColor(QPalette::Text,Qt::black);
	ui.lineEdit->setPalette(*palette);

	ui.tableWidget->setStyleSheet("color: black;" 
								  "gridline-color: black;"
								  "background-color: white;");

	ui.textEdit->setTextColor(Qt::blue);
	//this line of code is unecessary. if we use new, then u must destruct it, but then QlineEdit cannot be destructed. 
	//QLineEdit *line = new QLineEdit();
}

void CalenizerGUI::initialiseTableSize(){
	ui.tableWidget->setColumnWidth(0,  200);
	ui.tableWidget->setColumnWidth(1,  255);
	ui.tableWidget->setColumnWidth(2,  100);
}

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

void CalenizerGUI::getFeedback(DisplayOutput displayoutput)
{
	ui.textEdit->append(QString::fromStdString(displayoutput.getFeedBack()));
}

std::string CalenizerGUI::setStatus(std::string status)
{
		std::string taskStatus;
		if(status == STATUS_TRUE){
			taskStatus = STATUS_COMPLETE;
		} else {
			taskStatus = STATUS_INCOMPLETE;
		}
		return taskStatus;
}

void CalenizerGUI::getTask(DisplayOutput displayoutput, int row){

		std::string initialString = displayoutput.getDisplay().at(row);
		int startIndex = initialString.find_first_of("<>");

		int pos = initialString.find("<>", initialString.find("<>") + 1);
		std::string taskDesc = initialString.substr(startIndex+2,pos-(startIndex+2));

		startIndex = pos+1;
		int lastIndex = initialString.find("<>", startIndex);

		std::string duration;
		std::string status;
		if(lastIndex != initialString.npos){
			duration = initialString.substr(pos+2,lastIndex-(pos+2));
			status = initialString.substr(lastIndex+2);
		} else {
			duration = "";
			status = initialString.substr(startIndex+1);
		}

		status = setStatus(status);

		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(taskDesc)));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(duration)));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(status)));
}

void CalenizerGUI:: initialiseConnections() {
	//connect(ui.lineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkAlphabet(QString)));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(run()));
}

void CalenizerGUI::run()
{
	std::string userInput = ui.lineEdit->text().toStdString();
	//char alphabet = userInput.at(0);
	//checkAlphabet(alphabet);

	DisplayOutput displayoutput= _g_logic.executeUserInput(userInput);
	getFeedback(displayoutput);

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());

	for(int row=0; row<displayoutput.getDisplay().size(); row++){
		getTask(displayoutput,row);
	}

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
/*
//checking shd be okay, prob shd be with signal
void CalenizerGUI::checkAlphabet(QString string){
	std::string text = string.toStdString();
	char alphabet = text.at(0);

	QCursor c;
	if(alphabet == 'a'){
	ui.lineEdit->setText(ADD_MSG);
	//c.setPos (4,0);
	}

}
*/