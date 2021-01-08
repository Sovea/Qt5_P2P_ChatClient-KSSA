# Qt5_P2P_ChatClient-KSSA

一个使用Qt5以及C++开发的适用于局域网（Windows）的P2P聊天应用客户端。

#### 使用技术：

1.Qt5/C++开发

2.Qtcreator/Qtquick设计UI

3.Qml+Qss美化界面

4.自定义Qtsocket列表（数组容器）维护多方P2P连接

5.重写鼠标点击事件，实现好友列表右键小菜单

6.使用Qtquick为每个正在聊天的好友维护一个消息面板列表

7.利用MapSignal传递自定义参数给connect的SLOT函数，实现对应Socket的切换

#### 实现功能：

1.添加/删除好友

2.个人/好友名片（头像、昵称、简介）

3.发送心跳包给中间服务器维持状态

4.多分支P2P聊天

5.文件传输（确认机制）（可传送较大文件）

6.一对一聊天消息面板


#### 效果截图
![KSSA_Login](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_Login.png)

![KSSA_ChatExample](https://github.com/Sovea/Qt5_P2P_ChatClient-KSSA/blob/master/image/Screenshot/KSSA_ChatExample.png)
