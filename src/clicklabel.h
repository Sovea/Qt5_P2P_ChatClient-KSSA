// clicklabel.h

#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QWidget>
#include <QLabel>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent):QLabel(parent){

    }
    ~ClickedLabel() {}
signals:
    void clicked(); // 点击信号
protected:
    void mousePressEvent(QMouseEvent*); // 重载了鼠标释放事件

};

#endif // CLICKEDLABEL_H
