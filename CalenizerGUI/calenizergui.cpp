#include "calenizergui.h"

CalenizerGUI::CalenizerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPalette* palette = new QPalette();
	palette->setColor(QPalette::WindowText,Qt::white);
	ui.label->setPalette(*palette);
	QLineEdit *line = new QLineEdit();
	palette->setColor(QPalette::Text,Qt::white);
	ui.lineEdit->setPalette(*palette);

	ui.tableWidget->setColumnWidth(0,  200);
	ui.tableWidget->setColumnWidth(1,  355);
	ui.tableWidget->setStyleSheet("color: black;" 
								  "gridline-color: white;"
								  "background-color: gray;");
	_g_current_row = 0;
}

CalenizerGUI::~CalenizerGUI()
{

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

