// clicklabel.c

#include "clicklabel.h"
void ClickedLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
