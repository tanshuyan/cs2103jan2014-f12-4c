//v1.1
#include "calenizergui.h"
#include <QtWidgets/QApplication>
#include "Windows.h"
#include <QTimer>
#include <QtCore>
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QWidget>
#include <QMainWindow>
#include <QThread>
#include <QDesktopWidget>
#include <QPainter>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    CalenizerGUI program;
    program.show();
	return app.exec();
}