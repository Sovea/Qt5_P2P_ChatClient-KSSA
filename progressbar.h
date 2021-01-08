#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

namespace Ui {
class progressbar;
}

class progressbar : public QWidget
{
    Q_OBJECT

public:
    explicit progressbar(QWidget *parent = nullptr);
    Ui::progressbar *ui;
    ~progressbar();

private:

};

#endif // PROGRESSBAR_H
