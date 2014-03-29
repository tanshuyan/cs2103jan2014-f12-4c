//v1.1
#include "calenizergui.h"
#include <QtWidgets/QApplication>
#include "Windows.h"
#include <QTimer>
#include <QSplashScreen>

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
	QApplication a(argc, argv);
	
	QPixmap pixmap(":/CalenizerGUI/HwaChong.jpg");
	QSplashScreen splash(pixmap);
	splash.show();
	splash.showMessage("Loading");
	QTimer::singleShot(2000, &splash, SLOT(close()));
	Sleep(500);

    CalenizerGUI w;
    w.show();
	return a.exec();
}