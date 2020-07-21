#include "mainwindow.h"

#include <QApplication>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_DeleteOnClose);
    w.show();
    return a.exec();
}
