#ifndef CTABLE_H
#define CTABLE_H

#include <QString>
#include <QVector>
#include <QFile>
#include "ccontact.h"

class CTable
{
public:
    typedef QVector<CContact> QContactVector;

public:
    CTable();
    QContactVector contacts()
        { return m_vContacts; }

    int numContacts()
        { return m_vContacts.size(); }
    CContact contactByIdx(int idx)
        { return m_vContacts[idx]; }
    void addContact(CContact contact);
    void delContact(int idx);

    bool save(QFile& file);
    bool load(QFile& file);

protected:
    void generate();

private:
    QContactVector m_vContacts;
};

CTable& table();

#endif // CTABLE_H
