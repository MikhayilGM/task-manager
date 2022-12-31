#include "commandwindow.h"

CommandWindow::CommandWindow(QWidget *parent)
    : QMainWindow{parent}
{

}

CommandWindow::CommandWindow(QString tb_name, QWidget *parent)
    : QMainWindow{parent}, table_name(tb_name)
{
    add_button = new QPushButton("Add", this);
    add_button -> resize({100, 20});
    add_button -> move(150, 130);
    add_button -> show();

    QObject::connect(add_button, &QAbstractButton::clicked, this, &CommandWindow::clicked_on_add_button);

    show_button = new QPushButton("Show", this);
    show_button -> resize({100, 20});
    show_button -> move(150, 170);
    show_button -> show();

    QObject::connect(show_button, &QAbstractButton::clicked, this, &CommandWindow::clicked_on_show_button);

    delete_button = new QPushButton("Delete", this);
    delete_button -> resize({100, 20});
    delete_button -> move(150, 210);
    delete_button -> show();

    QObject::connect(delete_button, &QAbstractButton::clicked, this, &CommandWindow::clicked_on_delete_button);

    update_button = new QPushButton("Update", this);
    update_button -> resize({100, 20});
    update_button -> move(150, 250);
    update_button -> show();

    QObject::connect(update_button, &QAbstractButton::clicked, this, &CommandWindow::clicked_on_update_button);

    ParseTables["user"] = TABLES::USER;
    ParseTables["tasks"] = TABLES::TASKS;
    ParseTables["project"] = TABLES::PROJECT;
}

void CommandWindow::clicked_on_add_button()
{
    switch(ParseTables[table_name])
    {
        case TABLES::USER:
        {
            UsersTable* user_table = new UsersTable(this, "INSERT_INTO");
            user_table -> resize(400, 300);
            user_table -> show();
            break;
        }

        case TABLES::TASKS:
        {
            TasksTable* task_table = new TasksTable(this, "INSERT_INTO");
            task_table -> resize(400, 350);
            task_table -> show();
            break;
        }

        case TABLES::PROJECT:
        {
            ProjectTables* project_table = new ProjectTables(this, "INSERT_INTO");
            project_table -> resize(400, 300);
            project_table -> show();
            break;
        }

        default:
        break;
    }
}

void CommandWindow::clicked_on_show_button()
{
    switch(ParseTables[table_name])
    {
        case TABLES::USER:
        {
            UsersTable* user_table = new UsersTable(this, "SELECT");
            user_table -> resize(400, 300);
            user_table -> show();
            break;
        }

        case TABLES::TASKS:
        {
            TasksTable* task_table = new TasksTable(this, "SELECT");
            task_table -> resize(400, 350);
            task_table -> show();
            break;
        }

        case TABLES::PROJECT:
        {
            ProjectTables* project_table = new ProjectTables(this, "SELECT");
            project_table -> resize(400, 300);
            project_table -> show();
            break;
        }

        default:
        break;
    }
}

void CommandWindow::clicked_on_delete_button()
{
    switch(ParseTables[table_name])
    {
        case TABLES::USER:
        {
            UsersTable* user_table = new UsersTable(this, "DELETE");
            user_table -> resize(400, 300);
            user_table -> show();
            break;
        }

        case TABLES::TASKS:
        {
            TasksTable* task_table = new TasksTable(this, "DELETE");
            task_table -> resize(400, 350);
            task_table -> show();
            break;
        }

        case TABLES::PROJECT:
        {
            ProjectTables* project_table = new ProjectTables(this, "DELETE");
            project_table -> resize(400, 300);
            project_table -> show();
            break;
        }

        default:
        break;
    }
}

void CommandWindow::clicked_on_update_button()
{
    switch(ParseTables[table_name])
    {
        case TABLES::USER:
        {
            UsersTable* user_table = new UsersTable(this, "UPDATE");
            user_table -> resize(400, 300);
            user_table -> show();
            break;
        }

        case TABLES::TASKS:
        {
            TasksTable* task_table = new TasksTable(this, "UPDATE");
            task_table -> resize(400, 350);
            task_table -> show();
            break;
        }

        case TABLES::PROJECT:
        {
            ProjectTables* project_table = new ProjectTables(this, "UPDATE");
            project_table -> resize(400, 300);
            project_table -> show();
            break;
        }

        default:
        break;
    }
}
