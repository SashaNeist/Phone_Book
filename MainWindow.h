#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include "ContactDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    PhoneBook phoneBook;
    QTableWidget* contactsTable;
    QLineEdit* searchLineEdit;
    QList<QString> sortFields = { "firstName", "lastName", "middleName", "birthDate"};
    ContactDialog* contactDialog = nullptr;
    
private slots:
    void onAddContact();
    void onEditContact();
    void onRemoveContact();
    void onSearchContact();
    void onSortContacts();
    void updateTable();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

};