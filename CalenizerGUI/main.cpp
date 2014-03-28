#include "calenizergui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalenizerGUI w;
	w.setStyleSheet("background-color: gray ");
	w.show();
	return a.exec();
}

void CalenizerGUI::on_lineEdit_returnPressed()
{
	DisplayOutput displayoutput = _g_logic.executeUserInput(ui.lineEdit->text().toStdString());
	ui.textEdit->setTextColor(Qt::white);
	ui.textEdit->append(QString::fromStdString(displayoutput.getFeedBack()));

	ui.tableWidget->setRowCount(displayoutput.getDisplay().size());
	for(int row=0; row<displayoutput.getDisplay().size(); row++){
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
		std::string taskStatus;
		if(status == "true\n"){
			taskStatus = "complete";
		} else {
			taskStatus = "incomplete";
		}
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(taskDesc)));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(duration)));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(taskStatus)));
	}
	ui.lineEdit->clear();
}
