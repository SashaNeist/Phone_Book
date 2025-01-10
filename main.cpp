#include <QCoreApplication>
#include <QDebug>
#include "Book.h"
#include "Contact.h"

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
 
    FileStorage storage("report-log.txt");
    PhoneBook phoneBook(&storage);

    phoneBook.addContact({ "Alexandr", "Muraev", { "+79174013673" } });
    phoneBook.saveContacts();
    phoneBook.loadContacts();

    for (const auto& loadedContact : phoneBook.getContacts()) {
        qDebug() << loadedContact;
    }

    return a.exec();
}
