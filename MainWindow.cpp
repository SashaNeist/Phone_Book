#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QLabel>
 
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DatabaseStorage* DBStorage = new DatabaseStorage("phonebook.db");
    phoneBook.setStorage(DBStorage);
    contactsTable = ui->contactsTableWidget;
    contactsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    searchLineEdit = ui->searchLineEdit;

    connect(ui->addContactButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(ui->editContactButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(ui->removeContactButton, &QPushButton::clicked, this, &MainWindow::onRemoveContact);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchContact);
    connect(ui->sortContacts, &QPushButton::clicked, this, &MainWindow::onSortContacts);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::on_actionLoad_triggered);
    connect(contactsTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::onCellDoubleClicked);
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
            // Используем id из текущего контакта и обновляем его данными из диалогового окна
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

void MainWindow::onCellDoubleClicked(int row, int column) {
    if (row < 0 || column < 0) {
        return; // Защита от некорректного выбора
    }

    // Получаем текущий контакт
    Contact currentContact = phoneBook.getContacts()[row];
    // В зависимости от столбца выбираем, какое поле редактировать
    QString temp;
    QList<QString> temp2;
    QDate date;
    switch (column) {
    case 0:
        editField(temp);
        currentContact.setFirstName(temp);
        break;
    case 1:
        editField(temp);
        currentContact.setLastName(temp);
        break;
    case 2:
        editField(temp);
        currentContact.setMiddleName(temp);
        break;
    case 3:
        editField(temp);
        currentContact.setAddress(temp);
        break;
    case 4:
        temp = date.toString("yyyy-MM-dd"); 
        editField(temp);
        date = QDate::fromString(temp, "yyyy-MM-dd");
        currentContact.setBirthDate(date);
        break;
    case 5:
        editField(temp);
        currentContact.setEmail(temp);
        break;
    case 6:
        editPhoneNumber(temp2);
        currentContact.setPhoneNumbers(temp2);
        break;
        // Добавьте другие поля по необходимости
    default:
        return; // Если столбец не поддерживается, выходим
    }

    if (currentContact.isValid()) {
        // Обновляем контакт в модели
        phoneBook.getContacts()[row] = currentContact;
        // Обновляем таблицу
        updateTable();
    }
    else qWarning() << "Data is not valid!\n";
}

void MainWindow::editField(QString& field) {
    bool ok;
    QString newValue = QInputDialog::getText(this, tr("Edit Contact"),
        tr("Edit Field:"), QLineEdit::Normal,
        field, &ok);
    if (ok && !newValue.isEmpty()) {
        field = newValue; // обновляем значение поля
    }
}
void MainWindow::editPhoneNumber(QList<QString>& phoneNumbers) {
    bool ok;
    QString currentNumbers = phoneNumbers.join(", "); // Объединяем номера в строку

    QString newPhoneNumber = QInputDialog::getText(this, tr("Edit Phone Number"),
        tr("Phone Numbers:"), QLineEdit::Normal, currentNumbers, &ok);

    if (ok && !newPhoneNumber.isEmpty()) {
        // Обновляем список номеров
        phoneNumbers = newPhoneNumber.split(", ", QString::SkipEmptyParts); // Разделяем строку по запятой и пробелу
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

void MainWindow::onSortContacts()
{
    QMenu* sortMenu = new QMenu(this);
    for (const auto& field : sortFields) {
        QAction* action = new QAction(tr(field.toStdString().c_str()), this);
        sortMenu->addAction(action);
        connect(action, &QAction::triggered, [this, field]() {
            // Создаем диалог для выбора порядка сортировки
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Select the sort order"));
            QVBoxLayout* layout = new QVBoxLayout(&dialog);
            QComboBox* orderBox = new QComboBox(&dialog);
            orderBox->addItems({ tr("Ascending"), tr("Descending") });
            QPushButton* okButton = new QPushButton(tr("OK"), &dialog);
            QPushButton* cancelButton = new QPushButton(tr("Cancel"), &dialog);

            layout->addWidget(new QLabel(tr("field: %1").arg(field)));
            layout->addWidget(orderBox);
            QHBoxLayout* buttonLayout = new QHBoxLayout();
            buttonLayout->addWidget(okButton);
            buttonLayout->addWidget(cancelButton);
            layout->addLayout(buttonLayout);

            QObject::connect(okButton, &QPushButton::clicked, [&]() {
                dialog.accept();
                });
            QObject::connect(cancelButton, &QPushButton::clicked, [&]() {
                dialog.reject();
                });

            if (dialog.exec() == QDialog::Accepted) {
                Qt::SortOrder sortOrder = orderBox->currentText() == tr("Ascending") ? Qt::AscendingOrder : Qt::DescendingOrder;
                sortFieldsForSort.append({ field, sortOrder }); //добавляем в список сортировки
                // Запускаем обновление таблицы
                QMessageBox::information(this, tr("Sort"), tr("Sorting added by field: %1").arg(field));
                phoneBook.sortContacts(sortFieldsForSort);
                updateTable();
            }
            });
    }
    QAction* removeAllSortAction = new QAction(tr("Delete all sorts"), this);
    connect(removeAllSortAction, &QAction::triggered, [this]() {
        sortFieldsForSort.clear();
        phoneBook.sortContacts(sortFieldsForSort);
        phoneBook.loadContacts();
        updateTable();
        });
    sortMenu->addSeparator();
    sortMenu->addAction(removeAllSortAction);
    sortMenu->exec(ui->sortContacts->mapToGlobal(ui->sortContacts->rect().bottomLeft()));
}

void MainWindow::updateTable() {
    contactsTable->setRowCount(0);  // Очищаем текущие строки, но без двойного чистки элемента

    QList<Contact> contacts = phoneBook.getContacts();
    contactsTable->setRowCount(contacts.size());

    for (int row = 0; row < contacts.size(); ++row) {
        const Contact& contact = contacts[row];
        contactsTable->setItem(row, 0, new QTableWidgetItem(contact.getFirstName()));
        contactsTable->setItem(row, 1, new QTableWidgetItem(contact.getLastName()));
        contactsTable->setItem(row, 2, new QTableWidgetItem(contact.getMiddleName()));
        contactsTable->setItem(row, 3, new QTableWidgetItem(contact.getAddress()));
        contactsTable->setItem(row, 4, new QTableWidgetItem(contact.getBirthDate().toString("dd.MM.yyyy")));
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
