#include "calenizergui.h"
#include <QtWidgets/QApplication>
// v1.0
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalenizerGUI w;
	w.setStyleSheet("background-color: #A52A2A ");
	w.show();
	return a.exec();
}

void CalenizerGUI::on_lineEdit_returnPressed()
{
	ui.textEdit->setTextColor(Qt::white);
	ui.textEdit->append(QString::fromStdString(_g_parser.displayCMD(ui.lineEdit->text().toStdString())));	
}
