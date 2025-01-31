#include "ccontact.h"

QDataStream &operator >>(QDataStream &stream, CContact &contact)
{
    QString tempName;
    stream >> tempName;
    contact.setName(tempName);
    QString tempSurname;
    stream >> tempSurname;
    contact.setSurname(tempSurname);
    QString tempNumber;
    stream >> tempNumber;
    contact.setNumber(tempNumber);
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const CContact &contact)
{
    stream << contact.name();
    stream << contact.surname();
    stream << contact.number();
    return stream;
}
