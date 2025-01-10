#pragma once

#include <QList>
#include <QString>
#include "Contact.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QtSql>

//Forward declarations
class StorageProvider;
class FileStorage;
class DatabaseStorage;

class PhoneBook
{
private:
    QList<Contact> contacts;
    StorageProvider* storage;
public:
    PhoneBook(StorageProvider* storage);
    PhoneBook();
    ~PhoneBook();

    void addContact(const Contact& contact);
    void removeContact(int id);
    void updateContact(int id, const Contact& contact);
    QList<Contact> findContacts(const QString& query, const QList<QString>& fields);
    QList<Contact> sortContacts(const QString& field, Qt::SortOrder order);
    void loadContacts();
    void saveContacts();

    QList<Contact> getContacts();

};

// Abstract class for save data
class StorageProvider
{
public:
    virtual ~StorageProvider() = default;
    virtual QList<Contact> loadContacts() = 0;
    virtual void saveContacts(const QList<Contact>& contacts) = 0;
};

// Save data in memory
class MemoryStorage : public StorageProvider
{
private:
    QList<Contact> contacts;
public:
    MemoryStorage();
    QList<Contact> loadContacts() override;
    void saveContacts(const QList<Contact>& contacts) override;

};

// Save data if file
class FileStorage : public StorageProvider
{
private:
    QString fileName;
public:
    FileStorage(const QString& fileName);
    QList<Contact> loadContacts() override;
    void saveContacts(const QList<Contact>& contacts) override;
};



