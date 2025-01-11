#include "Storage.h"
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
FileStorage::~FileStorage() {

};
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
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text)) {
        qWarning() << "Could not open file for writing: " << fileName;
        return;
    }
    QDataStream stream(&file);
    for (const auto& contact : contacts) {
        contact.serialize(stream);
    }
    if(file.isOpen()) file.close();
}
