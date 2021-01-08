#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personbuddy.h"
#include "ui_personbuddy.h"
#include "info_card.h"
#include "ui_info_card.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "new_friend_buddy.h"
#include "ui_new_friend_buddy.h"
#include "chatbuddy.h"
#include "ui_chatbuddy.h"
#include "bubble-widget.h"
#include "ui_bubble-widget.h"
#include "progressbar.h"
#include "ui_progressbar.h"
#include <QDesktopServices>
#include <QDebug>
#include <QString>
#include <QUrl>
#include <QDir>
#include <QApplication>
#include <QIODevice>
#include <QPainter>
#include <QPixmap>
#include <QFile>
#include <QBuffer>
#include <QDataStream>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QHostInfo>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QNetworkInterface>
#include <QContextMenuEvent>
#include <QEventLoop>
#include <QtMultimedia/QSound>
#include <QQuickWidget>
#include <QFileDialog>
static QString user_id;static QString user_password;/*qint16 myport=24600;*/
static QStringList Friends_Ids;static QString newfriend_id;static int index_friend_item;
static QString LinkId;static qint64 loadSize = 1024;static QHostAddress server_ip;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->TextMessage->close();
    this->ui->Button_Send->close();
    this->ui->Button_Close->close();
    this->ui->frame_chatbar->close();
    this->ui->frame_tools->hide();
    this->ui->pushButton_sendfile->close();
    ServerMapper = new QSignalMapper();
    ClientMapper = new QSignalMapper();
    LinkId="";
    this->tempP2P=new QTcpSocket(this);
    this->structinit();
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
       file.close();
       this->StartServer();
      this->clickLabel = new ClickedLabel(this);
      this->clickLabel->setGeometry(830,30,121,31);
      QFont font("Microsoft YaHei", 12, 50);
      this->clickLabel->setFont(font);
      this->newmessage_bells=new QSound(":/sound/newmessage.wav");
      connect(this->ui->listWidget_friends,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(ItemDoubleClicked(QListWidgetItem *)));
      connect(ui->Button_Close,SIGNAL(clicked()),this,SLOT(Close_Chatwindow()));
      connect(this->clickLabel,SIGNAL(clicked()),this,SLOT(on_label_clicked()));
      connect(ui->Button_AddFriend,SIGNAL(clicked()),this,SLOT(add_one_friend()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::structinit(){
    this->stackwidget.count=0;
    this->stackwidget.userid.clear();
    this->LinkInfo.count=0;
    this->LinkInfo.userid.clear();
    this->LinkInfo.linktype.clear();
    this->LinkInfo.username.clear();
    this->FriendsInfo.count=0;
    this->FriendsInfo.userid.clear();
    this->FriendsInfo.message.clear();
    this->FriendsInfo.clientid.clear();
    this->FriendsInfo.username.clear();
    this->FriendsInfo.useremail.clear();
    this->FriendsInfo.url_headimg.clear();
    this->ListBubbleWidgets.clear();
    this->indexBubbleWidget=-1;
    this->countBubbleWidget=0;
    this->MyselfInfo.type=Userinfo;

    index_friend_item=0;
//    this->Alive_server_users.count=0;
//    this->Alive_server_users.userid.clear();
//    this->Alive_server_users.ipaddress.clear();
//    this->Alive_server_users.port.clear();
//    this->Alive_client_users.count=0;
//    this->Alive_client_users.userid.clear();
//    this->Alive_client_users.ipaddress.clear();
//    this->Alive_client_users.port.clear();
}
void MainWindow::StartServer()
{
    this->tcpServer = new QTcpServer(this);
    this->tcpServer->listen(QHostAddress::Any,0);
    qDebug()<<"Server is running...";
    connect(this->tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect()));
}
void MainWindow::newConnect(){
    qDebug()<<"There is a new friend want to chat with me...";
//-----------------------------------------------------------------------------
    this->nowP2P=this->tcpServer->nextPendingConnection();
    LinkInfo.ListTcpsocket.append(this->nowP2P);
    //Alive_server_users.count++;
    qDebug()<<"当前列表套接字数目："<<LinkInfo.ListTcpsocket.count();
    ServerMapper->setMapping(LinkInfo.ListTcpsocket.last(),LinkInfo.ListTcpsocket.count());
    connect(LinkInfo.ListTcpsocket.last(), SIGNAL(readyRead()), ServerMapper, SLOT(map()));
    connect(ServerMapper, SIGNAL(mapped(int)), this, SLOT(changeTempTcpsocket(int)));
//-----------------------------------------------------------------------------
//    this->nowP2P = this->tcpServer->nextPendingConnection();
    //connect(this->nowP2P,SIGNAL(readyRead()),this,SLOT(ReadFriendsMessages()));
}
void MainWindow::changeTempTcpsocket(int index){
    qDebug()<<"当前套接字index："<<index;
    this->tempP2P=LinkInfo.ListTcpsocket[index-1];
    QHostAddress hisIp= this->tempP2P->peerAddress();
    int inthisPort = this->tempP2P->peerPort();
    QHostAddress myIp= this->tempP2P->localAddress();
    int intmyPort = this->tempP2P->localPort();
    qDebug()<<"他的ip地址是";
    qDebug()<<hisIp<<endl;
    qDebug()<<"他的ip端口是";
    qDebug()<<inthisPort<<endl;
    qDebug()<<"我的ip地址是";
    qDebug()<<myIp<<endl;
    qDebug()<<"我的ip端口是";
    qDebug()<<intmyPort<<endl;
    ReadFriendsMessages();

}
void MainWindow::TwochangeTempTcpsocket(int index){
    qDebug()<<"当前套接字index："<<index;
    this->tempP2P=LinkInfo.ListTcpsocket[index-1];
    QHostAddress hisIp= this->tempP2P->peerAddress();
    int inthisPort = this->tempP2P->peerPort();
    QHostAddress myIp= this->tempP2P->localAddress();
    int intmyPort = this->tempP2P->localPort();
    qDebug()<<"他的ip地址是";
    qDebug()<<hisIp<<endl;
    qDebug()<<"他的ip端口是";
    qDebug()<<inthisPort<<endl;
    qDebug()<<"我的ip地址是";
    qDebug()<<myIp<<endl;
    qDebug()<<"我的ip端口是";
    qDebug()<<intmyPort<<endl;
    TwoReadFriendsMessages();

}
void MainWindow::changeServerTcpsocket(int index){
    this->nowP2P=LinkInfo.ListTcpsocket[index-1];
    QHostAddress hisIp= this->nowP2P->peerAddress();
    int inthisPort = this->nowP2P->peerPort();
    QHostAddress myIp= this->nowP2P->localAddress();
    int intmyPort = this->nowP2P->localPort();
    qDebug()<<"他的ip地址是";
    qDebug()<<hisIp<<endl;
    qDebug()<<"他的ip端口是";
    qDebug()<<inthisPort<<endl;
    qDebug()<<"我的ip地址是";
    qDebug()<<myIp<<endl;
    qDebug()<<"我的ip端口是";
    qDebug()<<intmyPort<<endl;
    ReadFriendsMessages();
}
void MainWindow::changeClientTcpsocket(int index){
    this->actP2P=LinkInfo.ListTcpsocket[index-1];
    QHostAddress hisIp= this->nowP2P->peerAddress();
    int inthisPort = this->nowP2P->peerPort();
    QHostAddress myIp= this->nowP2P->localAddress();
    int intmyPort = this->nowP2P->localPort();
    qDebug()<<"他的ip地址是";
    qDebug()<<hisIp<<endl;
    qDebug()<<"他的ip端口是";
    qDebug()<<inthisPort<<endl;
    qDebug()<<"我的ip地址是";
    qDebug()<<myIp<<endl;
    qDebug()<<"我的ip端口是";
    qDebug()<<intmyPort<<endl;
    TwoReadFriendsMessages();
}
void MainWindow::connectServer()
{
    this->tcpSocket = new QTcpSocket(this);
    this->tcpSocket->abort();
//    this->nowP2P->bind(24600);
    Friends_Ids.clear();
    this->timer=new QTimer(this);
    this->timer->start(10000);
    QString Ipaddress = this->GetLocalIPAddress();
    qDebug()<<Ipaddress;
    QHostAddress Myip = QHostAddress(Ipaddress);
    this->tcpSocket->connectToHost(QHostAddress(server_ip),24576);
//    this->tcpSocket->waitForConnected(30000);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(Send_HeartBeat()));
    connect(this->tcpSocket,SIGNAL(connected()),this,SLOT(Send_login_Messages()));
    connect(this->tcpSocket,SIGNAL(readyRead()),this,SLOT(ReadMessages()));

}
void MainWindow::Send_login_Messages(){
    qDebug()<<"I am sending the Login message...";
    QByteArray data;
    data.resize(sizeof(LoginMessage));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    LoginMessage Message;
    Message.type=UsrLogin;
    qDebug()<<user_id <<user_password<<endl;
    Message.userid=user_id;
    Message.password=user_password;
    Message.Message="I want to login in,please.";
    out<<Message.type<<Message.userid<<Message.password<<Message.Message<<true;
    buffer.close();
    this->tcpSocket->write(data);
    this->tcpSocket->flush();
}
void MainWindow::SendMessages(QByteArray data){
    qDebug()<<"I am sending the message...";
    this->tcpSocket->waitForBytesWritten();
    this->tcpSocket->write(data);
    this->tcpSocket->flush();
}
void MainWindow::ReadMessages(){
    qDebug()<<"I get the message!";
    QByteArray data = this->tcpSocket->readAll();
    QBuffer buf(&data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
        MsgType type;
        in>>type;
        qDebug()<<type;
        if(type==UsrLogin){
            LoginMessage Message;
            in>>Message.userid>>Message.password>>Message.Message>>Message.success;
            qDebug()<<Message.Message;
        }
        else if(type==Userinfo){
            struct_Userinfo User_info;
            in>>User_info.username;
            in>>User_info.userid;
            in>>User_info.useremail;
            in>>User_info.url_headimg;
            qDebug()<<User_info.username;
            this->MyselfInfo.userid=User_info.userid;
            this->MyselfInfo.username=User_info.username;
            this->MyselfInfo.useremail=User_info.useremail;
            this->clickLabel->setText(User_info.username);
            QStringList list = User_info.url_headimg.split(".");
            QNetworkRequest request;
            request.setUrl(QUrl(User_info.url_headimg));
            QNetworkAccessManager *manager = new QNetworkAccessManager();
            QNetworkReply *reply = manager->get(request);
            QEventLoop loop;
            QObject::connect(reply,SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            if (reply->error() != QNetworkReply::NoError)
                {
                    ui->label_headimg->setText("Error!");
                }
            else{
                QFile file(QDir::currentPath()+"/friends_headimg/Me."+list[1]);
                    if(!file.open(QIODevice::WriteOnly))
                        ui->label_headimg->setText("Error!");
                    file.write(reply->readAll());
                    file.close();
                    delete reply;
            }
                QString file = QDir::currentPath()+"/friends_headimg/Me."+list[1];
                this->MyselfInfo.url_headimg=file;
                QPixmap pixmapa(file);
                QPixmap pixmap(60,60);
                pixmap.fill(Qt::transparent);
                QPainter painter(&pixmap);
                painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
                QPainterPath path;
                path.addEllipse(0, 0, 60, 60);
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, 60, 60, pixmapa);
                ui->label_headimg->setPixmap(pixmap);
                QStringList nomean={""};
                QByteArray data;
                data.resize(sizeof(struct_Friendsinfo));
                QBuffer buffer(&data);
                buffer.open(QIODevice::WriteOnly);
                QDataStream out(&buffer);
                struct_Friendsinfo Message;
                Message.type=Friendsinfo;
                Message.count=0;
                Message.clientid=user_id;
                Message.userid=nomean;
                Message.message="I want my friends' info.";
                Message.username=nomean;
                Message.useremail=nomean;
                Message.url_headimg=nomean;
                out<<Message.type<<Message.count<<Message.clientid<<Message.message<<Message.username<<Message.userid<<Message.useremail<<Message.url_headimg;
                buffer.close();
                this->SendMessages(data);
        }
        else if(type==Friendsinfo){
            struct_Friendsinfo Friends;
            in>>Friends.count;
            in>>Friends.clientid;
            in>>Friends.message;
            in>>Friends.userid;
            in>>Friends.username;
            in>>Friends.useremail;
            in>>Friends.url_headimg;
            Friends_Ids=Friends.userid;
            FriendsInfo.count=Friends.count;
            FriendsInfo.userid=Friends.userid;
            FriendsInfo.username=Friends.username;
            FriendsInfo.useremail=Friends.useremail;
            for(int i=0;i<Friends.count;i++){
                QListWidgetItem *item=new QListWidgetItem;
                PersonBuddy *newBuddy = new PersonBuddy;
                newBuddy->ui->label_friend_username->setText(Friends.username[i]);
                newBuddy->ui->label_friend_usersign->setText("Hello World!");
                QString file = Friends.url_headimg[i];
                QStringList list = file.split(".");
                QNetworkRequest request;
                request.setUrl(QUrl(file));
                QNetworkAccessManager *manager = new QNetworkAccessManager();
                QNetworkReply *reply = manager->get(request);
                QEventLoop loop;
                QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
                loop.exec();
                if (reply->error()!=QNetworkReply::NoError)
                    {
                        newBuddy->ui->label_friend_headimg->setText("Error!");
                    }
                else{
//                    qDebug()<<QDir::currentPath();
                    QString save_road=QDir::currentPath()+"/friends_headimg/"+Friends.userid[i]+"."+list[1];
                    QFile file_save(save_road);
                    FriendsInfo.url_headimg<<save_road;
                        if(!file_save.open(QIODevice::WriteOnly))
                            ui->label_headimg->setText("Error!");
                        file_save.write(reply->readAll());
                        file_save.close();
                        delete reply;
                        QPixmap pixmapa(save_road);
                        QPixmap pixmap(40,40);
                        pixmap.fill(Qt::transparent);
                        QPainter painter(&pixmap);
                        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
                        QPainterPath path;
                        path.addEllipse(0, 0, 40, 40);
                        painter.setClipPath(path);
                        painter.drawPixmap(0, 0, 40, 40, pixmapa);
                        newBuddy->ui->label_friend_headimg->setPixmap(pixmap);
                        ui->listWidget_friends->addItem(item);
                        ui->listWidget_friends->setItemWidget(item,newBuddy);
                }

            }

        }
        else if(type==LinkFriend){
            struct_Link_friend linkfriend;
            in>>linkfriend.userid;
            in>>linkfriend.port;
            in>>linkfriend.ipaddress;
            in>>linkfriend.online;
            qDebug()<<linkfriend.userid;
            qDebug()<<linkfriend.port;
            qDebug()<<linkfriend.ipaddress;
            qDebug()<<linkfriend.online;
            if(linkfriend.online==true){
                    qDebug()<<"正在连接";
                    LinkInfo.count++;
                    LinkInfo.userid<<linkfriend.userid;
                    int index = FriendsInfo.userid.indexOf(linkfriend.userid);
                    LinkInfo.username<<FriendsInfo.username[index];
                    LinkInfo.linktype<<"0";
                    this->stackwidget.count++;
                    this->stackwidget.userid<<linkfriend.userid;
                    LinkId=linkfriend.userid;
                    BubbleWidget *newBubbleWidget = new BubbleWidget(this->ui->chat_widget);
                    newBubbleWidget->setGeometry(0,0,731,341);
                    this->ListBubbleWidgets.append(newBubbleWidget);
                    if(this->indexBubbleWidget>=0){
                        this->ListBubbleWidgets[this->indexBubbleWidget]->hide();
                    }
                    this->countBubbleWidget++;
                    this->indexBubbleWidget=this->stackwidget.userid.indexOf(linkfriend.userid);
                    this->ListBubbleWidgets[this->indexBubbleWidget]->show();
                    this->LinktoFriends(linkfriend.port,linkfriend.ipaddress);
                    disconnect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(SendFriendsMessages()));
                    connect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(TwoSendFriendsMessages()));
                    disconnect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(select_the_file()));
                    connect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(Twoselect_the_file()));
//                    disconnect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(SendFriendsMessages()));
//                    connect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(TwoSendFriendsMessages()));
            }


        }
        else if(type==DeleteFriend){
            struct_handle_friend handle_friend;
            in>>handle_friend.Myid;
            in>>handle_friend.Hisid;
            in>>handle_friend.ifsuccess;
            qDebug()<<handle_friend.ifsuccess;
            if(handle_friend.ifsuccess==true){
            int deleindex=FriendsInfo.userid.indexOf(handle_friend.Hisid);
            FriendsInfo.count--;
            FriendsInfo.userid.removeAt(deleindex);
            FriendsInfo.username.removeAt(deleindex);
            FriendsInfo.useremail.removeAt(deleindex);
            FriendsInfo.url_headimg.removeAt(deleindex);
            ui->listWidget_friends->takeItem(deleindex);
            }
        }
        else if(type==SelectFriend){
            struct_Userinfo thisfriend;
            in>>thisfriend.username;
            in>>thisfriend.userid;
            in>>thisfriend.useremail;
            in>>thisfriend.url_headimg;
            newfriend_id=thisfriend.userid;
            qDebug()<<"目标用户的信息为："<<thisfriend.username<<thisfriend.userid<<thisfriend.useremail<<thisfriend.url_headimg;
//            this->dialog_addfriend->ui->firstuserID->setText(thisfriend.userid);
//            this->dialog_addfriend->ui->firstusername->setText(thisfriend.username);
            this->dialog_addfriend->ui->Resultlist->clear();
            QListWidgetItem *item=new QListWidgetItem;
            new_friend_buddy *newfriendBuddy = new new_friend_buddy();
            newfriendBuddy->ui->label_name->setText(thisfriend.username);
            newfriendBuddy->ui->label_id->setText(thisfriend.userid);
            QString file = thisfriend.url_headimg;
            QStringList list = file.split(".");
            QNetworkRequest request;
            request.setUrl(QUrl(file));
            QNetworkAccessManager *manager = new QNetworkAccessManager();
            QNetworkReply *reply = manager->get(request);
            QEventLoop loop;
            QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
            loop.exec();
            if (reply->error()!=QNetworkReply::NoError)
                {
                    newfriendBuddy->ui->label_headimg->setText("Error!");
                }
            else{
//                    qDebug()<<QDir::currentPath();
                QString save_road=QDir::currentPath()+"/friends_headimg/"+thisfriend.userid+"."+list[1];
                QFile file_save(save_road);
                FriendsInfo.url_headimg<<save_road;
                    if(!file_save.open(QIODevice::WriteOnly))
                        ui->label_headimg->setText("Error!");
                    file_save.write(reply->readAll());
                    file_save.close();
                    delete reply;
                    QPixmap pixmapa(save_road);
                    QPixmap pixmap(70,70);
                    pixmap.fill(Qt::transparent);
                    QPainter painter(&pixmap);
                    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
                    QPainterPath path;
                    path.addEllipse(0, 0, 70, 70);
                    painter.setClipPath(path);
                    painter.drawPixmap(0, 0, 70, 70, pixmapa);
                    newfriendBuddy->ui->label_headimg->setPixmap(pixmap);
            }
            this->dialog_addfriend->ui->Resultlist->addItem(item);
            this->dialog_addfriend->ui->Resultlist->setItemWidget(item,newfriendBuddy);
            if(this->dialog_addfriend->ui->Resultlist->count()>0){
                connect(this->dialog_addfriend->ui->FixButton,SIGNAL(clicked()),this,SLOT(add_this_friend()));
            }
        }
        else if(type==AddFriend){
            struct_handle_friend addfriend;
            in>>addfriend.Myid;
            in>>addfriend.Hisid;
            in>>addfriend.ifsuccess;
            if(addfriend.ifsuccess==true){
            this->dialog_addfriend->ui->Resultlabel->setText("添加好友成功！");
            this->dialog_addfriend->ui->Resultlabel->show();
            QStringList nomean={""};
            QByteArray data;
            data.resize(sizeof(struct_Friendsinfo));
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            QDataStream out(&buffer);
            struct_Friendsinfo Message;
            Message.type=Friendsinfo;
            Message.count=0;
            Message.clientid=user_id;
            Message.userid=nomean;
            Message.message="I want my friends' info.";
            Message.username=nomean;
            Message.useremail=nomean;
            Message.url_headimg=nomean;
            out<<Message.type<<Message.count<<Message.clientid<<Message.message<<Message.username<<Message.userid<<Message.useremail<<Message.url_headimg;
            buffer.close();
            this->ui->listWidget_friends->clear();
            this->SendMessages(data);
            }
        }
}
void MainWindow::LinktoFriends(int port,QHostAddress address){
    qDebug()<<"目标"<<port<<address;
    this->actP2P=new QTcpSocket(this);
    this->actP2P->abort();
    //connect(this->actP2P,SIGNAL(readyRead()),this,SLOT(TwoReadFriendsMessages()));

    this->actP2P->connectToHost(address,port);
    LinkInfo.ListTcpsocket.append(this->actP2P);
    qDebug()<<"当前列表套接字数目："<<LinkInfo.ListTcpsocket.count();
    connect(LinkInfo.ListTcpsocket.last(), SIGNAL(readyRead()), ClientMapper, SLOT(map()));
    connect(this->actP2P,SIGNAL(connected()),this,SLOT(TwoSend_Hello_Messages()));
    ClientMapper->setMapping(LinkInfo.ListTcpsocket.last(),LinkInfo.ListTcpsocket.count());
    connect(ClientMapper, SIGNAL(mapped(int)), this, SLOT(TwochangeTempTcpsocket(int)));
}
void MainWindow::Send_Hello_Messages(){

    QByteArray data;
    data.resize(sizeof(struct_HelloMyfriend));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    struct_HelloMyfriend Hello;
    Hello.type=HelloToMyfriend;
    Hello.userid=this->MyselfInfo.userid;
    Hello.username=this->MyselfInfo.username;
    Hello.Message="Hello!";
    out<<Hello.type<<Hello.userid<<Hello.username<<Hello.Message;
    buffer.close();
    this->nowP2P->write(data);
    this->nowP2P->flush();
}
void MainWindow::TwoSend_Hello_Messages(){
    //------------------------------------------------------


    //------------------------------------------------------
    QByteArray data;
    data.resize(sizeof(struct_HelloMyfriend));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    struct_HelloMyfriend Hello;
    Hello.type=HelloToMyfriend;
    Hello.userid=this->MyselfInfo.userid;
    Hello.Message="Hello2!";
    out<<Hello.type<<Hello.userid<<Hello.Message;
    buffer.close();
    this->actP2P->write(data);
    this->actP2P->flush();
}
void MainWindow::ReadFriendsMessages(){
    qDebug()<<"I get the message from my friend!";
    QByteArray data = this->tempP2P->readAll();
    QBuffer buf(&data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
        MsgType type;
        in>>type;
        qDebug()<<type;
        if(type==HelloToMyfriend){
            struct_HelloMyfriend Hello;
            in>>Hello.userid;
            in>>Hello.username;
            in>>Hello.Message;
            qDebug()<<Hello.userid<<Hello.username<<Hello.Message;
            if((LinkInfo.userid.contains(Hello.userid)==false)&&(this->stackwidget.userid.contains(Hello.userid)==false)){
                LinkInfo.count++;
                LinkInfo.userid<<Hello.userid;
                LinkInfo.username<<Hello.username;
                LinkInfo.linktype<<"1";
                this->stackwidget.count++;
                this->stackwidget.userid<<Hello.userid;
                this->countBubbleWidget++;
                BubbleWidget *newBubbleWidget = new BubbleWidget(this->ui->chat_widget);
                newBubbleWidget->setGeometry(0,0,731,341);
                this->ListBubbleWidgets.append(newBubbleWidget);
            }
        }
        else if(type==Msg){
            this->newmessage_bells->play();
            NomalMessage Message;
            in>>Message.userid;
            in>>Message.message;
            qDebug()<<Message.userid<<Message.message;
            if(Message.userid!=""){
                int indexinfo=this->FriendsInfo.userid.indexOf(Message.userid);
                QString headimg_url=this->FriendsInfo.url_headimg[indexinfo];
                QStringList list = headimg_url.split(".");
                QString headimg = QDir::currentPath()+"/friends_headimg/"+Message.userid+"."+list[1];
                int indexDesBubbleWidget = this->stackwidget.userid.indexOf(Message.userid);
                this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("He","Me",headimg,Message.message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),"");
            }
        }
        else if(type==emitFile){
            FileMessage filemessage;
            filemessage.totalsize=0;
            in>>filemessage.userid>>filemessage.filesize>>filemessage.filetype>>filemessage.filename>>filemessage.totalsize;
            qDebug()<<"总大小为"<<filemessage.totalsize;
//          qDebug()<<"需要接收的文件大小为"<<filemessage.totalsize-sizeof (type)-sizeof (filemessage.userid)-sizeof (filemessage.filesize)-sizeof (filemessage.filetype)-sizeof (filemessage.filename);
            QString filepath =QDir::currentPath()+"/files/"+filemessage.filename;
            qDebug()<<"接收到的文件信息是:"<<filemessage.filename<<filemessage.filesize<<filemessage.filetype;
            this->FILEMessage.userid=filemessage.userid;
            this->FILEMessage.filesize=filemessage.filesize;
            this->FILEMessage.filetype=filemessage.filetype;
            this->FILEMessage.filename=filemessage.filename;
            this->recvfilesize=filemessage.filesize;
            QByteArray data;
            data.resize(sizeof(structemitFile));
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            QDataStream out(&buffer);
            structemitFile TextMessage;
            TextMessage.type=accessFile;
            TextMessage.success=true;
            out<<TextMessage.type<<TextMessage.success;
            buffer.close();
            this->bytesrecved=0;
            this->bytestorecv=0;
            this->recvfile=new QFile(filepath);
            this->recvfile->open(QIODevice::WriteOnly);
            this->tempP2P->waitForBytesWritten();
            this->tempP2P->write(data);
            this->tempP2P->flush();
            this->recvbar = new progressbar();
            this->recvbar->ui->label_headtext->setText("正在接收...");
            this->recvbar->ui->progressBar->setOrientation(Qt::Horizontal);
            this->recvbar->ui->progressBar->setMinimum(0);
            this->recvbar->ui->progressBar->setMaximum(100);
            this->recvbar->ui->progressBar->setValue(0);
            this->recvbar->show();
        }
        else if(type==accessFile){
            bool ifaccess;
            in>>ifaccess;
            if(ifaccess==true){
                if(this->bytestosend>0){
                    structFilecontent filecontent;
                    filecontent.bytearray.clear();
                    filecontent.type=File;
                    if(bytessended==0){
                        filecontent.iffirst=1;
                    }
                    else{
                        filecontent.iffirst=0;
                    }
                    filecontent.bytearray=this->sendfile->read(qMin(bytestosend,loadSize));
                    this->bytessended+=qMin(this->bytestosend,loadSize);
                    this->bytestosend-=qMin(this->bytestosend,loadSize);
                    if(this->bytestosend>0){
                        filecontent.ifend=0;
                    }
                    else{
                        filecontent.ifend=1;
                    }
                    QByteArray data;
                    data.clear();
                    data.resize(sizeof(structFilecontent));
                    QBuffer buffer(&data);
                    buffer.open(QIODevice::WriteOnly);
                    QDataStream out(&buffer);
                    out<<filecontent.type<<filecontent.bytearray<<filecontent.iffirst<<filecontent.ifend;
                    buffer.close();
                    this->tempP2P->waitForBytesWritten();
                    this->tempP2P->write(data);
                    this->tempP2P->flush();
//                    qDebug()<<bytessended<<int((double(bytessended)/double(filemessage.filesize))*100);
                    this->sendbar->ui->progressBar->setValue(qMin(100,int((double(this->bytessended)/double(this->sendfilesize))*100)));
                    if(this->sendbar->ui->progressBar->value()==100){
                        this->newmessage_bells->play();
                        this->sendbar->ui->label_headtext->setText("发送完成！");
                        int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
                        QString message=this->FILEMessage.filename;
                        QString filetype=this->FILEMessage.filetype;
                        QString filetype_icon = QDir::currentPath()+"/icon_file/"+filetype+".png";
                        this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("Me","He",this->MyselfInfo.url_headimg,message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),filetype_icon);

                    }
                }
                }
        }
        else if(type==File){

            structFilecontent filecontent;
            in>>filecontent.bytearray;
            in>>filecontent.iffirst;
            in>>filecontent.ifend;
            bytestorecv=this->FILEMessage.filesize;

            if(filecontent.ifend==true&&filecontent.iffirst==true){
                this->bytestorecv=this->FILEMessage.filesize;
//                this->recvfile->open(QIODevice::WriteOnly);
                this->recvfile->write(filecontent.bytearray);
                this->bytestorecv=0;
                this->bytestorecv=this->FILEMessage.filesize;
                this->recvfile->close();
            }
            else if(filecontent.ifend==false&&filecontent.iffirst==true){
                this->bytestorecv=this->FILEMessage.filesize;
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved+=filecontent.bytearray.size();
                this->bytestorecv-=filecontent.bytearray.size();
                QByteArray data;
                data.resize(sizeof(structemitFile));
                QBuffer buffer(&data);
                buffer.open(QIODevice::WriteOnly);
                QDataStream out(&buffer);
                structemitFile TextMessage;
                TextMessage.type=accessFile;
                TextMessage.success=true;
                out<<TextMessage.type<<TextMessage.success;
                buffer.close();
                this->tempP2P->waitForBytesWritten();
                this->tempP2P->write(data);
                this->tempP2P->flush();
            }
            else if(filecontent.ifend==false&&filecontent.iffirst==false){
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved+=filecontent.bytearray.size();
                this->bytestorecv-=filecontent.bytearray.size();
                QByteArray data;
                data.resize(sizeof(structemitFile));
                QBuffer buffer(&data);
                buffer.open(QIODevice::WriteOnly);
                QDataStream out(&buffer);
                structemitFile TextMessage;
                TextMessage.type=accessFile;
                TextMessage.success=true;
                out<<TextMessage.type<<TextMessage.success;
                buffer.close();
                this->tempP2P->waitForBytesWritten();
                this->tempP2P->write(data);
                this->tempP2P->flush();
            }
            else if(filecontent.ifend==true&&filecontent.iffirst==false){
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved=this->recvfilesize;
                this->bytestorecv=0;
                recvfile->close();
            }
            this->recvbar->ui->progressBar->setValue(qMin(100,int((double(this->bytesrecved)/double(this->recvfilesize))*100)));
            if(this->recvbar->ui->progressBar->value()==100){
                this->newmessage_bells->play();
                this->recvbar->ui->label_headtext->setText("接收完成！");
                int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
                int index_friend=FriendsInfo.userid.indexOf(LinkId);
                QString friend_headimg = FriendsInfo.url_headimg[index_friend];
                QString message=this->FILEMessage.filename;
                QString filetype=this->FILEMessage.filetype;
                QString filetype_icon = QDir::currentPath()+"/icon_file/"+filetype+".png";
                this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("He","Me",friend_headimg,message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),filetype_icon);

            }

}
}
void MainWindow::SendFriendsMessages(){
    qDebug()<<"I am sending the message to my friend...";
    if(this->ui->TextMessage->toPlainText()==""){
        qDebug()<<"输出内容不能为空。";
    }
    else{
        QByteArray data;
        data.resize(sizeof(NomalMessage));
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        NomalMessage TextMessage;
        TextMessage.type=Msg;
        TextMessage.userid=user_id;
        TextMessage.message=this->ui->TextMessage->toPlainText();
        out<<TextMessage.type<<TextMessage.userid<<TextMessage.message;
        buffer.close();
        this->ui->TextMessage->clear();
        this->nowP2P->waitForBytesWritten();
        this->nowP2P->write(data);
        this->nowP2P->flush();
        QString headimg_url=this->MyselfInfo.url_headimg;
        QStringList list = headimg_url.split(".");
        QString headimg = QDir::currentPath()+"/friends_headimg/"+this->MyselfInfo.userid+"."+list[1];
        int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
        this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("Me","He",headimg,TextMessage.message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),"");
    }

}
void MainWindow::TwoReadFriendsMessages(){
    qDebug()<<"I get the 2message from my friend!";
    QByteArray data = this->tempP2P->readAll();
    QBuffer buf(&data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
        MsgType type;
        in>>type;
        qDebug()<<type;
        if(type==HelloToMyfriend){
            struct_HelloMyfriend Hello;
            in>>Hello.userid;
            in>>Hello.username;
            in>>Hello.Message;
            qDebug()<<Hello.userid<<Hello.username<<Hello.Message;
            if((LinkInfo.userid.contains(Hello.userid)==false)&&(this->stackwidget.userid.contains(Hello.userid)==false)){
                LinkInfo.count++;
                LinkInfo.userid<<Hello.userid;
                LinkInfo.username<<Hello.username;
                LinkInfo.linktype<<"2";
                this->stackwidget.count++;
                this->stackwidget.userid<<Hello.userid;
                this->countBubbleWidget++;
                BubbleWidget *newBubbleWidget = new BubbleWidget(this->ui->chat_widget);
                newBubbleWidget->setGeometry(0,0,731,341);
                this->ListBubbleWidgets.append(newBubbleWidget);
            }
        }
        else if(type==Msg){
            this->newmessage_bells->play();
            NomalMessage Message;
            in>>Message.userid;
            in>>Message.message;
            qDebug()<<Message.message;
            int indexinfo=this->FriendsInfo.userid.indexOf(Message.userid);
            QString headimg_url=this->FriendsInfo.url_headimg[indexinfo];
            QStringList list = headimg_url.split(".");
            QString headimg = QDir::currentPath()+"/friends_headimg/"+Message.userid+"."+list[1];
            int indexDesBubbleWidget = this->stackwidget.userid.indexOf(Message.userid);
            this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("He","Me",headimg,Message.message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),"");
        }
        else if(type==emitFile){
            FileMessage filemessage;
            filemessage.totalsize=0;
            in>>filemessage.userid>>filemessage.filesize>>filemessage.filetype>>filemessage.filename>>filemessage.totalsize;
            qDebug()<<"总大小为"<<filemessage.totalsize;
//          qDebug()<<"需要接收的文件大小为"<<filemessage.totalsize-sizeof (type)-sizeof (filemessage.userid)-sizeof (filemessage.filesize)-sizeof (filemessage.filetype)-sizeof (filemessage.filename);
            QString filepath =QDir::currentPath()+"/files/"+filemessage.filename;
            qDebug()<<"接收到的文件信息是:"<<filemessage.filename<<filemessage.filesize<<filemessage.filetype;
            this->FILEMessage.userid=filemessage.userid;
            this->FILEMessage.filesize=filemessage.filesize;
            this->FILEMessage.filetype=filemessage.filetype;
            this->FILEMessage.filename=filemessage.filename;
            this->recvfilesize=filemessage.filesize;
            QByteArray data;
            data.resize(sizeof(structemitFile));
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            QDataStream out(&buffer);
            structemitFile TextMessage;
            TextMessage.type=accessFile;
            TextMessage.success=true;
            out<<TextMessage.type<<TextMessage.success;
            buffer.close();
            this->bytesrecved=0;
            this->bytestorecv=0;
            this->recvfile=new QFile(filepath);
            this->recvfile->open(QIODevice::WriteOnly);
            this->tempP2P->waitForBytesWritten();
            this->tempP2P->write(data);
            this->tempP2P->flush();
            this->recvbar = new progressbar();
            this->recvbar->ui->label_headtext->setText("正在接收...");
            this->recvbar->ui->progressBar->setOrientation(Qt::Horizontal);
            this->recvbar->ui->progressBar->setMinimum(0);
            this->recvbar->ui->progressBar->setMaximum(100);
            this->recvbar->ui->progressBar->setValue(0);
            this->recvbar->show();
        }
        else if(type==accessFile){
            bool ifaccess;
            in>>ifaccess;
            if(ifaccess==true){
                if(this->bytestosend>0){
                    structFilecontent filecontent;
                    filecontent.bytearray.clear();
                    filecontent.type=File;
                    if(bytessended==0){
                        filecontent.iffirst=1;
                    }
                    else{
                        filecontent.iffirst=0;
                    }
                    filecontent.bytearray=this->sendfile->read(qMin(bytestosend,loadSize));
                    this->bytessended+=qMin(this->bytestosend,loadSize);
                    this->bytestosend-=qMin(this->bytestosend,loadSize);
                    if(this->bytestosend>0){
                        filecontent.ifend=0;
                    }
                    else{
                        filecontent.ifend=1;
                    }
                    QByteArray data;
                    data.clear();
                    data.resize(sizeof(structFilecontent));
                    QBuffer buffer(&data);
                    buffer.open(QIODevice::WriteOnly);
                    QDataStream out(&buffer);
                    out<<filecontent.type<<filecontent.bytearray<<filecontent.iffirst<<filecontent.ifend;
                    buffer.close();
                    this->tempP2P->waitForBytesWritten();
                    this->tempP2P->write(data);
                    this->tempP2P->flush();
//                    qDebug()<<bytessended<<int((double(bytessended)/double(filemessage.filesize))*100);
                    this->sendbar->ui->progressBar->setValue(qMin(100,int((double(this->bytessended)/double(this->sendfilesize))*100)));
                    if(this->sendbar->ui->progressBar->value()==100){
                        this->newmessage_bells->play();
                        this->sendbar->ui->label_headtext->setText("发送完成！");
                        int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
                        QString message=this->FILEMessage.filename;
                        QString filetype=this->FILEMessage.filetype;
                        qDebug()<<"文件类型为"<<filetype;
                        QString filetype_icon = QDir::currentPath()+"/icon_file/"+filetype+".png";
                        this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("Me","He",this->MyselfInfo.url_headimg,message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),filetype_icon);
                    }
                }
                }
        }
        else if(type==File){

            structFilecontent filecontent;
            in>>filecontent.bytearray;
            in>>filecontent.iffirst;
            in>>filecontent.ifend;
            bytestorecv=this->FILEMessage.filesize;

            if(filecontent.ifend==true&&filecontent.iffirst==true){
                this->bytestorecv=this->FILEMessage.filesize;
//                this->recvfile->open(QIODevice::WriteOnly);
                this->recvfile->write(filecontent.bytearray);
                this->bytestorecv=0;
                this->bytestorecv=this->FILEMessage.filesize;
                this->recvfile->close();
            }
            else if(filecontent.ifend==false&&filecontent.iffirst==true){
                this->bytestorecv=this->FILEMessage.filesize;
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved+=filecontent.bytearray.size();
                this->bytestorecv-=filecontent.bytearray.size();
                QByteArray data;
                data.resize(sizeof(structemitFile));
                QBuffer buffer(&data);
                buffer.open(QIODevice::WriteOnly);
                QDataStream out(&buffer);
                structemitFile TextMessage;
                TextMessage.type=accessFile;
                TextMessage.success=true;
                out<<TextMessage.type<<TextMessage.success;
                buffer.close();
                this->tempP2P->waitForBytesWritten();
                this->tempP2P->write(data);
                this->tempP2P->flush();
            }
            else if(filecontent.ifend==false&&filecontent.iffirst==false){
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved+=filecontent.bytearray.size();
                this->bytestorecv-=filecontent.bytearray.size();
                QByteArray data;
                data.resize(sizeof(structemitFile));
                QBuffer buffer(&data);
                buffer.open(QIODevice::WriteOnly);
                QDataStream out(&buffer);
                structemitFile TextMessage;
                TextMessage.type=accessFile;
                TextMessage.success=true;
                out<<TextMessage.type<<TextMessage.success;
                buffer.close();
                this->tempP2P->waitForBytesWritten();
                this->tempP2P->write(data);
                this->tempP2P->flush();
            }
            else if(filecontent.ifend==true&&filecontent.iffirst==false){
                this->recvfile->write(filecontent.bytearray);
                this->bytesrecved=this->recvfilesize;
                this->bytestorecv=0;
                recvfile->close();
            }
            this->recvbar->ui->progressBar->setValue(qMin(100,int((double(this->bytesrecved)/double(this->recvfilesize))*100)));
            if(this->recvbar->ui->progressBar->value()==100){
                this->newmessage_bells->play();
                this->recvbar->ui->label_headtext->setText("接收完成！");
                int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
                int index_friend=FriendsInfo.userid.indexOf(LinkId);
                QString friend_headimg = FriendsInfo.url_headimg[index_friend];
                QString message=this->FILEMessage.filename;
                QString filetype=this->FILEMessage.filetype;
                QString filetype_icon = QDir::currentPath()+"/icon_file/"+filetype+".png";
                this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("He","Me",friend_headimg,message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),filetype_icon);

            }
}
}
void MainWindow::TwoSendFriendsMessages(){
    qDebug()<<"I am sending the 2message to my friend...";
    if(this->ui->TextMessage->toPlainText()==""){
        qDebug()<<"输出内容不能为空。";
    }
    else{
        QByteArray data;
        data.resize(sizeof(NomalMessage));
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        NomalMessage TextMessage;
        TextMessage.type=Msg;
        TextMessage.userid=user_id;
        TextMessage.message=this->ui->TextMessage->toPlainText();
        out<<TextMessage.type<<TextMessage.userid<<TextMessage.message;
        buffer.close();
        this->ui->TextMessage->clear();
        this->actP2P->waitForBytesWritten();
        this->actP2P->write(data);
        this->actP2P->flush();
        QString headimg_url=this->MyselfInfo.url_headimg;
        QStringList list = headimg_url.split(".");
        QString headimg = QDir::currentPath()+"/friends_headimg/"+this->MyselfInfo.userid+"."+list[1];
        int indexDesBubbleWidget = this->stackwidget.userid.indexOf(LinkId);
        this->ListBubbleWidgets[indexDesBubbleWidget]->appendMessage("Me","He",headimg,TextMessage.message,QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"),"");

    }

}
void MainWindow::mainwindow_get_userinfo(QString UserId,QString UserPassword,QHostAddress serverip){
    user_id = UserId;
    user_password=UserPassword;
    server_ip=serverip;
    this->connectServer();
}
void MainWindow::ItemDoubleClicked(QListWidgetItem *item){
//    connect(ui->Button_Send,SIGNAL(clicked()),this,SLOT(TwoSendFriendsMessages()));
    this->ui->TextMessage->clear();
    this->ui->Button_Send->close();
    this->ui->Button_Close->close();
    this->ui->frame_chatbar->close();
    this->ui->pushButton_sendfile->close();
    this->ui->TextMessage->show();
    this->ui->frame_chatbar->show();
    this->ui->Button_Send->show();
    this->ui->Button_Close->show();
    this->ui->pushButton_sendfile->show();
    this->ui->frame_tools->show();
    qDebug()<<this->ui->listWidget_friends->row(item);
    index_friend_item=this->ui->listWidget_friends->row(item);
    if(LinkInfo.userid.contains(Friends_Ids[this->ui->listWidget_friends->row(item)])){
        LinkId=Friends_Ids[this->ui->listWidget_friends->row(item)];
        int index=LinkInfo.userid.indexOf(Friends_Ids[this->ui->listWidget_friends->row(item)]);
        if(this->stackwidget.userid.contains(Friends_Ids[this->ui->listWidget_friends->row(item)])==true){
            if(this->indexBubbleWidget>=0){
                this->ListBubbleWidgets[this->indexBubbleWidget]->hide();
            }

            int stackindex=this->stackwidget.userid.indexOf(Friends_Ids[this->ui->listWidget_friends->row(item)]);
            this->indexBubbleWidget=stackindex;
            ListBubbleWidgets[stackindex]->show();
        }
        if(LinkInfo.linktype[index]=="1"){
            qDebug()<<"1双击切换的index:"<<index;
            disconnect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(TwoSendFriendsMessages()));
            connect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(SendFriendsMessages()));
            disconnect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(Twoselect_the_file()));
            connect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(select_the_file()));
            this->nowP2P = LinkInfo.ListTcpsocket[index];
