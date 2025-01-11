/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QTableWidget *contactsTableWidget;
    QPushButton *addContactButton;
    QPushButton *editContactButton;
    QPushButton *removeContactButton;
    QPushButton *sortContacts;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 595);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        gridLayout->addWidget(searchLineEdit, 0, 0, 1, 3);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        gridLayout->addWidget(searchButton, 0, 3, 1, 1);

        contactsTableWidget = new QTableWidget(centralwidget);
        if (contactsTableWidget->columnCount() < 7)
            contactsTableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        contactsTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        contactsTableWidget->setObjectName(QString::fromUtf8("contactsTableWidget"));

        gridLayout->addWidget(contactsTableWidget, 1, 0, 1, 4);

        addContactButton = new QPushButton(centralwidget);
        addContactButton->setObjectName(QString::fromUtf8("addContactButton"));

        gridLayout->addWidget(addContactButton, 2, 0, 1, 1);

        editContactButton = new QPushButton(centralwidget);
        editContactButton->setObjectName(QString::fromUtf8("editContactButton"));

        gridLayout->addWidget(editContactButton, 2, 1, 1, 1);

        removeContactButton = new QPushButton(centralwidget);
        removeContactButton->setObjectName(QString::fromUtf8("removeContactButton"));

        gridLayout->addWidget(removeContactButton, 2, 2, 1, 1);

        sortContacts = new QPushButton(centralwidget);
        sortContacts->setObjectName(QString::fromUtf8("sortContacts"));

        gridLayout->addWidget(sortContacts, 2, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Phone Book", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        searchLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Search...", nullptr));
        searchButton->setText(QApplication::translate("MainWindow", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = contactsTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "First Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = contactsTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Last Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = contactsTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Middle Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = contactsTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Address", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = contactsTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Birth Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = contactsTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = contactsTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Phone Numbers", nullptr));
        addContactButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        editContactButton->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        removeContactButton->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        sortContacts->setText(QApplication::translate("MainWindow", "Sort", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
