#include "calenizergui.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include "Windows.h"

// v1.0
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QPixmap pixmap(":/CalenizerGUI/Resources/hc.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	splash.show();
	Sleep(300);

	CalenizerGUI calenizer;
	calenizer.setStyleSheet("background-color: #ffffff");
	calenizer.show();
	return app.exec();
}