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
    Login.cpp \
    bubble-widget.cpp \
    chatbuddy.cpp \
    clicklabel.cpp \
    dialog.cpp \
    info_card.cpp \
    main.cpp \
    mainwindow.cpp \
    new_friend_buddy.cpp \
    personbuddy.cpp \
    progressbar.cpp

HEADERS += \
    Login.h \
    bubble-widget.h \
    chatbuddy.h \
    clicklabel.h \
    dialog.h \
    info_card.h \
    mainwindow.h \
    new_friend_buddy.h \
    personbuddy.h \
    progressbar.h

FORMS += \
    Login.ui \
    bubble-widget.ui \
    chatbuddy.ui \
    dialog.ui \
    info_card.ui \
    mainwindow.ui \
    new_friend_buddy.ui \
    personbuddy.ui \
    progressbar.ui

TRANSLATIONS += \
    KSSA_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ChatBox.qml \
    ChatBuddy.qml \
    ChatBuddyForm.ui.qml \
    icon_file/7z.png \
    icon_file/c.png \
    icon_file/cpp.png \
    icon_file/doc.png \
    icon_file/docx.png \
    icon_file/exe.png \
    icon_file/jpg.png \
    icon_file/mkv.png \
    icon_file/mp3.png \
    icon_file/mp4.png \
    icon_file/pdf.png \
    icon_file/png.png \
    icon_file/py.png \
    icon_file/sql.png \
    icon_file/txt.png \
    icon_file/zip.png \
    image/KSSAA.png \
    image/KSSA_Back.png \
    image/KSSA_Icon.png \
    image/KSSA_Login_Title.png \
    image/back_progressbar.jpg \
    image/cube.jpg \
    image/cubee.jpg \
    image/head_pic/head_pic1.jpg \
    image/head_pic/head_pic2.jpg \
    image/head_pic/head_pic3.jpg \
    image/head_pic/head_pic4.jpg \
    image/head_pic/head_pic5.jpg \
    image/icon_file.png \
    image/main_back.jpg \
    image/main_back2.jpg \
    image/pic/32764888973_8c8a7ac1b7_o.jpg \
    image/pic/alex-simpson-sCq3bz253xs-unsplash.jpg \
    image/pic/alex-simpson-vFb4K-KZ5a8-unsplash.jpg \
    image/pic/anja-junghans-8SdYMct3zI4-unsplash.jpg \
    image/pic/anton-darius-xYIuqpHD2oQ-unsplash.jpg \
    image/pic/arto-marttinen-pQS0ETF3KTI-unsplash.jpg \
    image/pic/brett-jackson-a81-5nFX-_Y-unsplash.jpg \
    image/pic/cameron-venti-bS5OwMjMc1I-unsplash.jpg \
    image/pic/carles-rabada-IMNKkZfzsSI-unsplash.jpg \
    image/pic/daniele-franchi-dt0yhDQmJ4k-unsplash.jpg \
    image/pic/diego-ph-VmRxRz0gD_s-unsplash.jpg \
    image/pic/hannah-rodrigo-mf_3yZnC6ug-unsplash.jpg \
    image/pic/igor-sergeyev-2N0Ol4TgNQU-unsplash.jpg \
    image/pic/james-penhey-KkHNZ2JTDgQ-unsplash.jpg \
    image/pic/jerry-wang-ARgNgdFXAS4-unsplash.jpg \
    image/pic/jerry-wang-mnFKp-h1GUo-unsplash.jpg \
    image/pic/patrick-hendry-6xTCch1CbcE-unsplash.jpg \
    image/pic/quino-al-JFeOy62yjXk-unsplash.jpg \
    image/pic/samsommer-J3ABLQjZQBg-unsplash.jpg \
    image/sparrowoo.jpg \
    qml/ChatBox.qml \
    qss/mainwindow.qss \
    sound/newmessage.mp3 \
    sound/newmessage.wav

RESOURCES += \
    Resources.qrc
