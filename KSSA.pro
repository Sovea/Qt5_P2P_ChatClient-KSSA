QT       += core gui network sql multimedia quickwidgets \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = KSSA.ico
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Login.cpp \
    src/bubble-widget.cpp \
    src/chatbuddy.cpp \
    src/clicklabel.cpp \
    src/dialog.cpp \
    src/info_card.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/new_friend_buddy.cpp \
    src/personbuddy.cpp \
    src/progressbar.cpp

HEADERS += \
    src/Login.h \
    src/bubble-widget.h \
    src/chatbuddy.h \
    src/clicklabel.h \
    src/dialog.h \
    src/info_card.h \
    src/mainwindow.h \
    src/new_friend_buddy.h \
    src/personbuddy.h \
    src/progressbar.h

FORMS += \
    src/Login.ui \
    src/bubble-widget.ui \
    src/chatbuddy.ui \
    src/dialog.ui \
    src/info_card.ui \
    src/mainwindow.ui \
    src/new_friend_buddy.ui \
    src/personbuddy.ui \
    src/progressbar.ui

TRANSLATIONS += \
    KSSA_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/qml/ChatBox.qml \
    src/qml/ChatBuddy.qml \
    src/qml/ChatBuddyForm.ui.qml \
    src/icon_file/7z.png \
    src/icon_file/c.png \
    src/icon_file/cpp.png \
    src/icon_file/doc.png \
    src/icon_file/docx.png \
    src/icon_file/exe.png \
    src/icon_file/jpg.png \
    src/icon_file/mkv.png \
    src/icon_file/mp3.png \
    src/icon_file/mp4.png \
    src/icon_file/pdf.png \
    src/icon_file/png.png \
    src/icon_file/py.png \
    src/icon_file/sql.png \
    src/icon_file/txt.png \
    src/icon_file/zip.png \
    src/image/KSSAA.png \
    src/image/KSSA_Back.png \
    src/image/KSSA_Icon.png \
    src/image/KSSA_Login_Title.png \
    src/image/back_progressbar.jpg \
    src/image/cube.jpg \
    src/image/cubee.jpg \
    src/image/addfriend-back.jpg \
    src/image/icon_file.png \
    src/image/main-back.jpg \
    src/qss/mainwindow.qss \
    src/sound/newmessage.mp3 \
    src/sound/newmessage.wav

RESOURCES += \
    Resources.qrc
