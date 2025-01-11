#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QListWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QInputDialog>
#include "Book.h"

namespace Ui {
    class ContactDialog;
}

class ContactDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ContactDialog* ui;
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* middleNameEdit;
    QLineEdit* addressEdit;
    QDateEdit* birthDateEdit;
    QLineEdit* emailEdit;
    QListWidget* phoneNumbersEdit;
    QPushButton* addPhoneNumberButton;
    QPushButton* removePhoneNumberButton;

private slots:
    void onAddPhoneNumber();
    void onRemovePhoneNumber();
    void validateDialog();

public:
    ContactDialog();
    ContactDialog(const Contact& contact);
    ~ContactDialog();
    Contact getContact();
};