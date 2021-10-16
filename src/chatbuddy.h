#ifndef CHATBUDDY_H
#define CHATBUDDY_H

#include <QWidget>

namespace Ui {
class ChatBuddy;
}

class ChatBuddy : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBuddy(QWidget *parent = nullptr);
    Ui::ChatBuddy *ui;
    ~ChatBuddy();

private:
};

#endif // CHATBUDDY_H
