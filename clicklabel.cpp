// clicklabel.c

#include "clicklabel.h"
void ClickedLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked(); // 在点击事件中发送信号
}
