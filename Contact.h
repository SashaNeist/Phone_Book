#pragma once

#include <QString>
#include <QList>
#include <QDate>

class Contact {
private:
    static int nextId;
    int id;
    QString firstName; // Name
    QString lastName; // SerName
    QString middleName; // PatronumicName
    QString address; // Home address
    QDate birthDate; // Date of birth
    QString email; // e-mail
    QList<QString> phoneNumbers; // List of phone numbers(personal, home, work)

    //Validation methods
    bool validateName(const QString& name) const;
    bool validatePhoneNumber(const QString& phoneNumber) const;
    bool validateEmail(const QString& email) const;
    bool validateBirthDate(const QDate& birthDate) const;

public:
    // Constructors
    Contact();
    Contact(const QString& firstName, const QString& lastName, const QList<QString>& phoneNumbers);
    Contact(const QString& firstName, const QString& lastName, const QString& middleName,
        const QString& address, const QDate& birthDate, const QString& email,
        const QList<QString>& phoneNumbers);
    // Copy constructor
    Contact(const Contact& other);

    // Getters
    int getId() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getMiddleName() const;
    QString getAddress() const;
    QDate getBirthDate() const;
    QString getEmail() const;
    QList<QString> getPhoneNumbers() const;

    // Setters
    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setMiddleName(const QString& middleName);
    void setAddress(const QString& address);
    void setBirthDate(const QDate& birthDate);
    void setEmail(const QString& email);
    void setPhoneNumbers(const QList<QString>& phoneNumbers);

    // Adding new number 
    void addPhoneNumber(const QString& phoneNumber);

    // Delete number
    void removePhoneNumber(const QString& phoneNumber);

    // Check data valid
    bool isValid() const;

    // Comparison operator
    bool operator==(const Contact& other) const;

    // in|out operators
    friend QDebug operator<<(QDebug dbg, const Contact& contact);

  
    Contact& operator=(const Contact& other); // Copy operator
    Contact& operator=(Contact&& other) noexcept; // Move operator

    // Work with files methods
    void serialize(QDataStream& stream) const;
    void deserialize(QDataStream& stream);

};
