#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QPainter>
#include <QFile>
#include <QTextStream>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QFile file(":/src/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    flag1 = true;
    flag2 = true;
    ui->resultwidget->setVisible(false);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_findlineEdit_textChanged(const QString &arg1)
{
    string = arg1;
    if (this->flag1)
    {
        QRegExp regExp{"[1-9][0-9]{6,10}"};
        ui->findlineEdit->setValidator(new QRegExpValidator(regExp, this));
        ui->findpushButton->setEnabled(ui->findlineEdit->hasAcceptableInput());
    }
    else
    {
        ui->findlineEdit->setValidator(0);
        ui->findpushButton->setEnabled(!arg1.isEmpty());
    }
}
