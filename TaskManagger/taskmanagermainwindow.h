#ifndef TASKMANAGERMAINWINDOW_H
#define TASKMANAGERMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <commandwindow.h>

class TaskManagerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TaskManagerMainWindow(QWidget *parent = nullptr);
    ~TaskManagerMainWindow();
    void clicked_on_user_button();
    void clicked_on_tasks_button();
    void clicked_on_project_button();

private:
    QPushButton* user_button;
    QPushButton* tasks_button;
    QPushButton* project_button;
};
#endif // TASKMANAGERMAINWINDOW_H
