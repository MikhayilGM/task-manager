#ifndef TASKSTABLE_H
#define TASKSTABLE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <SQL-CLONE.h>

class TasksTable : public QMainWindow
{
    Q_OBJECT
public:
    explicit TasksTable(QWidget *parent = nullptr, QString comm = "NONE");
    void clicked_on_submit_button();
    void titleline_editing_finished();
    void worker_nameline_editing_finished();
    void projectline_editing_finished();
    void descriptionline_editing_finished();

private:
    QString command;
    QLabel* title;
    QLineEdit* titleline;
    QLabel* worker_name;
    QLineEdit* worker_nameline;
    QLabel* project;
    QLineEdit* projectline;
    QLabel* description;
    QLineEdit* descriptionline;
    QPushButton* sumbitbutton;

signals:

};

#endif // TASKSTABLE_H
