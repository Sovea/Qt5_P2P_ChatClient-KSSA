#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include "Login.h"
#include "personbuddy.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.setWindowTitle("KSSA");
//    w.setWindowIcon(QIcon(":/image/KSSA_Icon.png"));
//    w.show();
    Login l;
    l.setWindowTitle("KSSA");
    l.setWindowIcon(QIcon(":/image/KSSA_Icon.png"));
    l.show();
//    PersonBuddy p;
//    p.show();
    return a.exec();

}
