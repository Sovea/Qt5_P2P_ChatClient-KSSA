# Qt5_P2P_ChatClient-KSSA
**[中文介绍](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/ReadMe_ZH.md)**

A P2P chat application client for local area network (Windows) developed using Qt5 and C++.

### Use technology:

1. Qt5/C++ development

2. Qtcreator/Qtquick design UI

3.Qml+Qss beautify the interface

4. Customize Qtsocket list (array container) to maintain multi-party P2P connection

5. Rewrite the mouse click event to realize the small right-click menu of the friend list

6. Use Qtquick to maintain a message panel list for each friend who is chatting

7. Use MapSignal to pass custom parameters to the SLOT function of connect to switch the corresponding Socket

### Realization function:

1. Add/remove friends

2. Personal/friend business card (avatar, nickname, profile)

3. Send a heartbeat packet to the intermediate server to maintain the state

4. Multi-branch P2P chat

5. File transfer (confirmation mechanism) (larger files can be transferred)

6. One-to-one chat message panel

### Project highlights

##### 1.QVector <QTcpSocket*> ListTcpsocket maintains a list of sockets
##### 2. QSignalMapper does the mapping of binding events (solves the problem that SLOT cannot pass parameters)
##### 3. QBuffer unified data transmission method, easy to read and write:

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

##### 4. Client socket explanation: tcpSocket is used to connect to the server; tempP2P is a socket that dynamically receives background messages; nowP2P sockets handle requests from friends; actP2P actively sends requests
##### 5. The process of sending and receiving files: the emitFile type message sends and receives the detailed information of the file. After the other party receives it, it creates the corresponding file and opens the progress bar panel; File type messages are used to send or receive file content and update the progress bar; accessFile type messages Responsible for sending or receiving confirmation, indicating that the reception of this group of data is complete and waiting for the next group of data.

### ScreenShots
![KSSA_Login](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_Login.png)

![KSSA_ChatExample](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_ChatExample.png)
