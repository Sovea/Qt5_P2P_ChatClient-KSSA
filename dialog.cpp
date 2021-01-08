#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QPainter>
#include <QFile>
#include <QTextStream>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
       file.close();
//    this->setWindowTitle("KASA    查找用户");
    this->setMaximumSize(500,400);
    this->setMinimumSize(500,400);
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    flag1=true;
    flag2=true;

//    connect(ui->findlineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_findlineEdit_textChanged(QString)));
//    connect(ui->findpushButton,SIGNAL(clicked()),this,SLOT(on_findpushButton_clicked()));
//    connect(ui->typecomboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_typecomboBox_currentTextChanged(QString)));
//    connect(ui->onlineradioButton,SIGNAL(toggled(bool)),this,SLOT(on_onlineradioButton_clicked(bool)));
    ui->resultwidget->setVisible(false);
//    ui->notfoundlabel->setVisible(false);
//    ui->firstuserwidget->setVisible(false);
//    ui->seconduserwidget->setVisible(false);
//    ui->thirduserwidget->setVisible(false);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_findlineEdit_textChanged(const QString &arg1)
{
    string = arg1;
    if(this->flag1){
        QRegExp regExp{"[1-9][0-9]{6,10}"};
        ui->findlineEdit->setValidator(new QRegExpValidator(regExp,this));
        ui->findpushButton->setEnabled(ui->findlineEdit->hasAcceptableInput());
    }
    else{
        ui->findlineEdit->setValidator(0);
        ui->findpushButton->setEnabled(!arg1.isEmpty());
    }
}

//void Dialog::on_findpushButton_clicked()
//{
//    if(this->flag1&&this->flag2){//ID且需在线

//    }else if(this->flag1&&!this->flag2){//ID且可不在线

//    }else if(!this->flag1&&this->flag2){//昵称且需在线

//    }else{//昵称且可不在线

//    }
//    ui->resultwidget->setVisible(true);
//    ui->enteredlabel->setText("搜索："+string);
//    QPalette pa;
//    pa.setColor(QPalette::WindowText,Qt::darkYellow);
//    ui->enteredlabel->setPalette(pa);
//    ui->enteredlabel->adjustSize();
//    if(true){   //找到对应用户
//        ui->firstuserID->setText("1234567890");
//        ui->firstusername->setText("取名真是难");
//        ui->firstuserwidget->setVisible(true);

//        ui->seconduserID->setText("987654321");
//        ui->secondusername->setText("真难取名字");
//        ui->seconduserwidget->setVisible(true);

//        ui->thirduserID->setText("11111111");
//        ui->thirdusername->setText("名字真难取");
//        ui->thirduserwidget->setVisible(true);
//        ui->notfoundlabel->setText("成功找到对应用户!");
//        ui->notfoundlabel->adjustSize();
//        ui->notfoundlabel->setVisible(true);
//    }
//    else{   //未找到相应用户
//        ui->notfoundlabel->adjustSize();
//        ui->notfoundlabel->setVisible(true);
//    }
//}

//void Dialog::on_onlineradioButton_clicked(bool checked)
//{
//    this->flag2=checked;
//}

//void Dialog::on_typecomboBox_currentTextChanged(const QString &arg1)
//{
//    ui->findlineEdit->del();
//    ui->findlineEdit->insert("1");
//    ui->findlineEdit->clear();
//    if(!QString::compare(arg1,"用户ID"))
//    {
//        this->flag1=true;
//    }
//    else if(!QString::compare(arg1,"昵称")) this->flag1=false;
//}

//void Dialog::on_gobackButton_clicked()
//{
//    ui->resultwidget->setVisible(false);
//    ui->findlineEdit->del();
//    ui->findlineEdit->insert("1");
//    ui->findlineEdit->clear();
//}


//void Dialog::on_firstAddButton_clicked()
//{
//    //添加好友
//}

//void Dialog::on_secondAddButton_clicked()
//{
//    //添加好友
//}

//void Dialog::on_thirdAddButton_clicked()
//{
//    //添加好友
//}
