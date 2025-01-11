#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileStorage* fileStorage = new FileStorage("contacts.txt");
    phoneBook.setStorage(fileStorage);
    contactsTable = ui->contactsTableWidget;
    contactsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    searchLineEdit = ui->searchLineEdit;

    QMenu* sortMenu = new QMenu(this);
    for (const auto& field : sortFields) {
        QAction* action = new QAction(field, this);
        sortMenu->addAction(action);
        connect(action, &QAction::triggered, [this, field]() {
            bool ok;
            QStringList items;
            items << tr("Ascending") << tr("Descending");

            QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                tr("Sort order:"), items, 0, false, &ok);
            if (ok && !item.isEmpty()) {
                Qt::SortOrder sortOrder = item == "Ascending" ? Qt::AscendingOrder : Qt::DescendingOrder;
                phoneBook.sortContacts(field, sortOrder);
                updateTable();
            }
            });
    }
    ui->sortContacts->setMenu(sortMenu);


    connect(ui->addContactButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(ui->editContactButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(ui->removeContactButton, &QPushButton::clicked, this, &MainWindow::onRemoveContact);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchContact);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::on_actionLoad_triggered);

    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddContact() {
    contactDialog = new ContactDialog();
    if (contactDialog->exec() == QDialog::Accepted) {
        if(phoneBook.addContact(contactDialog->getContact())) updateTable();
    }
    delete contactDialog;
    contactDialog = nullptr;

}

void MainWindow::onEditContact() {
    int selectedRow = contactsTable->currentRow();
    if (selectedRow >= 0) {
        Contact currentContact = phoneBook.getContacts()[selectedRow];
        contactDialog = new ContactDialog(currentContact);
        if (contactDialog->exec() == QDialog::Accepted) {
            // »спользуем id из текущего контакта и обновл€ем его данными из диалогового окна
            phoneBook.getContacts()[selectedRow] = contactDialog->getContact();
            updateTable();
        }
        delete contactDialog;
        contactDialog = nullptr;
    }
    else {
        QMessageBox::warning(this, "Warning", "Select contact to edit.");
    }
}

void MainWindow::onRemoveContact() {
    int selectedRow = contactsTable->currentRow();
    if (selectedRow >= 0) {
        Contact contactToRemove = phoneBook.getContacts().at(selectedRow);
        if (phoneBook.removeContact(contactToRemove.getId())) updateTable();
        else qWarning() << "Error: Remove contact";
        
    }
    else {
        QMessageBox::warning(this, "Warning", "Select contact to remove.");
    }
}

void MainWindow::onSearchContact() {
    QString searchText = searchLineEdit->text();
    QList<Contact> foundContacts;
    if (!searchText.isEmpty()) {
        QList<QString> fields = { "firstName", "lastName", "middleName", "address", "email" };
        foundContacts = phoneBook.findContacts(searchText, fields);
    }
    else {
        foundContacts = phoneBook.getContacts();
    }
    contactsTable->clearContents();
    contactsTable->setRowCount(foundContacts.size());

    for (int row = 0; row < foundContacts.size(); ++row) {
        const Contact& contact = foundContacts[row];
        contactsTable->setItem(row, 0, new QTableWidgetItem(contact.getFirstName()));
        contactsTable->setItem(row, 1, new QTableWidgetItem(contact.getLastName()));
        contactsTable->setItem(row, 2, new QTableWidgetItem(contact.getMiddleName()));
        contactsTable->setItem(row, 3, new QTableWidgetItem(contact.getAddress()));
        contactsTable->setItem(row, 4, new QTableWidgetItem(contact.getBirthDate().toString()));
        contactsTable->setItem(row, 5, new QTableWidgetItem(contact.getEmail()));
        QString numbers = contact.getPhoneNumbers().join(", ");
        contactsTable->setItem(row, 6, new QTableWidgetItem(numbers));
    }
}

void MainWindow::onSortContacts() {
    // «десь будет код дл€ сортировки контактов
    
    qDebug() << "onSortContacts() called";
}

void MainWindow::updateTable() {
    // ќчистка содержимого таблицы и удаление старых QTableWidgetItem
    for (int row = 0; row < contactsTable->rowCount(); ++row) {
        for (int col = 0; col < contactsTable->columnCount(); ++col) {
            QTableWidgetItem* item = contactsTable->item(row, col);
            if (item) {
                delete item;
                contactsTable->setItem(row, col, nullptr);
            }
        }
    }
    contactsTable->clearContents();

    QList<Contact> contacts = phoneBook.getContacts();
    contactsTable->setRowCount(contacts.size());

    for (int row = 0; row < contacts.size(); ++row) {
        const Contact& contact = contacts[row];
        contactsTable->setItem(row, 0, new QTableWidgetItem(contact.getFirstName()));
        contactsTable->setItem(row, 1, new QTableWidgetItem(contact.getLastName()));
        contactsTable->setItem(row, 2, new QTableWidgetItem(contact.getMiddleName()));
        contactsTable->setItem(row, 3, new QTableWidgetItem(contact.getAddress()));
        contactsTable->setItem(row, 4, new QTableWidgetItem(contact.getBirthDate().toString("dd.MM.yyyy"))); // ѕример формата
        contactsTable->setItem(row, 5, new QTableWidgetItem(contact.getEmail()));
        QString numbers = contact.getPhoneNumbers().join(", ");
        contactsTable->setItem(row, 6, new QTableWidgetItem(numbers));
    }
}


void MainWindow::on_actionSave_triggered()
{
    phoneBook.saveContacts();
}

void MainWindow::on_actionLoad_triggered()
{
    phoneBook.loadContacts();
    updateTable();
}
