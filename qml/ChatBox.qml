import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    color: "#e0e0e0"
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
                anchors.rightMargin: sentByMe ? 20 : undefined
                spacing: 6

                readonly property bool sentByMe: model.to !== "Me"

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined
                    layoutDirection: sentByMe ? Qt.RightToLeft : Qt.LeftToRight
                    Image {
                        id: avatar
                        width: 35
                        height: 35
                        fillMode: Image.PreserveAspectFit
                        source: "img/" + model.from + ".png"
                    }

                    Rectangle {
                        width: Math.min(
                                   messageText.implicitWidth + 24,
                                   0.6 * (listView_msg.width - avatar.width - messageRow.spacing))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"
                        radius: 10
                        Label {
                            id: messageText
                            text: content
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
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
    function append(from, to, content, time) {
        listView_msg.model.append({
                                      from: from,
                                      to: to,
                                      content: content,
                                      time: time
                                  })
        listView_msg.currentIndex = listView_msg.count - 1
    }
}
