import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    color: "#FFFFFF"
    ScrollView {
        anchors.fill: parent
        id: scrollView

        ListView {
            id: listView_msg
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            spacing: 10
            keyNavigationWraps: true
            focus: true
            model: modelMsg.createObject(listView_msg)

            delegate: Column {
                id: column
                anchors.right: sentByMe ? parent.right : undefined
                anchors.left: sentByMe ? undfined : parent.left
                anchors.rightMargin: sentByMe ? 20 : undefined
                anchors.leftMargin: sentByMe ? undefined : 20
                spacing: 6

                readonly property bool sentByMe: model.to !== "Me"
                readonly property bool not_filetransfer: model.fileimg === ""
                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined
                    anchors.left: sentByMe ? undfined : parent.left
                    layoutDirection: sentByMe ? Qt.RightToLeft : Qt.LeftToRight
                    Image {
                        id: avatar
                        width: 50
                        height: 50
                        fillMode: Image.PreserveAspectFit
                        source: "file:///" + model.headimg
                    }

                    Rectangle {
                        width: not_filetransfer ? Math.min(messageText.implicitWidth + 24,0.6 * (listView_msg.width - avatar.width - messageRow.spacing)) : Math.max(Math.min(messageText.implicitWidth + 24,0.6 * (listView_msg.width - avatar.width - messageRow.spacing)),transfericon.width)
                        height: not_filetransfer? messageText.implicitHeight + 24 :Math.max(messageText.implicitHeight + 24,transfericon.height)
                        color: sentByMe ? "lightgrey" : "steelblue"
                        radius: 10
                        Image {
                            id: transfericon
//                            anchors.centerIn:parent
                            anchors.right: sentByMe ? messageText.left : undefined
                            anchors.left: sentByMe ? undefined : messageText.right
                            width: 50
                            height: 50
                            anchors.rightMargin: sentByMe ? 20 : 0
                            anchors.leftMargin: sentByMe ? 0 : 20
                            fillMode: Image.PreserveAspectFit
                            source: "file:///"+model.fileimg
                        }
                        Label {
                            id: messageText
                            text: content
                            color: sentByMe ? "black" : "white"
//                            anchors.fill: parent
                            anchors.centerIn:parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }

                    }
                }

                Label {
                    id: timestampText
                    text: time
                    //                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                    anchors.left: sentByMe ? undfined : parent.left
                }
            }

            Component {
                id: modelMsg
                ListModel {
                    id: listmode

                }
            }
        }
    }
    function append(from, to,headimg,content,time,fileimg){
        listView_msg.model.append({
                                      from: from,
                                      to: to,
                                      headimg: headimg,
                                      content: content,
                                      time: time,
                                      fileimg:fileimg
                                  })
        listView_msg.currentIndex = listView_msg.count - 1
    }
}
