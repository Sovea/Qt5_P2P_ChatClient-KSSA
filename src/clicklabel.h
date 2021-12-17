// clicklabel.h

#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QWidget>
#include <QLabel>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent) : QLabel(parent)
    {
    }
    ~ClickedLabel() {}
signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // CLICKEDLABEL_H
