#include "DataBase.h"
#include <sqlite3.h>
#include <QDebug>

DatabaseStorage::DatabaseStorage(const QString& dbPath)
    : db(nullptr), dbPath(dbPath)
{
    int exit = sqlite3_open(dbPath.toUtf8().constData(), &db);
    if (exit) {
        qDebug() << "Error open DB: " << sqlite3_errmsg(db);
        db = nullptr; 
    }
    else {
        qDebug() << "DB was open";
        
    }
}

DatabaseStorage::~DatabaseStorage()
{
    if (db) {
        sqlite3_close(db);
    }
}
QList<Contact> DatabaseStorage::loadContacts()
{
    QList<Contact> contacts;
    if (!db) {
        qDebug() << "Database is not open";
        return contacts;
    }

    const char* sql = "SELECT id, firstName, lastName, middleName, address, birthDate, email, phoneNumbers FROM contacts;";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        qDebug() << "Error preparing select statement: " << sqlite3_errmsg(db);
        return contacts;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Contact contact;
        contact.setId(sqlite3_column_int(stmt, 0));
        contact.setFirstName(QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
        contact.setLastName(QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))));
        contact.setMiddleName(QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))));
        contact.setAddress(QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))));
        QString birthDateString = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        contact.setBirthDate(QDate::fromString(birthDateString, "yyyy-MM-dd"));
        contact.setEmail(QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))));
        QString numbersString = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        QStringList numbersList = numbersString.split("||", QString::SplitBehavior::SkipEmptyParts);
        contact.setPhoneNumbers(numbersList);
        contacts.append(contact);
    }
    sqlite3_finalize(stmt);
    return contacts;
}


void DatabaseStorage::saveContacts(const QList<Contact>& contacts)
{
    if (!db) {
        qDebug() << "Database is not open";
        return;
    }

    // Удаляем старые данные
    const char* deleteSQL = "DELETE FROM contacts;";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, deleteSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        qDebug() << "Error deleting old data: " << errMsg;
        sqlite3_free(errMsg);
        return;
    }

    // Подготавливаем SQL запрос
    const char* insertSQL = "INSERT INTO contacts (id, firstName, lastName, middleName, address, birthDate, email, phoneNumbers) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        qDebug() << "Error preparing insert statement: " << sqlite3_errmsg(db);
        return;
    }

    for (const auto& contact : contacts) {

        QStringList numbersList = contact.getPhoneNumbers();
        QString numbersString = numbersList.join("||");

        sqlite3_bind_int(stmt, 1, contact.getId());
        sqlite3_bind_text(stmt, 2, contact.getFirstName().toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, contact.getLastName().toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, contact.getMiddleName().toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, contact.getAddress().toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, contact.getBirthDate().toString("yyyy-MM-dd").toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, contact.getEmail().toUtf8().constData(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 8, numbersString.toUtf8().constData(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            qDebug() << "Error inserting contact: " << sqlite3_errmsg(db);
        }

        sqlite3_reset(stmt);

    }
    sqlite3_finalize(stmt);
}