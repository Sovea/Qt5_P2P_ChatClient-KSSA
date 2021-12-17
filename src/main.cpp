#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include "Login.h"
#include "personbuddy.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.setWindowTitle("KSSA");
    l.setWindowIcon(QIcon(":/src/image/KSSA_Icon.png"));
    l.show();
    return a.exec();

}
