#include "ctable.h"

#include <qdatastream.h>
#include <QRandomGenerator>


static CTable* g_pTable = nullptr;

CTable &table()
{
    if(!g_pTable)
        g_pTable = new CTable;
    return *g_pTable;
}

CTable::CTable()
{
    generate();
}

void CTable::addContact(CContact contact)
{
    m_vContacts.push_back(contact);
}

void CTable::delContact(int idx)
{
    m_vContacts.remove(idx);
}

bool CTable::save(QFile &file)
{
    QDataStream stream(&file);
    stream << m_vContacts;
    return true;
}

bool CTable::load(QFile &file)
{
    QDataStream stream(&file);
    m_vContacts.clear();
    stream >> m_vContacts;
    return true;
}

int randdigit()
{
    return QRandomGenerator::global()->bounded(9);
}
void CTable::generate()
{
    QStringList names = {"Алексей", "Иван", "Матвей", "Петр", "Максим", "Степан", "Ксения", "Анастасия", "Елена"};
    QStringList surnames = {"Коваленко", "Шнайдер", "Репа", "Ройзман", "Смит", "Левченко", "Шмидт", "Ли", "Трунь"};
    foreach(QString name, names)
        foreach(QString surname, surnames)
        {
            QString number = QString("+7(9%1%2)-%3%4%5-%6%7%8%9").arg(randdigit()).arg(randdigit()).arg(randdigit())
                    .arg(randdigit()).arg(randdigit()).arg(randdigit()).arg(randdigit()).arg(randdigit()).arg(randdigit());
            addContact(CContact(name, surname, number));
        }
}
