
#include <QtCore/QCoreApplication>
#include <iostream>
#include <string>
#include "Logic.h"
#include "TaskStorage.h"
#include "UI.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
	UI test;
	test.ProgramLaunch();
	QCoreApplication a(argc, argv);
	return a.exec();
}
