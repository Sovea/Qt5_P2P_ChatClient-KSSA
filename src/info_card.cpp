#include "info_card.h"
#include "ui_info_card.h"

Info_Card::Info_Card(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info_Card)
{
    ui->setupUi(this);
}

Info_Card::~Info_Card()
{
    delete ui;
}
