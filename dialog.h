#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    Ui::Dialog *ui;
    ~Dialog();
    QString string;
    bool flag1;
    bool flag2;

signals:

private:


private slots:
    void on_findlineEdit_textChanged(const QString &arg1);
//    void on_findpushButton_clicked();
//    void on_typecomboBox_currentTextChanged(const QString &arg1);
//    void on_onlineradioButton_clicked(bool checked);
//    void on_gobackButton_clicked();
//    void on_firstAddButton_clicked();
//    void on_secondAddButton_clicked();
//    void on_thirdAddButton_clicked();
};
#endif // DIALOG_H
