#ifndef PROJECTTABLES_H
#define PROJECTTABLES_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <SQL-CLONE.h>

class ProjectTables : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProjectTables(QWidget *parent = nullptr, QString comm = "NONE");
    void clicked_on_submit_button();
    void titleline_editing_finished();
    void descriptionline_editing_finished();

private:
    QString command;
    QLabel* title;
    QLineEdit* titleline;
    QLabel* created_at;
    QDateEdit* dateline;
    QLabel* description;
    QLineEdit* descriptionline;
    QPushButton* sumbitbutton;

signals:

};

#endif // PROJECTTABLES_H
