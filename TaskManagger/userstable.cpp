#include "userstable.h"

UsersTable::UsersTable(QWidget *parent, QString comm)
    : QMainWindow{parent}, command(comm)
{
    name = new QLabel("Name: ", this);
    name -> move(50, 50);
    name -> show();

    nameline = new QLineEdit(this);
    nameline -> move(150, 55);
    nameline -> resize(200, 20);
    nameline -> show();

    QObject::connect(nameline, &QLineEdit::editingFinished, this, &UsersTable::nameline_editing_finished);

    surname = new QLabel("Surname: ", this);
    surname -> move(50, 90);
    surname -> show();

    surnameline = new QLineEdit(this);
    surnameline -> move(150, 95);
    surnameline -> resize(200, 20);
    surnameline -> show();

    QObject::connect(surnameline, &QLineEdit::editingFinished, this, &UsersTable::surnameline_editing_finished);

    age = new QLabel("Age: ", this);
    age -> move(50, 130);
    age -> show();

    ageline = new QLineEdit(this);
    ageline -> move(150, 135);
    ageline -> resize(200, 20);
    ageline -> show();

    QObject::connect(ageline, &QLineEdit::editingFinished, this, &UsersTable::ageline_editing_finished);

    email = new QLabel("E-Mail: ", this);
    email -> move(50, 170);
    email -> show();

    emailline = new QLineEdit(this);
    emailline -> move(150, 175);
    emailline -> resize(200, 20);
    emailline -> show();

    QObject::connect(emailline, &QLineEdit::editingFinished, this, &UsersTable::emailline_editing_finished);

    phone_number = new QLabel("Phone Number: ", this);
    phone_number -> move(50, 210);
    phone_number -> show();

    phone_numberline = new QLineEdit(this);
    phone_numberline -> move(150, 215);
    phone_numberline -> resize(200, 20);
    phone_numberline -> show();

    QObject::connect(phone_numberline, &QLineEdit::editingFinished, this, &UsersTable::phone_numberline_editing_finished);

    sumbitbutton = new QPushButton("Submit", this);
    sumbitbutton -> resize(100, 20);
    sumbitbutton -> move(250, 250);
    sumbitbutton -> show();

    QObject::connect(sumbitbutton, &QAbstractButton::clicked, this, &UsersTable::clicked_on_submit_button);
}

void UsersTable::nameline_editing_finished()
{
    if(nameline -> text() != "")
    {
        if(!(nameline -> text().front() >= 'A'  && nameline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must start with uppercase.", QMessageBox::Ok);
            nameline -> setText("");
            return;
        }

        for(int i = 1; i < nameline -> text().size(); ++i)
        {
            if(!(nameline -> text()[i] >= 'a' && nameline -> text()[i] <= 'z'))
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must contain only letters.", QMessageBox::Ok);
                nameline -> setText("");
                return;
            }
        }
    }
}

void UsersTable::surnameline_editing_finished()
{
    if(surnameline -> text() != "")
    {
        if(!(surnameline -> text().front() >= 'A'  || surnameline -> text().front() <= 'Z'))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must start with uppercase.", QMessageBox::Ok);
            surnameline -> setText("");
            return;
        }

        for(int i = 1; i < surnameline -> text().size(); ++i)
        {
            if(!(surnameline -> text()[i] >= 'a'  || surnameline -> text()[i] <= 'z'))
            {
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered surname must contain only lowercase letters.", QMessageBox::Ok);
                surnameline -> setText("");
                return;
            }
        }
    }
}

void UsersTable::ageline_editing_finished()
{
    if(!is_number(ageline -> text().toStdString()))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered age must be a number.", QMessageBox::Ok);
        ageline -> setText("");
        return;
    }
}

void UsersTable::emailline_editing_finished()
{
    if(!(emailline -> text().endsWith("@gmail.com") || emailline -> text().endsWith("@mail.ru") || emailline -> text().endsWith("@yahoo.com") || emailline -> text().endsWith("@yandex.ru")))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered e-mail must end with @gmail.com, @mail.ru, @yahoo.com, @yandex.ru", QMessageBox::Ok);
        emailline -> setText("");
        return;
    }
}

void UsersTable::phone_numberline_editing_finished()
{
    if(!(phone_numberline -> text().startsWith("+374") || + phone_numberline -> text().startsWith("+8") || phone_numberline -> text().startsWith("+971")))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered phone number must starts with +374, +8, +971.", QMessageBox::Ok);
        phone_numberline -> setText("");
        return;
    }

    std::string tmp = phone_numberline -> text().toStdString();
    tmp.erase(0, 1);
    if(!is_number(tmp))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered phone number must contains only numbers.", QMessageBox::Ok);
        phone_numberline -> setText("");
        return;
    }
}

