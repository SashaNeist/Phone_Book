#pragma once
#include "Contact.h"
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
    ~FileStorage();
    QList<Contact> loadContacts() override;
    void saveContacts(const QList<Contact>& contacts) override;

    friend class PhoneBook;
    friend class MainWindow;
};