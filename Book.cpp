#include "Book.h"
#include <algorithm>
#include <QRegularExpression>

// Constructors
PhoneBook::PhoneBook() = default;
PhoneBook::~PhoneBook()
{
    if (storage) {
        delete storage;
    }
}
void PhoneBook::setStorage(StorageProvider* storage)
{
    this->storage = storage;
    loadContacts();
}

// Change contacts
bool PhoneBook::addContact(const Contact& contact) {
    if (!contact.isValid()) return false;
    contacts.append(contact);
    return true;
}
bool PhoneBook::removeContact(int id) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == id) {
            contacts.removeAt(i);
            // Find id and delete
            return true;
        }
    }
    qWarning() << "Contact with id = " << id << " not found";
    return false;
}
bool PhoneBook::updateContact(int id, const Contact& contact) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == id) {
            contacts[i] = contact;
            return true;
        }
    }
    qWarning() << "Contact with id = " << id << " not found";
    return false;
}

// Find|Sort contacts
QList<Contact> PhoneBook::findContacts(const QString& query, const QList<QString>& fields) {
        QList<Contact> results;
        if (query.isEmpty() || fields.isEmpty()) {
            return contacts;
        }
        for (const auto& contact : contacts) {
             bool contactFound = false;
             for (const auto& field : fields) {
                if (field == "firstName" && contact.getFirstName().contains(query, Qt::CaseInsensitive)) {
                   contactFound = true;
                    break;
                }
               else if (field == "lastName" && contact.getLastName().contains(query, Qt::CaseInsensitive)) {
                    contactFound = true;
                    break;
                }
               else if (field == "middleName" && contact.getMiddleName().contains(query, Qt::CaseInsensitive)) {
                    contactFound = true;
                    break;
                }
                else if (field == "address" && contact.getAddress().contains(query, Qt::CaseInsensitive)) {
                    contactFound = true;
                    break;
               }
               else if (field == "email" && contact.getEmail().contains(query, Qt::CaseInsensitive)) {
                    contactFound = true;
                    break;
               }
         }
            if (contactFound) {
                results.append(contact);
           }
        }
        return results;
    }
QList<Contact> PhoneBook::sortContacts(const QString& field, Qt::SortOrder order) {
    if (contacts.empty()) return contacts;
    std::sort(contacts.begin(), contacts.end(), [&](const Contact& a, const Contact& b) {
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
        else if (field == "birthDate")
        {
            result = a.getBirthDate() < b.getBirthDate();
        }
        else if (field == "email")
        {
            result = a.getEmail() < b.getEmail();
        }
        if (order == Qt::DescendingOrder)
        {
            result = !result;
        }
        return result;
        });
    return contacts;
}

// Load|Save contacts
void PhoneBook::loadContacts() {
    if (storage) {
        try
        {
            QList<Contact> loadedContacts = storage->loadContacts();
            if (!loadedContacts.isEmpty()) {
                contacts = loadedContacts;
            }
        }
        catch (const std::exception& ex) {
            qWarning() << "Storage is invalid" << ex.what();
        }
    }
    else {
        qWarning() << "Storage is not set";
    }
}
void PhoneBook::saveContacts() {
    if (storage) {
        try {
            storage->saveContacts(contacts);
        }
        catch (const std::ios_base::failure& ex) {
            qWarning() << "I/O Error during save: " << ex.what();
        }
        catch (const std::exception& ex) {
            qWarning() << "Generic exception during save: " << ex.what();
        }
    }
    else {
        qWarning() << "Storage is not set";
    }
}

//Getter
QList<Contact>& PhoneBook::getContacts() {
    return contacts;
}




