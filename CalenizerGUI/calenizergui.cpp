#include "calenizergui.h"
// v1.0
CalenizerGUI::CalenizerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPalette* palette; 
	palette = new QPalette();
	palette->setColor(QPalette::WindowText,Qt::black);
	ui.label->setPalette(*palette);
	QLineEdit *line = new QLineEdit();
	palette->setColor(QPalette::Text,Qt::black);
	ui.lineEdit->setPalette(*palette);
}

CalenizerGUI::~CalenizerGUI()
{
	delete _g_parser;
}

void CalenizerGUI::on_lineEdit_returnPressed()
{
	ui.textEdit->setTextColor(Qt::white);
	ui.textEdit->append(QString::fromStdString(_g_parser->displayCMD(ui.lineEdit->text().toStdString())));	
}
