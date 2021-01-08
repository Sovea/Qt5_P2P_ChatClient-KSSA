#include "new_friend_buddy.h"
#include "ui_new_friend_buddy.h"

new_friend_buddy::new_friend_buddy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_friend_buddy)
{
    ui->setupUi(this);
}

new_friend_buddy::~new_friend_buddy()
{
    delete ui;
}
