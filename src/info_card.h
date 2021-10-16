#ifndef INFO_CARD_H
#define INFO_CARD_H

#include <QDialog>

namespace Ui {
class Info_Card;
}

class Info_Card : public QDialog
{
    Q_OBJECT

public:
    explicit Info_Card(QWidget *parent = nullptr);
    Ui::Info_Card *ui;
    ~Info_Card();

private:

};

#endif // INFO_CARD_H
