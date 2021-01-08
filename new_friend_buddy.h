#ifndef NEW_FRIEND_BUDDY_H
#define NEW_FRIEND_BUDDY_H

#include <QWidget>

namespace Ui {
class new_friend_buddy;
}

class new_friend_buddy : public QWidget
{
    Q_OBJECT

public:
    explicit new_friend_buddy(QWidget *parent = nullptr);
    Ui::new_friend_buddy *ui;
    ~new_friend_buddy();

private:

};

#endif // NEW_FRIEND_BUDDY_H
