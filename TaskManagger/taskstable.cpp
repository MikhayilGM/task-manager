#include "taskstable.h"

TasksTable::TasksTable(QWidget *parent, QString comm)
    : QMainWindow{parent}, command(comm)
{
    title = new QLabel("Title: ", this);
    title -> move(50, 50);
    title -> show();

    titleline = new QLineEdit(this);
    titleline -> move(150, 55);
    titleline -> resize(200, 20);
    titleline -> show();

    QObject::connect(titleline, &QLineEdit::editingFinished, this, &TasksTable::titleline_editing_finished);

    worker_name = new QLabel("Project Name: ", this);
    worker_name -> move(50, 90);
    worker_name -> show();

    worker_nameline = new QLineEdit(this);
    worker_nameline -> move(150, 95);
    worker_nameline -> resize(200, 20);
    worker_nameline -> show();

    QObject::connect(worker_nameline, &QLineEdit::editingFinished, this, &TasksTable::worker_nameline_editing_finished);

    project = new QLabel("Worker Name: ", this);
    project -> move(50, 130);
    project -> show();

    projectline = new QLineEdit(this);
    projectline -> move(150, 135);
    projectline -> resize(200, 20);
    projectline -> show();

    QObject::connect(projectline, &QLineEdit::editingFinished, this, &TasksTable::projectline_editing_finished);

    description = new QLabel("Description: ", this);
    description -> move(50, 170);
    description -> show();

    descriptionline = new QLineEdit(this);
    descriptionline -> move(150, 175);
    descriptionline -> resize(200, 100);
    descriptionline -> show();

    QObject::connect(descriptionline, &QLineEdit::editingFinished, this, &TasksTable::descriptionline_editing_finished);

    sumbitbutton = new QPushButton("Submit", this);
    sumbitbutton -> resize(100, 20);
    sumbitbutton -> move(250, 300);
    sumbitbutton -> show();

    QObject::connect(sumbitbutton, &QAbstractButton::clicked, this, &TasksTable::clicked_on_submit_button);
}

void TasksTable::titleline_editing_finished()
{
    if(titleline -> text() != "")
    {
        if(!(titleline -> text().front() >= 'A'  && titleline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered title must start with uppercase.", QMessageBox::Ok);
            titleline -> setText("");
            return;
        }

        for(int i = 1; i < titleline -> text().size(); ++i)
        {
            if(!(titleline -> text()[i] >= 'a' && titleline -> text()[i] <= 'z'))
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered title must contain only letters.", QMessageBox::Ok);
                titleline -> setText("");
                return;
            }
        }
    }
}

void TasksTable::worker_nameline_editing_finished()
{
    if(worker_nameline -> text() != "")
    {
        if(!(worker_nameline -> text().front() >= 'A'  && worker_nameline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must start with uppercase.", QMessageBox::Ok);
            worker_nameline -> setText("");
            return;
        }

        for(int i = 1; i < worker_nameline -> text().size(); ++i)
        {
            if(!(worker_nameline -> text()[i] >= 'a' && worker_nameline -> text()[i] <= 'z'))
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must contain only letters.", QMessageBox::Ok);
                worker_nameline -> setText("");
                return;
            }
        }
    }
}

