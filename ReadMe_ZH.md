# Qt5_P2P_ChatClient-KSSA

一个使用Qt5以及C++开发的适用于局域网（Windows）的P2P聊天应用客户端。

### 使用技术：

1.Qt5/C++开发

2.Qtcreator/Qtquick设计UI

3.Qml+Qss美化界面

4.自定义Qtsocket列表（数组容器）维护多方P2P连接

5.重写鼠标点击事件，实现好友列表右键小菜单

6.使用Qtquick为每个正在聊天的好友维护一个消息面板列表

7.利用MapSignal传递自定义参数给connect的SLOT函数，实现对应Socket的切换

### 实现功能：

1.添加/删除好友

2.个人/好友名片（头像、昵称、简介）

3.发送心跳包给中间服务器维持状态

4.多分支P2P聊天

5.文件传输（确认机制）（可传送较大文件）

6.一对一聊天消息面板

### 项目重点介绍

##### 1.QVector <QTcpSocket*> ListTcpsocket维持套接字列表

##### 2.QSignalMapper做绑定事件的映射（解决SLOT无法传参的问题）

```c++
ServerMapper->setMapping(LinkInfo.ListTcpsocket.last(),LinkInfo.ListTcpsocket.count());
    connect(LinkInfo.ListTcpsocket.last(), SIGNAL(readyRead()), ServerMapper, SLOT(map()));
    connect(ServerMapper, SIGNAL(mapped(int)), this, SLOT(changeTempTcpsocket(int)));
```

##### 3.QBuffer统一数据发送方式，便于读写：

```c++
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
```

```c++
QByteArray data = this->tcpSocket->readAll();
    QBuffer buf(&data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
```

##### 4.客户端套接字解释：tcpSocket连接服务器；tempP2P负责转为活动套接字，后台默默接收数据；nowP2P接收P2P请求；actP2P发送P2P请求

##### 5.发送接收文件流程：emitFile类型消息发送接收文件详细信息，对方创建文件并打开进度条面板；File类型消息发送接收文件内容，更新进度条；accessFile返回接收确认消息，表示本组数据接收完成，等待下一组。

### 效果截图
![KSSA_Login](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_Login.png)

![KSSA_ChatExample](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_ChatExample.png)

