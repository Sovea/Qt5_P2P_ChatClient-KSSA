#include "chatbuddy.h"
#include "ui_chatbuddy.h"

ChatBuddy::ChatBuddy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBuddy)
{
    ui->setupUi(this);
}

ChatBuddy::~ChatBuddy()
{
    delete ui;
}
