#include "Login.h"
#include "ui_Login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QDebug>
#include <string>
#include <QString>
#include <QUrl>
#include <QtDebug>
#include <QApplication>

Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::on_clicked_register()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://localhost/DashboardX/main-ltr/auth_register.html")));
}
int Login::on_clicked_signin()
{
    QString user_id = ui->lineEdit_Id->text();
    QString user_password = ui->lineEdit_Pw->text();
    QHostAddress serverip = QHostAddress(ui->line_ip->text());
    MainWindow *w = new MainWindow;
    w->mainwindow_get_userinfo(user_id, user_password, serverip);
    w->setWindowTitle("KSSA");
    w->setWindowIcon(QIcon(":/src/image/KSSA_Icon.png"));
    w->show();
    this->hide();
    return 1;
}
