#include "Book.h"
#include <algorithm>
#include <QRegularExpression>

// Constructors
PhoneBook::PhoneBook(StorageProvider * storage) : storage(storage)
{
    loadContacts();
}
PhoneBook::PhoneBook() : storage(nullptr) {}

PhoneBook::~PhoneBook()
{
    if (storage) {
        delete storage;
    }
}

// Change contacts
void PhoneBook::addContact(const Contact& contact) {
    contacts.append(contact);
}
void PhoneBook::removeContact(int id) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == id) {
            contacts.removeAt(i);
            // Find id and delete
            return;
        }
    }
    qWarning() << "Contact with id = " << id << " not found";
}
void PhoneBook::updateContact(int id, const Contact& contact) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == id) {
            contacts[i] = contact;
            return;
        }
    }
    qWarning() << "Contact with id = " << id << " not found";
}

// Find|Sort contacts
QList<Contact> PhoneBook::findContacts(const QString& query, const QList<QString>& fields) {
    QList<Contact> results;
    if (query.isEmpty() || fields.isEmpty()) {
        return contacts;
    }
    for (const auto& contact : contacts) {
        for (const auto& field : fields) {
            if (field == "firstName" && contact.getFirstName().contains(query, Qt::CaseInsensitive)) {
                results.append(contact);
                break;
            }
            else if (field == "lastName" && contact.getLastName().contains(query, Qt::CaseInsensitive)) {
                results.append(contact);
                break;
            }
            else if (field == "middleName" && contact.getMiddleName().contains(query, Qt::CaseInsensitive)) {
                results.append(contact);
                break;
            }
            else if (field == "address" && contact.getAddress().contains(query, Qt::CaseInsensitive)) {
                results.append(contact);
                break;
            }
            else if (field == "email" && contact.getEmail().contains(query, Qt::CaseInsensitive)) {
                results.append(contact);
                break;
            }
        }
    }
    return results;
}
QList<Contact> PhoneBook::sortContacts(const QString& field, Qt::SortOrder order) {
    std::sort(contacts.begin(), contacts.end(), [field, order](const Contact& a, const Contact& b) {
        bool result = false;
        if (field == "firstName") {
            result = a.getFirstName() < b.getFirstName();
        }
        else if (field == "lastName") {
            result = a.getLastName() < b.getLastName();
        }
        else if (field == "middleName") {
            result = a.getMiddleName() < b.getMiddleName();
        }
        else if (field == "address") {
            result = a.getAddress() < b.getAddress();
        }
        else if (field == "birthDate") {
            result = a.getBirthDate() < b.getBirthDate();
        }
        else if (field == "email") {
            result = a.getEmail() < b.getEmail();
        }
        return (order == Qt::AscendingOrder) ? result : !result;
        });
    return contacts;
}

// Load|Save contacts
void PhoneBook::loadContacts() {
    if (storage) {
        contacts = storage->loadContacts();
    }
    else {
        qWarning() << "Storage is not set";
    }
}
void PhoneBook::saveContacts() {
    if (storage) {
        storage->saveContacts(contacts);
    }
    else {
        qWarning() << "Storage is not set";
    }
}

//Getter
QList<Contact> PhoneBook::getContacts() {
    return contacts;
}


// Save data in memory
MemoryStorage::MemoryStorage() {}
QList<Contact> MemoryStorage::loadContacts() {
    return contacts;
}
void MemoryStorage::saveContacts(const QList<Contact>& contacts) {
    this->contacts = contacts;
}

// Save data in file
FileStorage::FileStorage(const QString& fileName) : fileName(fileName) {}
QList<Contact> FileStorage::loadContacts() {
    QList<Contact> contacts;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading: " << fileName;
        return contacts;
    }
    QDataStream stream(&file);
    while (!stream.atEnd()) {
        Contact contact;
        contact.deserialize(stream);
        contacts.append(contact);
    }
    file.close();
    return contacts;
}
void FileStorage::saveContacts(const QList<Contact>& contacts) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing: " << fileName;
        return;
    }
    QDataStream stream(&file);
    for (const auto& contact : contacts) {
        contact.serialize(stream);
    }
    file.close();
}


