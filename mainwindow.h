#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clicklabel.h"
#include "info_card.h"
#include "dialog.h"
#include "bubble-widget.h"
#include "ui_bubble-widget.h"
#include "progressbar.h"
#include "ui_progressbar.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTime>
#include <QMenu>
#include <QVector>
#include <QtMultimedia/QSound>
#include <QSignalMapper>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum MsgType{Msg,UsrLogin,UsrLeft,Userinfo,Friendsinfo,HeartBeat,LinkFriend,File,Refuse,DeleteFriend,AddFriend,SelectFriend,HelloToMyfriend,emitFile,accessFile};     //消息类型
    typedef struct {
        MsgType type;
        QString userid;
        QString password;
        QString Message;
        bool success;
    }LoginMessage;
    typedef struct {
        MsgType type;
        QString userid;
        QString message;
    }NomalMessage;
    typedef struct{
        MsgType type;
        QString userid;
        QString filename;
        qint64 filesize;
        QString filetype;
        qint64 totalsize;
        QFile *file;
    }FileMessage;
    typedef struct{
        MsgType type;
        QByteArray bytearray;
        bool iffirst;
        bool ifend;
    }structFilecontent;
    typedef struct{
        MsgType type;
        bool success;
    }structemitFile;
    typedef struct{
        MsgType type;
        QString username;
        QString userid;
        QString useremail;
        QString url_headimg;
//        bool success;
    }struct_Userinfo;
    typedef struct{
        MsgType type;
        int count;
        QString clientid;
        QString message;
        QStringList userid;
        QStringList username;
        QStringList useremail;
        QStringList url_headimg;
//        bool success;
    }struct_Friendsinfo;
    typedef struct{
        MsgType type;
        QString userid;
        QString ipaddress;
        int port;
        QString Message;
        QTime time;
    }struct_heartbeat;
    typedef struct{
        MsgType type;
        QString userid;
        int port;
        QHostAddress ipaddress;
        bool online;
    }struct_Link_friend;
    typedef struct{
        MsgType type;
        QString Myid;
        QString Hisid;
        bool ifsuccess;
    }struct_handle_friend;
    typedef struct{
        MsgType type;
        QString userid;
        QString username;
        QString Message;
    }struct_HelloMyfriend;
    typedef struct{
        int count;
        QStringList userid;
        QStringList username;
        QStringList linktype;
        QVector <QTcpSocket*> ListTcpsocket;
    }struct_link_info;
    typedef struct{
        int count;
        QStringList userid;
    }struct_stackwidget;
    typedef struct{
        int count;
        QStringList userid;
        QStringList ipaddress;
        QStringList port;
        QStringList time;
        QStringList subtime;
        QVector <QTcpSocket*> ListTcpsocket;
    }struct_alive_users;

    void mainwindow_get_userinfo(QString UserId,QString UserPassword,QHostAddress serverip);
public slots:

signals:

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
    QTcpSocket *nowP2P;
    QTcpSocket *tempP2P;
    QTcpSocket *actP2P;
//    struct_alive_users Alive_server_users;
//    struct_alive_users Alive_client_users;
    ClickedLabel * clickLabel;
    struct_Userinfo MyselfInfo;
    struct_Friendsinfo FriendsInfo;
    struct_link_info LinkInfo;
    QMenu *RightClickMenu;
    QListWidgetItem* Friend_Card_Item;
    int Friend_Card_Index;
    Dialog *dialog_addfriend;
    QSound *newmessage_bells;
//    progressbar *newprogline;
    struct_stackwidget stackwidget;
    int indexBubbleWidget;
    int countBubbleWidget;
    QVector <BubbleWidget*> ListBubbleWidgets;
    QString filePath;
    FileMessage FILEMessage;
    qint64 bytestorecv;
    qint64 bytesrecved;
    qint64 bytestosend;
    qint64 bytessended;
    QFile *recvfile;
    QFile *sendfile;
    progressbar *sendbar;
    progressbar *recvbar;
    qint64 sendfilesize;
    qint64 recvfilesize;
    QSignalMapper * ServerMapper;
    QSignalMapper * ClientMapper;
    void SendMessages(QByteArray data);
    QString GetLocalIPAddress();
    void StartServer();
    void structinit();
//    void clearMSG();
private slots:
    void ReadMessages();
    void ReadFriendsMessages();
    void TwoReadFriendsMessages();
    void connectServer();
    void SendFriendsMessages();
    void TwoSendFriendsMessages();
    void Send_login_Messages();
    void ItemDoubleClicked(QListWidgetItem *item);
    void contextMenuEvent(QContextMenuEvent *event);
    void Close_Chatwindow();
    void Send_HeartBeat();
    void LinktoFriends(int port,QHostAddress address);
    void on_label_clicked();
    void show_firend_card();
    void dele_this_friend();
    void add_one_friend();
    void find_new_friend();
    void add_this_friend();
    void Send_Hello_Messages();
    void TwoSend_Hello_Messages();
    void newConnect();
    void select_the_file();
    void Twoselect_the_file();
    void changeServerTcpsocket(int index);
    void changeClientTcpsocket(int index);
    void changeTempTcpsocket(int index);
    void TwochangeTempTcpsocket(int index);
//    void recv_the_file();
//    void Tworecv_the_file();
};
#endif // MAINWINDOW_H

