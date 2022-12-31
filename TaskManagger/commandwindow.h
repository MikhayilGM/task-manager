#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <map>
#include <userstable.h>
#include <taskstable.h>
#include <projecttables.h>

class CommandWindow : public QMainWindow
{
    Q_OBJECT
    enum class TABLES
    {
        USER,
        TASKS,
        PROJECT,
    };

public:
    explicit CommandWindow(QWidget *parent = nullptr);
    explicit CommandWindow( QString tb_name = "NONE", QWidget *parent = nullptr);
    void clicked_on_add_button();
    void clicked_on_show_button();
    void clicked_on_delete_button();
    void clicked_on_update_button();

private:
    std::map<QString, TABLES>  ParseTables;
    QString table_name;
    QPushButton* add_button;
    QPushButton* show_button;
    QPushButton* delete_button;
    QPushButton* update_button;
};

#endif // COMMANDWINDOW_H
