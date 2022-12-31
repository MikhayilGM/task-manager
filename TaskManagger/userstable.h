#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <SQL-CLONE.h>
#include <QMessageBox>
#include <QTableWidget>>

class UsersTable : public QMainWindow
{
    Q_OBJECT
public:
    explicit UsersTable(QWidget *parent = nullptr, QString comm = "NONE");
    void clicked_on_submit_button();
    void nameline_editing_finished();
    void surnameline_editing_finished();
    void ageline_editing_finished();
    void emailline_editing_finished();
    void phone_numberline_editing_finished();

private:
    QString command;
    QLabel* name;
    QLineEdit* nameline;
    QLabel* surname;
    QLineEdit* surnameline;
    QLabel* age;
    QLineEdit* ageline;
    QLabel* email;
    QLineEdit* emailline;
    QLabel* phone_number;
    QLineEdit* phone_numberline;
    QPushButton* sumbitbutton;

signals:

};

#endif // USERSTABLE_H
