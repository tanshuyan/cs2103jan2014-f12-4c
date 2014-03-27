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
		int lastIndex = initialString.find_last_of("<>");
		std::string taskDesc = initialString.substr(startIndex+2,lastIndex-(startIndex+3));
		std::string duration = initialString.substr(lastIndex+1);
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(taskDesc)));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(duration)));
	}
}
