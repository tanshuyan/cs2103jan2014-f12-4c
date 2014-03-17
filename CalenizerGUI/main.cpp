#include "calenizergui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CalenizerGUI w;
	w.show();
	return a.exec();
}

void CalenizerGUI::on_pushButton_released()
{
	ui.textEdit->append(QString::fromStdString(_g_parser.displayCMD(ui.lineEdit->text().toStdString())));
}
