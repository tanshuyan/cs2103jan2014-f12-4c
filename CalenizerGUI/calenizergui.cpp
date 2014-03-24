#include "calenizergui.h"
// v1.0
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
}

CalenizerGUI::~CalenizerGUI()
{

}


