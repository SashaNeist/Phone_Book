#include "ContactDialog.h"
#include "ui_contactdialog.h"
#include <QMessageBox>
#include <QRegularExpression>

ContactDialog::ContactDialog() : QDialog(),
    ui(new Ui::ContactDialog)
{
    ui->setupUi(this);
    firstNameEdit = ui->firstNameEdit;
    lastNameEdit = ui->lastNameEdit;
    middleNameEdit = ui->middleNameEdit;
    addressEdit = ui->addressEdit;
    birthDateEdit = ui->birthDateEdit;
    emailEdit = ui->emailEdit;
    phoneNumbersEdit = ui->phoneNumbersListWidget;
    addPhoneNumberButton = ui->addPhoneNumberButton;
    removePhoneNumberButton = ui->removePhoneNumberButton;
    connect(addPhoneNumberButton, &QPushButton::clicked, this, &ContactDialog::onAddPhoneNumber);
    connect(removePhoneNumberButton, &QPushButton::clicked, this, &ContactDialog::onRemovePhoneNumber);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ContactDialog::validateDialog);

    birthDateEdit->setDate(QDate::currentDate());
}
ContactDialog::ContactDialog(const Contact& contact) :
    QDialog(),
    ui(new Ui::ContactDialog)
{
    ui->setupUi(this);
    firstNameEdit = ui->firstNameEdit;
    lastNameEdit = ui->lastNameEdit;
    middleNameEdit = ui->middleNameEdit;
    addressEdit = ui->addressEdit;
    birthDateEdit = ui->birthDateEdit;
    emailEdit = ui->emailEdit;
    phoneNumbersEdit = ui->phoneNumbersListWidget;
    addPhoneNumberButton = ui->addPhoneNumberButton;
    removePhoneNumberButton = ui->removePhoneNumberButton;

    firstNameEdit->setText(contact.getFirstName());
    lastNameEdit->setText(contact.getLastName());
    middleNameEdit->setText(contact.getMiddleName());
    addressEdit->setText(contact.getAddress());
    birthDateEdit->setDate(contact.getBirthDate());
    emailEdit->setText(contact.getEmail());
    phoneNumbersEdit->addItems(contact.getPhoneNumbers());

    connect(addPhoneNumberButton, &QPushButton::clicked, this, &ContactDialog::onAddPhoneNumber);
    connect(removePhoneNumberButton, &QPushButton::clicked, this, &ContactDialog::onRemovePhoneNumber);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ContactDialog::validateDialog);
}
ContactDialog::~ContactDialog()
{
    delete ui;
}

Contact ContactDialog::getContact() {
    QString firstName = firstNameEdit->text().trimmed();
    QString lastName = lastNameEdit->text().trimmed();
    QString middleName = middleNameEdit->text().trimmed();
    QString address = addressEdit->text().trimmed();
    QDate birthDate = birthDateEdit->date();
    QString email = emailEdit->text().trimmed();
    QList<QString> numbers;
    for (int i = 0; i < phoneNumbersEdit->count(); ++i) {
        numbers.append(phoneNumbersEdit->item(i)->text());
    }

    return  Contact(firstName, lastName, middleName, address, birthDate, email, numbers);
}

void ContactDialog::onAddPhoneNumber() {
    bool ok;
    QString phoneNumber = QInputDialog::getText(this, tr("Add phone number"),
        tr("Phone number:"), QLineEdit::Normal,
        "", &ok);
    if (ok && !phoneNumber.isEmpty()) {
        QRegularExpression phoneRegex("^(?:\\+7|8)?[\\s(]?(\\d{3})[\\s)]?(\\d{3})[\\s-]?(\\d{2})[\\s-]?(\\d{2})$");
        if (!phoneRegex.match(phoneNumber).hasMatch()) {
            QMessageBox::warning(this, "Warning", "Incorrect phone format. Example +79999999999");
            return;
        }
        phoneNumbersEdit->addItem(phoneNumber);
    }

}

void ContactDialog::onRemovePhoneNumber() {
    int selectedRow = phoneNumbersEdit->currentRow();
    if (selectedRow >= 0) {
        phoneNumbersEdit->takeItem(selectedRow);
    }
}

void ContactDialog::validateDialog()
{
    QString firstName = firstNameEdit->text().trimmed();
    QString lastName = lastNameEdit->text().trimmed();
    QString middleName = middleNameEdit->text().trimmed();
    QString address = addressEdit->text().trimmed();
    QDate birthDate = birthDateEdit->date();
    QString email = emailEdit->text().trimmed();
    QList<QString> numbers;
    for (int i = 0; i < phoneNumbersEdit->count(); ++i) {
        numbers.append(phoneNumbersEdit->item(i)->text());
    }

    Contact contact = Contact(firstName, lastName, middleName, address, birthDate, email, numbers);
    if (!contact.isValid()) {
        QMessageBox::warning(this, "Warning", "Data is not valid");
        return;
    }
    QDialog::accept();
}