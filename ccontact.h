#ifndef CCONTACT_H
#define CCONTACT_H

#include <QString>



class CContact
{
public:
    CContact(){}
    CContact(QString name, QString surname, QString number) : m_name(name), m_surname(surname), m_number(number){}

    QString name() const
        { return m_name; }
    void setName(const QString &value)
        { m_name = value; }
    QString surname() const
        { return m_surname; }
    void setSurname(const QString &value)
        { m_surname = value; }
    QString number() const
        { return m_number; }
    void setNumber(const QString &value)
        { m_number = value; }

private:
    QString m_name;
    QString m_surname;
    QString m_number;
};

QDataStream& operator >>(QDataStream& stream, CContact& contact);
QDataStream& operator <<(QDataStream& stream, const CContact& contact);

#endif // CCONTACT_H