void TasksTable::projectline_editing_finished()
{
    if(projectline -> text() != "")
    {
        if(!(projectline -> text().front() >= 'A'  && projectline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered Project name must start with uppercase.", QMessageBox::Ok);
            worker_nameline -> setText("");
            return;
        }

    }
}

void TasksTable::descriptionline_editing_finished()
{

}

void TasksTable::clicked_on_submit_button()
{
    std::vector<std::string> CommandLine;

    switch(CommandParse[command.toStdString()])
    {
        case Command::INSERTINTO:
        {
            if(titleline -> text() == "" )
            {
                titleline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your name line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(worker_nameline -> text() == "" )
            {
                worker_nameline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your surname line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(projectline -> text() == "" )
            {
                projectline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your age line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(descriptionline -> text() == "" )
            {
                descriptionline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your E-mail line is empty, please enter the information", QMessageBox::Ok);
                return;
            }


            CommandLine.push_back(command.toStdString());
            CommandLine.push_back("tasks");
            CommandLine.push_back("(");
            CommandLine.push_back("title,");
            CommandLine.push_back("worker_name,");
            CommandLine.push_back("project_name,");
            CommandLine.push_back("description");
            CommandLine.push_back(")");

            CommandLine.push_back("VALUES");
            CommandLine.push_back("(");
            CommandLine.push_back(titleline -> text().toStdString()+',');
            CommandLine.push_back(worker_nameline -> text().toStdString()+',');
            CommandLine.push_back(projectline -> text().toStdString()+',');
            CommandLine.push_back(descriptionline -> text().toStdString());
            CommandLine.push_back(")");

            insert_into(CommandLine);
            QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Added", "Data Succesfuly added.", QMessageBox::Ok);
            break;
        }
        case Command::SELECT:
        {
            CommandLine.push_back(command.toStdString());
            CommandLine.push_back("*");
            CommandLine.push_back("FROM");
            CommandLine.push_back("tasks");
            bool is_not_first = 0;
            if(titleline -> text() != "")
            {
                CommandLine.push_back("WHERE");
                CommandLine.push_back("title=" + titleline -> text().toStdString());
                is_not_first = 1;
            }

            if(worker_nameline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("worker_name=" + worker_nameline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("worker_name=" + worker_nameline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(projectline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("project_name=" + projectline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("project_name=" + projectline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(descriptionline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("description=" + descriptionline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("description=" + descriptionline -> text().toStdString());
                }
            }

            for(int i = 0; i < CommandLine.size(); ++i)
            {
                std::cout << CommandLine[i] << " ";
            }

            std::map<std::string, std::vector<std::string>> table = select(CommandLine);
            QTableWidget* tableWidget = new QTableWidget(table["title"].size(), 4);
            tableWidget -> setHorizontalHeaderLabels(QStringList() << "Title" << "Worker Name" << "Project Name" << "Description");
            for(int i = 0; i < tableWidget -> rowCount(); ++i)
            {
                QTableWidgetItem* tmp = new QTableWidgetItem();
                tmp -> setText(table["title"][i].c_str());
                tableWidget -> setItem(i, 0, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["worker_name"][i].c_str());
                tableWidget -> setItem(i, 1, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["project_name"][i].c_str());
                tableWidget -> setItem(i, 2, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["description"][i].c_str());
                tableWidget -> setItem(i, 3, tmp);
            }
            tableWidget -> show();
            break;
        }

        case Command::UPDATE:
        {
            static std::vector<std::string> CommandLine1;
            static bool where_is_entered = 0;
            if(!where_is_entered)
            {
                CommandLine1.push_back("WHERE");
                bool is_not_first = 0;
                if(titleline -> text() != "")
                {
                    CommandLine1.push_back("title=" + titleline -> text().toStdString());
                    is_not_first = 1;
                }

                if(worker_nameline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("worker_name=" + worker_nameline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("worker_name=" + worker_nameline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                if(projectline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("project_name=" + projectline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("project_name=" + projectline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                if(descriptionline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("description=" + descriptionline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("description=" + descriptionline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                titleline -> clear();
                worker_nameline -> clear();
                projectline -> clear();
                descriptionline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Not Entered", "Your Updating condition is Succesfully entered, please enter your Changable Data.", QMessageBox::Ok);
                where_is_entered = 1;
            }
            else
            {
                CommandLine.push_back(command.toStdString());
                CommandLine.push_back("tasks");
                CommandLine.push_back("SET");
                if(titleline -> text() != "")
                {
                    CommandLine.push_back("title=" + titleline -> text().toStdString());
                }

                if(worker_nameline -> text() != "")
                {
                        CommandLine.push_back("worker_name=" + worker_nameline -> text().toStdString());
                }

                if(projectline -> text() != "")
                {
                        CommandLine.push_back("project_name=" + projectline -> text().toStdString());
                }

                if(descriptionline -> text() != "")
                {
                        CommandLine.push_back("description=" + descriptionline -> text().toStdString());
                }

                CommandLine.insert(CommandLine.end(), CommandLine1.begin(), CommandLine1.end());
                CommandLine1.clear();
                where_is_entered = 0;
                for(int i = 0; i < CommandLine.size(); ++i)
                {
                    std::cout << CommandLine[i] << " ";
                }

                uppdate(CommandLine);
                QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Updated", "Data succesfully updated.", QMessageBox::Ok);
            }

            break;
        }
        case Command::DELETE:
        {
            CommandLine.push_back(command.toStdString());
            CommandLine.push_back("FROM");
            CommandLine.push_back("tasks");
            CommandLine.push_back("WHERE");
            bool is_not_first = 0;
            if(titleline -> text() != "")
            {
                CommandLine.push_back("title=" + titleline -> text().toStdString());
                is_not_first = 1;
            }

            if(worker_nameline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("worker_name=" + worker_nameline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("worker_name=" + worker_nameline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(projectline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("project_name=" + projectline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("project_name=" + projectline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(descriptionline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("description=" + descriptionline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("description=" + descriptionline -> text().toStdString());
                }
            }

            for(int i = 0; i < CommandLine.size(); ++i)
            {
                std::cout << CommandLine[i] << " ";
            }

            delete_data(CommandLine);
            QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Deleted", "Data succesfully deleted.", QMessageBox::Ok);
            break;
        }

        default:
            break;
    }
}
