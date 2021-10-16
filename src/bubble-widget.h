#ifndef BUBBLEWIDGET_H
#define BUBBLEWIDGET_H

#include <QWidget>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWidget>
#include <QDateTime>

namespace Ui {
class BubbleWidget;
}

class BubbleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BubbleWidget(QWidget *parent = 0);
     Ui::BubbleWidget *ui;
    ~BubbleWidget();

    void appendMessage(QString from, QString to,QString headimg, QString content, QString time,QString fileimg);

private slots:
//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

private:

};

#endif // BUBBLEWIDGET_H
