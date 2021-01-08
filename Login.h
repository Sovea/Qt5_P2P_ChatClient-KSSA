#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
private slots:
    void on_clicked_register();
    int on_clicked_signin();
};

#endif // LOGIN_H
