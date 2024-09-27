#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "begin.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainwindow w;
    w.show();
    return QApplication::exec();
}
