#pragma once

#include "Storage.h"

class PhoneBook {
private:
    StorageProvider* storage = nullptr;
    QList<Contact> contacts;
public:
    PhoneBook();
    ~PhoneBook();
    void setStorage(StorageProvider* storage);
    bool addContact(const Contact& contact);
    bool removeContact(int id);
    bool updateContact(int id, const Contact& contact);
    QList<Contact> findContacts(const QString& query, const QList<QString>& fields);
    QList<Contact> sortContacts(const QString& field, Qt::SortOrder order);
    void loadContacts();
    void saveContacts();
    QList<Contact>& getContacts();
};





