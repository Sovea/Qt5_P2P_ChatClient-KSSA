#include "bubble-widget.h"
#include "ui_bubble-widget.h"
#include <QMetaObject>
#include <qmetaobject.h>
BubbleWidget::BubbleWidget(QWidget *parent) : QWidget(parent),
                                              ui(new Ui::BubbleWidget)
{
    ui->setupUi(this);
}

BubbleWidget::~BubbleWidget()
{
    delete ui;
}

void BubbleWidget::appendMessage(QString from, QString to, QString headimg, QString content, QString time, QString fileimg)
{
    QMetaObject::invokeMethod(
        ui->quickWidget->rootObject(),
        "append",
        Q_ARG(QVariant, QVariant(from)),
        Q_ARG(QVariant, QVariant(to)),
        Q_ARG(QVariant, QVariant(headimg)),
        Q_ARG(QVariant, QVariant(content)),
        Q_ARG(QVariant, QVariant(time)),
        Q_ARG(QVariant, QVariant(fileimg))
    );
}
