#include "projecttables.h"

ProjectTables::ProjectTables(QWidget *parent, QString comm)
    : QMainWindow{parent}, command(comm)
{
    title = new QLabel("Title: ", this);
    title -> move(50, 50);
    title -> show();

    titleline = new QLineEdit(this);
    titleline -> move(150, 55);
    titleline -> resize(200, 20);
    titleline -> show();

    QObject::connect(titleline, &QLineEdit::editingFinished, this, &ProjectTables::titleline_editing_finished);

    created_at = new QLabel("Date: ", this);
    created_at -> move(50, 90);
    created_at -> show();

    dateline = new QDateEdit(this);
    dateline -> move(150, 95);
    dateline -> resize(200, 20);
    dateline -> setDate({1900, 1, 1});
    dateline -> show();

    description = new QLabel("Description: ", this);
    description -> move(50, 170);
    description -> show();

    descriptionline = new QLineEdit(this);
    descriptionline -> move(150, 135);
    descriptionline -> resize(200, 100);
    descriptionline -> show();

    QObject::connect(descriptionline, &QLineEdit::editingFinished, this, &ProjectTables::descriptionline_editing_finished);

    sumbitbutton = new QPushButton("Submit", this);
    sumbitbutton -> move(250, 250);
    sumbitbutton -> resize(100, 20);
    sumbitbutton -> show();

    QObject::connect(sumbitbutton, &QAbstractButton::clicked, this, &ProjectTables::clicked_on_submit_button);
}

void ProjectTables::titleline_editing_finished()
{
    if(titleline -> text() != "")
    {
        if(!(titleline -> text().front() >= 'A'  && titleline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered Project name must start with uppercase.", QMessageBox::Ok);
            titleline -> setText("");
            return;
        }

    }
}

void ProjectTables::descriptionline_editing_finished()
{

}

void ProjectTables::clicked_on_submit_button()
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

            if(dateline -> date().toString("dd-MM-yyyy") == "" )
            {
                dateline -> setDate({1, 1, 1});
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your surname line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(descriptionline -> text() == "" )
            {
                descriptionline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your age line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            CommandLine.push_back(command.toStdString());
            CommandLine.push_back("project");
            CommandLine.push_back("(");
            CommandLine.push_back("project_title,");
            CommandLine.push_back("created_at,");
            CommandLine.push_back("project_descrip");
            CommandLine.push_back(")");

            CommandLine.push_back("VALUES");
            CommandLine.push_back("(");
            CommandLine.push_back(titleline -> text().toStdString()+',');
            CommandLine.push_back(dateline -> date().toString("dd-MM-yyyy").toStdString()+',');
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
            CommandLine.push_back("project");
            bool is_not_first = 0;
            if(titleline -> text() != "")
            {
                CommandLine.push_back("WHERE");
                CommandLine.push_back("project_title=" + titleline -> text().toStdString());
                is_not_first = 1;
            }

            if(dateline -> date().toString("dd-MM-yyyy") != "01-01-1900")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                    is_not_first = 1;
                }
            }


            if(descriptionline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("project_descrip=" + descriptionline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("project_descrip=" + descriptionline -> text().toStdString());
                }
            }

            for(int i = 0; i < CommandLine.size(); ++i)
            {
                std::cout << CommandLine[i] << " ";
            }

            std::map<std::string, std::vector<std::string>> table = select(CommandLine);
            QTableWidget* tableWidget = new QTableWidget(table["project_title"].size(), 3);
            tableWidget -> setHorizontalHeaderLabels(QStringList() << "Title" << "Create at" << "Description");
            for(int i = 0; i < tableWidget -> rowCount(); ++i)
            {
                QTableWidgetItem* tmp = new QTableWidgetItem();
                tmp -> setText(table["project_title"][i].c_str());
                tableWidget -> setItem(i, 0, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["created_at"][i].c_str());
                tableWidget -> setItem(i, 1, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["project_descrip"][i].c_str());
                tableWidget -> setItem(i, 2, tmp);
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
                    CommandLine1.push_back("project_title=" + titleline -> text().toStdString());
                    is_not_first = 1;
                }

                if(dateline -> date().toString("dd-MM-yyyy") != "01-01-1900")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                        is_not_first = 1;
                    }
                }

                if(descriptionline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("project_descrip=" + descriptionline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("project_descrip=" + descriptionline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                titleline -> clear();
                dateline -> setDate({1, 1, 1});
                descriptionline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Updating Condition", "Your Updating condition is Succesfully entered, please enter your Changable Data.", QMessageBox::Ok);
                where_is_entered = 1;
            }
            else
            {
                CommandLine.push_back(command.toStdString());
                CommandLine.push_back("project");
                CommandLine.push_back("SET");
                if(titleline -> text() != "")
                {
                    CommandLine.push_back("project_title=" + titleline -> text().toStdString());
                }

                if(dateline -> date().toString("dd-MM-yyyy") != "01-01-1900")
                {
                        CommandLine.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                }

                if(descriptionline -> text() != "")
                {
                        CommandLine.push_back("project_descrip=" + descriptionline -> text().toStdString());
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
            CommandLine.push_back("project");
            CommandLine.push_back("WHERE");
            bool is_not_first = 0;
            if(titleline -> text() != "")
            {
                CommandLine.push_back("project_title=" + titleline -> text().toStdString());
                is_not_first = 1;
            }

            if(dateline -> date().toString("dd-MM-yyyy") != "01-01-1900")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                }
                else
                {
                    CommandLine.push_back("created_at=" + dateline -> date().toString("dd-MM-yyyy").toStdString());
                    is_not_first = 1;
                }
            }

            if(descriptionline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("project_descrip=" + descriptionline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("project_descrip=" + descriptionline -> text().toStdString());
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

