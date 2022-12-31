#include "taskmanagermainwindow.h"

TaskManagerMainWindow::TaskManagerMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::fstream file;

    file.open("task_manager.data");
    if(!file.is_open())
    {
        complete_command("CREATE DATABASE task_manager;");
    }
    else
    {
        complete_command("OPEN DATABASE task_manager;");
    }
    file.close();

    file.open("user.tb");
    if(!file.is_open())
    {
        complete_command("CREATE TABLE user ( VARCHAR name, VARCHAR surname, INT age, VARCHAR e_mail, VARCHAR phone_number )");
    }
    file.close();

    file.open("tasks.tb");
    if(!file.is_open())
    {
        complete_command("CREATE TABLE tasks ( VARCHAR title, VARCHAR worker_name, VARCHAR project_name, VARCHAR description )");
    }
    file.close();

    file.open("project.tb");
    if(!file.is_open())
    {
        complete_command("CREATE TABLE project ( VARCHAR project_title, DATE created_at, VARCHAR project_descrip )");
    }
    file.close();

    user_button = new QPushButton("User", this);
    user_button -> resize({100, 20});
    user_button -> move(250, 200);
    user_button -> show();

    QObject::connect(user_button, &QAbstractButton::clicked, this, &TaskManagerMainWindow::clicked_on_user_button);

    tasks_button = new QPushButton("Tasks", this);
    tasks_button -> resize({100, 20});
    tasks_button -> move(250, 240);
    tasks_button -> show();

    QObject::connect(tasks_button, &QAbstractButton::clicked, this, &TaskManagerMainWindow::clicked_on_tasks_button);

    project_button = new QPushButton("Projects", this);
    project_button -> resize({100, 20});
    project_button -> move(250, 280);
    project_button -> show();

    QObject::connect(project_button, &QAbstractButton::clicked, this, &TaskManagerMainWindow::clicked_on_project_button);
}

TaskManagerMainWindow::~TaskManagerMainWindow()
{
}

void TaskManagerMainWindow::clicked_on_user_button()
{
    CommandWindow* user_window;
    user_window = new CommandWindow( QString("user"), this);
    user_window -> resize(QSize(400, 400));
    user_window -> show();
}

void TaskManagerMainWindow::clicked_on_tasks_button()
{
    CommandWindow* user_window;
    user_window = new CommandWindow( QString("tasks"), this);
    user_window -> resize(QSize(400, 400));
    user_window -> show();
}


void TaskManagerMainWindow::clicked_on_project_button()
{
    CommandWindow* user_window;
    user_window = new CommandWindow( QString("project"), this);
    user_window -> resize(QSize(400, 400));
    user_window -> show();
}
