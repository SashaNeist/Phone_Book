#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include <utility>
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
    QList<QString> sortFields = { "firstName", "lastName", "middleName", "address", "birthDate", "email"};
    QList<std::pair<QString, Qt::SortOrder>> sortFieldsForSort;
    ContactDialog* contactDialog = nullptr;
    
private slots:
    void onAddContact();
    void onEditContact();
    void onCellDoubleClicked(int row, int column);
    void editField(QString& field);
    void editPhoneNumber(QList<QString>& field);
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