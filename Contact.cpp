#include "Contact.h"

#include <QRegularExpression>
#include <QDebug>
#include <QDateTime>

int Contact::nextId = 1;

Contact::Contact() : id(nextId++), firstName(""), lastName(""), middleName(""), address(""), email(""), phoneNumbers({}) {}
Contact::Contact(const QString& firstName, const QString& lastName, const QList<QString>& phoneNumbers)
    : id(nextId++),
    firstName(firstName),
    lastName(lastName),
    middleName(),  // Default QString
    address(),      // Default QString
    birthDate(),    // Default QDate(invalid)
    email(),        // Default QString
    phoneNumbers(phoneNumbers) {}
Contact::Contact(const QString& firstName, const QString& lastName, const QString& middleName,
    const QString& address, const QDate& birthDate, const QString& email, const QList<QString>& phoneNumbers)
    : id(nextId++), 
    firstName(firstName), 
    lastName(lastName), 
    middleName(middleName), 
    address(address),
    birthDate(birthDate), 
    email(email), 
    phoneNumbers(phoneNumbers) {}
Contact::Contact(const Contact& other)
    : id(other.id),
    firstName(other.firstName),
    lastName(other.lastName),
    middleName(other.middleName),
    address(other.address),
    birthDate(other.birthDate),
    email(other.email),
    phoneNumbers(other.phoneNumbers)
{
    qDebug() << "Contact::Contact (copy constructor)";
}

//Getters
int Contact::getId() const {
    return id;
}
QString Contact::getFirstName() const {
    return firstName;
}
QString Contact::getLastName() const {
    return lastName;
}
QString Contact::getMiddleName() const {
    return middleName;
}
QString Contact::getAddress() const {
    return address;
}
QDate Contact::getBirthDate() const {
    return birthDate;
}
QString Contact::getEmail() const {
    return email;
}
QList<QString> Contact::getPhoneNumbers() const {
    return phoneNumbers;
}

//Setters
void Contact::setId(const int& id) {
    this->id = id;
}
void Contact::setFirstName(const QString& firstName) {
    if (validateName(firstName)) {
        this->firstName = firstName.trimmed();
    }
    else {
        qWarning() << "Invalid first name";
    }
}
void Contact::setLastName(const QString& lastName) {
    if (validateName(lastName)) {
        this->lastName = lastName.trimmed();
    }
    else {
        qWarning() << "Invalid last name";
    }
}
void Contact::setMiddleName(const QString& middleName) {
    if (validateName(middleName)) {
        this->middleName = middleName.trimmed();
    }
    else {
        qWarning() << "Invalid middle name";
    }
}
void Contact::setAddress(const QString& address) {
    this->address = address;
}
void Contact::setBirthDate(const QDate& birthDate) {
    if (validateBirthDate(birthDate)) {
        this->birthDate = birthDate;
    }
    else {
        qWarning() << "Invalid birth date";
    }
}
void Contact::setEmail(const QString& email) {
    if (validateEmail(email)) {
        this->email = email.trimmed();
    }
    else {
        qWarning() << "Invalid email";
    }
}
void Contact::setPhoneNumbers(const QList<QString>& phoneNumbers) {
    this->phoneNumbers.clear();
    for (const auto& number : phoneNumbers) {
        if (validatePhoneNumber(number)) {
            this->phoneNumbers.append(number);
        }
        else {
            qWarning() << "Invalid phone number" << number;
        }
    }
}

//Change number
void Contact::addPhoneNumber(const QString& phoneNumber) {
    if (validatePhoneNumber(phoneNumber)) {
        this->phoneNumbers.append(phoneNumber);
    }
    else {
        qWarning() << "Invalid phone number" << phoneNumber;
    }
}
void Contact::removePhoneNumber(const QString& phoneNumber) {
    this->phoneNumbers.removeAll(phoneNumber);
}

//Main Validation
bool Contact::isValid() const {
    return validateName(firstName) && validateName(lastName) && validateName(middleName) &&
        validateEmail(email) && validateBirthDate(birthDate);
}
bool Contact::validateName(const QString& name) const {
    if (!name.isEmpty()) {
        QRegularExpression regex(QString(R"(^[A-Za-zА-Яа-я][A-Za-zА-Яа-я0-9\s-]*[A-Za-zА-Яа-я0-9]$)"));
        return regex.match(name).hasMatch();
    }
    else return true;
}
bool Contact::validatePhoneNumber(const QString& phoneNumber) const {
    QRegularExpression regex("^(?:\\+7|8)?[\\s(]?(\\d{3})[\\s)]?(\\d{3})[\\s-]?(\\d{2})[\\s-]?(\\d{2})$");
    return regex.match(phoneNumber).hasMatch();
}
bool Contact::validateEmail(const QString& email) const {
    if (!email.isEmpty()) {
        QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        return regex.match(email).hasMatch();
    }
    else return true;
}
bool Contact::validateBirthDate(const QDate& birthDate) const {
    return birthDate < QDate::currentDate();
}

//Operators
bool Contact::operator==(const Contact& other) const {
    return this->id == other.id;
}
QDebug operator<<(QDebug dbg, const Contact& contact) {
    dbg.nospace() << "Contact(id: " << contact.id << ", firstName: " << contact.firstName
        << ", lastName: " << contact.lastName << ", middleName: " << contact.middleName
        << ", address: " << contact.address << ", birthDate: " << contact.birthDate
        << ", email: " << contact.email << ", phoneNumbers: " << contact.phoneNumbers << ")";
    return dbg.space();
}


// Copy
Contact& Contact::operator=(const Contact& other) {
    qDebug() << "Contact::operator= (copy assignment)";
    if (this == &other)
        return *this;

    firstName = other.firstName;
    lastName = other.lastName;
    middleName = other.middleName;
    address = other.address;
    birthDate = other.birthDate;
    email = other.email;
    phoneNumbers = other.phoneNumbers;

    return *this;
}
// Move
Contact& Contact::operator=(Contact&& other) noexcept {
    qDebug() << "Contact::operator= (move assignment)";
    if (this == &other)
        return *this;

    firstName = std::move(other.firstName);
    lastName = std::move(other.lastName);
    middleName = std::move(other.middleName);
    address = std::move(other.address);
    birthDate = std::move(other.birthDate);
    email = std::move(other.email);
    phoneNumbers = std::move(other.phoneNumbers);

    return *this;
}

// Write in file
void Contact::serialize(QDataStream& stream) const {
    stream << id;
    stream << firstName;
    stream << lastName;
    stream << middleName;
    stream << address;
    stream << birthDate.year() << birthDate.month() << birthDate.day();//Сериализация QDate
    stream << email;
    stream << phoneNumbers.size();
    for (const QString& phoneNumber : phoneNumbers) {
        stream << phoneNumber;
    }
}
// Write from file
void Contact::deserialize(QDataStream& stream)
{
    stream >> id;
    stream >> firstName;
    stream >> lastName;
    stream >> middleName;
    stream >> address;
    int year, month, day;
    stream >> year >> month >> day; // Десериализация QDate
    birthDate.setDate(year, month, day);
    stream >> email;

    int phoneNumbersSize;
    stream >> phoneNumbersSize;
    phoneNumbers.clear();
    for (int i = 0; i < phoneNumbersSize; ++i) {
        QString phoneNumber;
        stream >> phoneNumber;
        phoneNumbers.append(phoneNumber);
    }
}

