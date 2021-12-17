#include "personbuddy.h"
#include "ui_personbuddy.h"
#include <QDesktopServices>
#include <QDebug>
#include <string>
#include <QString>
#include <QUrl>
#include <QtDebug>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
PersonBuddy::PersonBuddy(QWidget *parent) : 
    QWidget(parent),
    ui(new Ui::PersonBuddy)
{
    ui->setupUi(this);
}
void PersonBuddy::Buddy_init()
{
}
PersonBuddy::~PersonBuddy()
{
    delete ui;
}
