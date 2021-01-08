#ifndef PERSONBUDDY_H
#define PERSONBUDDY_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
namespace Ui {
class PersonBuddy;
}

class PersonBuddy : public QWidget
{
    Q_OBJECT

public:
    explicit PersonBuddy(QWidget *parent = nullptr);
    Ui::PersonBuddy *ui;
    QLabel *headimg;
    QLabel *username;
    QLabel *usersign;
    QString headimgpath;
    void Buddy_init();
    ~PersonBuddy();

private:

};

#endif // PERSONBUDDY_H