void UsersTable::clicked_on_submit_button()
{
    std::vector<std::string> CommandLine;

    switch(CommandParse[command.toStdString()])
    {
        case Command::INSERTINTO:
        {
            if(nameline -> text() == "" )
            {
                nameline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your name line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(surnameline -> text() == "" )
            {
                surnameline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your surname line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(ageline -> text() == "" )
            {
                ageline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your age line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(emailline -> text() == "" )
            {
                emailline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your E-mail line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            if(phone_numberline -> text() == "" )
            {
                phone_numberline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Not Entered", "Your Phone Number line is empty, please enter the information", QMessageBox::Ok);
                return;
            }

            CommandLine.push_back(command.toStdString());
            CommandLine.push_back("user");
            CommandLine.push_back("(");
            CommandLine.push_back("name,");
            CommandLine.push_back("surname,");
            CommandLine.push_back("age,");
            CommandLine.push_back("e_mail");
            CommandLine.push_back("phone_number");
            CommandLine.push_back(")");

            CommandLine.push_back("VALUES");
            CommandLine.push_back("(");
            CommandLine.push_back(nameline -> text().toStdString()+',');
            CommandLine.push_back(surnameline -> text().toStdString()+',');
            CommandLine.push_back(ageline -> text().toStdString()+',');
            CommandLine.push_back(emailline -> text().toStdString()+',');
            CommandLine.push_back(phone_numberline -> text().toStdString());
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
            CommandLine.push_back("user");
            bool is_not_first = 0;
            if(nameline -> text() != "")
            {
                CommandLine.push_back("WHERE");
                CommandLine.push_back("name=" + nameline -> text().toStdString());
                is_not_first = 1;
            }

            if(surnameline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("surname=" + surnameline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("surname=" + surnameline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(ageline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("age=" + ageline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("age=" + ageline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(emailline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("e_mail=" + emailline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("e_mail=" + emailline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(phone_numberline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("phone_number=" + phone_numberline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("WHERE");
                    CommandLine.push_back("phone_number=" + phone_numberline -> text().toStdString());
                }
            }

            std::map<std::string, std::vector<std::string>> table = select(CommandLine);
            QTableWidget* tableWidget = new QTableWidget(table["name"].size(), 5);
            tableWidget -> setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Age" << "E-mail" << "Phone Number");
            for(int i = 0; i < tableWidget -> rowCount(); ++i)
            {

                QTableWidgetItem* tmp = new QTableWidgetItem();
                tmp -> setText(table["name"][i].c_str());
                tableWidget -> setItem(i, 0, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["surname"][i].c_str());
                tableWidget -> setItem(i, 1, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["age"][i].c_str());
                tableWidget -> setItem(i, 2, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["e_mail"][i].c_str());
                tableWidget -> setItem(i, 3, tmp);

                tmp = new QTableWidgetItem();
                tmp -> setText(table["phone_number"][i].c_str());
                tableWidget -> setItem(i, 4, tmp);
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
                if(nameline -> text() != "")
                {
                    CommandLine1.push_back("name=" + nameline -> text().toStdString());
                    is_not_first = 1;
                }

                if(surnameline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("surname=" + surnameline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("surname=" + surnameline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                if(ageline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("age=" + ageline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("age=" + ageline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                if(emailline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("e_mail=" + emailline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("e_mail=" + emailline -> text().toStdString());
                        is_not_first = 1;
                    }
                }

                if(phone_numberline -> text() != "")
                {
                    if(is_not_first)
                    {
                        CommandLine1.push_back("AND");
                        CommandLine1.push_back("phone_number=" + phone_numberline -> text().toStdString());
                    }
                    else
                    {
                        CommandLine1.push_back("phone_number=" + phone_numberline -> text().toStdString());
                    }
                }

                nameline -> clear();
                surnameline -> clear();
                ageline -> clear();
                emailline -> clear();
                phone_numberline -> clear();
                QMessageBox::StandardButton qMessage = QMessageBox::information(this, "Not Entered", "Your Updating condition is Succesfully entered, please enter your Changable Data.", QMessageBox::Ok);
                where_is_entered = 1;
            }
            else
            {
                CommandLine.push_back(command.toStdString());
                CommandLine.push_back("user");
                CommandLine.push_back("SET");
                if(nameline -> text() != "")
                {
                    CommandLine.push_back("name=" + nameline -> text().toStdString());
                }

                if(surnameline -> text() != "")
                {
                        CommandLine.push_back("surname=" + surnameline -> text().toStdString());
                }

                if(ageline -> text() != "")
                {
                        CommandLine.push_back("age=" + ageline -> text().toStdString());
                }

                if(emailline -> text() != "")
                {
                        CommandLine.push_back("e_mail=" + emailline -> text().toStdString());
                }

                if(phone_numberline -> text() != "")
                {
                        CommandLine.push_back("phone_number=" + phone_numberline -> text().toStdString());
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
            CommandLine.push_back("user");
            CommandLine.push_back("WHERE");
            bool is_not_first = 0;
            if(nameline -> text() != "")
            {
                CommandLine.push_back("name=" + nameline -> text().toStdString());
                is_not_first = 1;
            }

            if(surnameline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("surname=" + surnameline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("surname=" + surnameline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(ageline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("age=" + ageline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("age=" + ageline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(emailline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("e_mail=" + emailline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("e_mail=" + emailline -> text().toStdString());
                    is_not_first = 1;
                }
            }

            if(phone_numberline -> text() != "")
            {
                if(is_not_first)
                {
                    CommandLine.push_back("AND");
                    CommandLine.push_back("phone_number=" + phone_numberline -> text().toStdString());
                }
                else
                {
                    CommandLine.push_back("phone_number=" + phone_numberline -> text().toStdString());
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
