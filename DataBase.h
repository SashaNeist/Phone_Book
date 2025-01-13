#pragma once
#include "Storage.h"
#include <QString>
#include <QList>
#include <sqlite3.h>

class DatabaseStorage : public StorageProvider
{
private:
    sqlite3* db;
    QString dbPath;
    void createTableIfNotExists();
public:
    DatabaseStorage(const QString& dbPath);
    ~DatabaseStorage() override;

    QList<Contact> loadContacts() override;
    void saveContacts(const QList<Contact>& contacts) override;
};