//            disconnect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(TwoSendFriendsMessages()));
//            connect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(SendFriendsMessages()));
        }
        else{
            qDebug()<<"2双击切换的index:"<<index;
            disconnect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(SendFriendsMessages()));
            connect(this->ui->Button_Send,SIGNAL(clicked()),this,SLOT(TwoSendFriendsMessages()));
            disconnect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(select_the_file()));
            connect(this->ui->pushButton_sendfile,SIGNAL(clicked()),this,SLOT(Twoselect_the_file()));
            this->actP2P = LinkInfo.ListTcpsocket[index];
//            disconnect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(SendFriendsMessages()));
//            connect(this->ui->Button_Send,SIGNAL(returnPressed()),this,SLOT(TwoSendFriendsMessages()));
        }
    }
    else{
        QByteArray data;
        data.resize(sizeof(struct_Link_friend));
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        struct_Link_friend Linkfriend;
        Linkfriend.type=LinkFriend;
        Linkfriend.userid=Friends_Ids[this->ui->listWidget_friends->row(item)];
        qDebug()<<Linkfriend.userid;
        Linkfriend.ipaddress=QHostAddress("");
        Linkfriend.port=0;
        out<<Linkfriend.type<<Linkfriend.userid<<Linkfriend.port<<Linkfriend.ipaddress;
        buffer.close();
        this->SendMessages(data);
    }

}
void MainWindow::Close_Chatwindow(){
    this->ui->TextMessage->clear();
    this->ui->TextMessage->close();
    this->ui->Button_Send->close();
    this->ui->Button_Close->close();
    this->ui->frame_chatbar->close();
    this->ui->frame_tools->hide();
    this->ui->pushButton_sendfile->close();
    this->ListBubbleWidgets[this->indexBubbleWidget]->hide();
}
QString MainWindow::GetLocalIPAddress()
{
    QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        return ipAddress;
}
void MainWindow::Send_HeartBeat(){
    QByteArray data;
    data.resize(sizeof(struct_heartbeat));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    struct_heartbeat heartbeat;
    heartbeat.type=HeartBeat;
    heartbeat.userid=user_id;
    heartbeat.ipaddress=this->GetLocalIPAddress();
    heartbeat.port=this->tcpServer->serverPort();
    heartbeat.Message="I'm alive.";
    heartbeat.time=QTime::currentTime();
    out<<heartbeat.type<<heartbeat.userid<<heartbeat.ipaddress<<heartbeat.port<<heartbeat.Message<<heartbeat.time;
    buffer.close();
    this->tcpSocket->write(data);
    this->tcpSocket->flush();
    this->timer->start(40000);
}
void MainWindow::on_label_clicked(){
    Info_Card *UI_Info = new Info_Card(nullptr);
    UI_Info->ui->nameBig->setText(this->MyselfInfo.username);
    UI_Info->ui->name->setText(this->MyselfInfo.username);
    UI_Info->ui->account->setText(this->MyselfInfo.userid);
    UI_Info->ui->email->setText(this->MyselfInfo.useremail);
    qDebug()<<this->MyselfInfo.url_headimg;
    UI_Info->ui->listView->setStyleSheet("QListView{border-image:url("+this->MyselfInfo.url_headimg+")}");
    UI_Info->setWindowTitle(this->MyselfInfo.username);
    UI_Info->setWindowIcon(QIcon(this->MyselfInfo.url_headimg));
    UI_Info->show();
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu *RightClickMenu = new QMenu(this);
    QAction *Menu_info = new QAction("查看资料",this);
    QAction *Menu_dele = new QAction("删除好友",this);
    RightClickMenu->addAction(Menu_info);
    RightClickMenu->addSeparator();
    RightClickMenu->addAction(Menu_dele);
        RightClickMenu->setContextMenuPolicy(Qt::DefaultContextMenu);
        connect(Menu_info,SIGNAL(triggered()),this,SLOT(show_firend_card()));
        connect(Menu_dele,SIGNAL(triggered()),this,SLOT(dele_this_friend()));
//        if(ui->listWidget_friends->geometry().contains(this->mapFromGlobal(QCursor::pos()))){
            if((this->Friend_Card_Item=ui->listWidget_friends->itemAt(ui->listWidget_friends->mapFromGlobal(QCursor::pos())))!= NULL){
            this->Friend_Card_Index=ui->listWidget_friends->row(this->Friend_Card_Item);
                RightClickMenu->exec(QCursor::pos());
//            qDebug()<<"要查看的好友是"<<this->Friend_Card_Index;

            }


}
void MainWindow::show_firend_card(){
    Info_Card *UI_Info = new Info_Card(nullptr);
    UI_Info->ui->nameBig->setText(FriendsInfo.username[this->Friend_Card_Index]);
    UI_Info->ui->account->setText(FriendsInfo.userid[this->Friend_Card_Index]);
    UI_Info->ui->name->setText(FriendsInfo.username[this->Friend_Card_Index]);
    UI_Info->ui->email->setText(FriendsInfo.useremail[this->Friend_Card_Index]);
    UI_Info->ui->listView->setStyleSheet("QListView{border-image:url("+FriendsInfo.url_headimg[this->Friend_Card_Index]+")}");
    UI_Info->setWindowTitle(FriendsInfo.username[this->Friend_Card_Index]);
    UI_Info->setWindowIcon(QIcon(FriendsInfo.url_headimg[this->Friend_Card_Index]));
    UI_Info->show();
}
void MainWindow::dele_this_friend(){
    struct_handle_friend delete_friend;
    delete_friend.type=DeleteFriend;
    delete_friend.Myid=this->MyselfInfo.userid;
    delete_friend.Hisid=FriendsInfo.userid[this->Friend_Card_Index];
    delete_friend.ifsuccess=true;
    QByteArray data;
    data.resize(sizeof(struct_handle_friend));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<delete_friend.type<<delete_friend.Myid<<delete_friend.Hisid<<delete_friend.ifsuccess;
    buffer.close();
    this->SendMessages(data);
}
void MainWindow::add_one_friend(){
    Dialog *dialog_addfriend=new Dialog();
    this->dialog_addfriend=dialog_addfriend;
    this->dialog_addfriend->setWindowTitle("添加好友");
    this->dialog_addfriend->setWindowIcon(QIcon(":/image/KSSA_Icon.png"));
    this->dialog_addfriend->show();
    connect(this->dialog_addfriend->ui->findpushButton,SIGNAL(clicked()),this,SLOT(find_new_friend()));
}
void MainWindow::find_new_friend(){
    int select_type=this->dialog_addfriend->ui->typecomboBox->currentIndex();
    this->dialog_addfriend->ui->resultwidget->setVisible(true);
    this->dialog_addfriend->ui->Resultlabel->hide();
    if(this->dialog_addfriend->ui->findlineEdit->text()!=""){
        if(select_type==0){
            struct_handle_friend select_friend;
            select_friend.type=SelectFriend;
            select_friend.Myid=this->MyselfInfo.userid;
            select_friend.Hisid=this->dialog_addfriend->ui->findlineEdit->text();
            qDebug()<<"要搜索的id是"<<select_friend.Hisid;
            select_friend.ifsuccess=true;
            QByteArray data;
            data.resize(sizeof(struct_handle_friend));
            QBuffer buffer(&data);
            buffer.open(QIODevice::WriteOnly);
            QDataStream out(&buffer);
            out<<select_friend.type<<select_friend.Myid<<select_friend.Hisid<<select_friend.ifsuccess;
            buffer.close();
            this->SendMessages(data);
        }
    }
}
void MainWindow::add_this_friend(){
    struct_handle_friend add_friend;
    add_friend.type=AddFriend;
    add_friend.Myid=this->MyselfInfo.userid;
    add_friend.Hisid=newfriend_id;
    add_friend.ifsuccess=true;
    QByteArray data;
    data.resize(sizeof(struct_handle_friend));
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<add_friend.type<<add_friend.Myid<<add_friend.Hisid<<add_friend.ifsuccess;
    buffer.close();
    this->SendMessages(data);
}
void MainWindow::select_the_file(){
    this->filePath=QFileDialog::getOpenFileName(this,"open","../");
    if(!this->filePath.isEmpty()){
        QFileInfo info(this->filePath);
        FileMessage filemessage;
        filemessage.type=emitFile;
        filemessage.filename=info.fileName().right(info.fileName().size()-info.fileName().lastIndexOf('/')-1);;
        QStringList List=filemessage.filename.split(".");
        filemessage.filetype=List[1];
        filemessage.filesize=info.size();
        filemessage.userid=this->MyselfInfo.userid;
        //added
        this->sendfile = new QFile(this->filePath);
        this->sendfile->open(QIODevice::ReadOnly);
        //
        QByteArray data;
        data.resize(sizeof(FileMessage));
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        out<<filemessage.type<<filemessage.userid<<filemessage.filesize<<filemessage.filetype<<filemessage.filename;
        filemessage.totalsize+=data.size();
        filemessage.totalsize+=filemessage.filesize;
        this->sendfilesize=filemessage.filesize;
//        bytestosend=filemessage.filesize;
        qDebug()<<"总大小为"<<filemessage.totalsize;
//        qDebug()<<"需要发送的文件大小为"<<bytestosend;
        qDebug()<<"要发送的文件信息："<<filemessage.filename<<filemessage.filesize<<filemessage.filetype;
        out<<filemessage.totalsize;
        buffer.close();
        this->FILEMessage.filesize=filemessage.filesize;
        this->FILEMessage.filetype=filemessage.filetype;
        this->FILEMessage.filename=filemessage.filename;
        this->recvfilesize=filemessage.filesize;
        this->bytestosend=filemessage.filesize;
        this->bytessended=0;
//        filemessage.file->close();
            this->nowP2P->waitForBytesWritten();
            this->nowP2P->write(data);
            this->nowP2P->flush();
            this->sendbar = new progressbar();
            this->sendbar->setWindowIcon(QIcon(QIcon(":/image/KSSA_Icon.png")));
            this->sendbar->setWindowTitle("文件传输");
            this->sendbar->ui->progressBar->setOrientation(Qt::Horizontal);
            this->sendbar->ui->progressBar->setMinimum(0);
            this->sendbar->ui->progressBar->setMaximum(100);
            this->sendbar->ui->progressBar->setValue(0);
            this->sendbar->show();
    }
}
void MainWindow::Twoselect_the_file(){
    this->filePath=QFileDialog::getOpenFileName(this,"open","../");
    if(!this->filePath.isEmpty()){
        QFileInfo info(this->filePath);
        FileMessage filemessage;
        filemessage.type=emitFile;
        filemessage.filename=info.fileName().right(info.fileName().size()-info.fileName().lastIndexOf('/')-1);;
        QStringList List=filemessage.filename.split(".");
        filemessage.filetype=List[1];
        filemessage.filesize=info.size();
        filemessage.userid=this->MyselfInfo.userid;
        //added
        this->sendfile = new QFile(this->filePath);
        this->sendfile->open(QIODevice::ReadOnly);
        //
        QByteArray data;
        data.resize(sizeof(FileMessage));
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        out<<filemessage.type<<filemessage.userid<<filemessage.filesize<<filemessage.filetype<<filemessage.filename;
        filemessage.totalsize+=data.size();
        filemessage.totalsize+=filemessage.filesize;
        this->sendfilesize=filemessage.filesize;
//        bytestosend=filemessage.filesize;
        qDebug()<<"总大小为"<<filemessage.totalsize;
//        qDebug()<<"需要发送的文件大小为"<<bytestosend;
        qDebug()<<"要发送的文件信息："<<filemessage.filename<<filemessage.filesize<<filemessage.filetype;
        out<<filemessage.totalsize;
        buffer.close();
        this->FILEMessage.filesize=filemessage.filesize;
        this->FILEMessage.filetype=filemessage.filetype;
        this->FILEMessage.filename=filemessage.filename;
        this->recvfilesize=filemessage.filesize;
        this->bytestosend=filemessage.filesize;
        this->bytessended=0;
//        filemessage.file->close();
            this->actP2P->waitForBytesWritten();
            this->actP2P->write(data);
            this->actP2P->flush();
            this->sendbar = new progressbar();
            this->sendbar->setWindowIcon(QIcon(QIcon(":/image/KSSA_Icon.png")));
            this->sendbar->setWindowTitle("文件传输");
            this->sendbar->ui->progressBar->setOrientation(Qt::Horizontal);
            this->sendbar->ui->progressBar->setMinimum(0);
            this->sendbar->ui->progressBar->setMaximum(100);
            this->sendbar->ui->progressBar->setValue(0);
            this->sendbar->show();
    }
}
