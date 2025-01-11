/********************************************************************************
** Form generated from reading UI file 'contactdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTDIALOG_H
#define UI_CONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ContactDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *firstNameLabel;
    QLineEdit *firstNameEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameEdit;
    QLabel *middleNameLabel;
    QLineEdit *middleNameEdit;
    QLabel *addressLabel;
    QLineEdit *addressEdit;
    QLabel *birthDateLabel;
    QDateEdit *birthDateEdit;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *phoneNumbersLabel;
    QListWidget *phoneNumbersListWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addPhoneNumberButton;
    QPushButton *removePhoneNumberButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ContactDialog)
    {
        if (ContactDialog->objectName().isEmpty())
            ContactDialog->setObjectName(QString::fromUtf8("ContactDialog"));
        ContactDialog->resize(400, 300);
        gridLayout = new QGridLayout(ContactDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        firstNameLabel = new QLabel(ContactDialog);
        firstNameLabel->setObjectName(QString::fromUtf8("firstNameLabel"));

        gridLayout->addWidget(firstNameLabel, 0, 0, 1, 1);

        firstNameEdit = new QLineEdit(ContactDialog);
        firstNameEdit->setObjectName(QString::fromUtf8("firstNameEdit"));

        gridLayout->addWidget(firstNameEdit, 0, 1, 1, 1);

        lastNameLabel = new QLabel(ContactDialog);
        lastNameLabel->setObjectName(QString::fromUtf8("lastNameLabel"));

        gridLayout->addWidget(lastNameLabel, 1, 0, 1, 1);

        lastNameEdit = new QLineEdit(ContactDialog);
        lastNameEdit->setObjectName(QString::fromUtf8("lastNameEdit"));

        gridLayout->addWidget(lastNameEdit, 1, 1, 1, 1);

        middleNameLabel = new QLabel(ContactDialog);
        middleNameLabel->setObjectName(QString::fromUtf8("middleNameLabel"));

        gridLayout->addWidget(middleNameLabel, 2, 0, 1, 1);

        middleNameEdit = new QLineEdit(ContactDialog);
        middleNameEdit->setObjectName(QString::fromUtf8("middleNameEdit"));

        gridLayout->addWidget(middleNameEdit, 2, 1, 1, 1);

        addressLabel = new QLabel(ContactDialog);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        gridLayout->addWidget(addressLabel, 3, 0, 1, 1);

        addressEdit = new QLineEdit(ContactDialog);
        addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

        gridLayout->addWidget(addressEdit, 3, 1, 1, 1);

        birthDateLabel = new QLabel(ContactDialog);
        birthDateLabel->setObjectName(QString::fromUtf8("birthDateLabel"));

        gridLayout->addWidget(birthDateLabel, 4, 0, 1, 1);

        birthDateEdit = new QDateEdit(ContactDialog);
        birthDateEdit->setObjectName(QString::fromUtf8("birthDateEdit"));
        birthDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(birthDateEdit, 4, 1, 1, 1);

        emailLabel = new QLabel(ContactDialog);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        gridLayout->addWidget(emailLabel, 5, 0, 1, 1);

        emailEdit = new QLineEdit(ContactDialog);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));

        gridLayout->addWidget(emailEdit, 5, 1, 1, 1);

        phoneNumbersLabel = new QLabel(ContactDialog);
        phoneNumbersLabel->setObjectName(QString::fromUtf8("phoneNumbersLabel"));

        gridLayout->addWidget(phoneNumbersLabel, 6, 0, 1, 1);

        phoneNumbersListWidget = new QListWidget(ContactDialog);
        phoneNumbersListWidget->setObjectName(QString::fromUtf8("phoneNumbersListWidget"));

        gridLayout->addWidget(phoneNumbersListWidget, 6, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addPhoneNumberButton = new QPushButton(ContactDialog);
        addPhoneNumberButton->setObjectName(QString::fromUtf8("addPhoneNumberButton"));

        horizontalLayout->addWidget(addPhoneNumberButton);

        removePhoneNumberButton = new QPushButton(ContactDialog);
        removePhoneNumberButton->setObjectName(QString::fromUtf8("removePhoneNumberButton"));

        horizontalLayout->addWidget(removePhoneNumberButton);


        gridLayout->addLayout(horizontalLayout, 7, 1, 1, 1);

        buttonBox = new QDialogButtonBox(ContactDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 8, 0, 1, 2);


        retranslateUi(ContactDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ContactDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ContactDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ContactDialog);
    } // setupUi

    void retranslateUi(QDialog *ContactDialog)
    {
        ContactDialog->setWindowTitle(QApplication::translate("ContactDialog", "Contact Details", nullptr));
        firstNameLabel->setText(QApplication::translate("ContactDialog", "First Name:", nullptr));
        lastNameLabel->setText(QApplication::translate("ContactDialog", "Last Name:", nullptr));
        middleNameLabel->setText(QApplication::translate("ContactDialog", "Middle Name:", nullptr));
        addressLabel->setText(QApplication::translate("ContactDialog", "Address:", nullptr));
        birthDateLabel->setText(QApplication::translate("ContactDialog", "Birth Date:", nullptr));
        emailLabel->setText(QApplication::translate("ContactDialog", "Email:", nullptr));
        phoneNumbersLabel->setText(QApplication::translate("ContactDialog", "Phone Numbers:", nullptr));
        addPhoneNumberButton->setText(QApplication::translate("ContactDialog", "Add", nullptr));
        removePhoneNumberButton->setText(QApplication::translate("ContactDialog", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContactDialog: public Ui_ContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTDIALOG_H
