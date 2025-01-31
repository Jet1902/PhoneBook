#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qinputdialog.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->QTable->setContextMenuPolicy(Qt::CustomContextMenu);

    // Добавление контакта
//    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddContact()));
    connect(ui->actionAddContact, SIGNAL(triggered()), this, SLOT(onAddContact()));

    // Редактирование контакта
//    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(onEditContact()));
    connect(ui->QTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onEditContact(int, int)));
    connect(ui->actionEditContact, SIGNAL(triggered()), this, SLOT(onEditContact()));

    // Удаление контакта
//    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteContact()));
    connect(ui->actionDeleteContact, SIGNAL(triggered()), this, SLOT(onDeleteContact()));

    // Сохранение файла
//    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSave()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));

    //Загрузка файла
//    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(onLoad()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(onLoad()));

    //Строка поиска
    connect(ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(fillTable(QString)));

    fillTable();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTable(QString search)
{
    int currentIdx = getCurrentRowIdx();
    int currentRow = -1;
    ui->QTable->clearContents();
    ui->QTable->setRowCount(0);
//    ui->QTable->setRowCount(table().numContacts());
    for(int i = 0; i < table().numContacts(); ++i)
    {
        CContact contact = table().contactByIdx(i);
        if(!contact.name().contains(search, Qt::CaseInsensitive) && !contact.surname().contains(search, Qt::CaseInsensitive) && !contact.number().contains(search, Qt::CaseInsensitive))
            continue;
        int rowIdx = ui->QTable->rowCount();
        ui->QTable->insertRow(rowIdx);
        QTableWidgetItem* newItem = new QTableWidgetItem(contact.name());
        newItem->setData(Qt::UserRole, i);
        if(i == currentIdx)
            currentRow = rowIdx;
        ui->QTable->setItem(rowIdx, 0, newItem);
        ui->QTable->setItem(rowIdx, 1, new QTableWidgetItem(contact.surname()));
        ui->QTable->setItem(rowIdx, 2, new QTableWidgetItem(contact.number()));
    }
    ui->QTable->selectRow(currentRow);
    checkAndEnable();
}

void MainWindow::checkAndEnable()
{
//    ui->editButton->setDisabled(ui->QTable->currentRow() == -1);
//    ui->deleteButton->setDisabled(ui->QTable->currentRow() == -1);
    ui->actionDeleteContact->setDisabled(ui->QTable->currentRow() == -1);
    ui->actionEditContact->setDisabled(ui->QTable->currentRow() == -1);
}

int MainWindow::getCurrentRowIdx()
{
    if(ui->QTable->currentRow() == -1)
        return -1;
    return ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt();
}

void MainWindow::onAddContact()
{
    QInputDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
        table().addContact(dlg.getData());

    fillTable(ui->searchLine->text());
}

void MainWindow::onEditContact(int row, int column)
{
    QInputDialog dlg(this);
    dlg.setData(table().contactByIdx(row));
    if(dlg.exec() == QDialog::Accepted)
    {
        table().delContact(row);
        table().addContact(dlg.getData());
    }
    fillTable(ui->searchLine->text());
}

void MainWindow::onEditContact()
{
    if(ui->QTable->currentRow() != -1)
    {
        QInputDialog dlg(this);
        dlg.setData(table().contactByIdx(ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt()));
        if(dlg.exec() == QDialog::Accepted)
        {
            table().contactByIdx(ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt()).setName(dlg.getData().name());
            table().contactByIdx(ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt()).setSurname(dlg.getData().surname());
            table().contactByIdx(ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt()).setNumber(dlg.getData().number());
        }
        fillTable(ui->searchLine->text());
    }
}

void MainWindow::onDeleteContact()
{
    if(ui->QTable->currentRow() != -1)
    {
        table().delContact(ui->QTable->item(ui->QTable->currentRow(), 0)->data(Qt::UserRole).toInt());
        fillTable(ui->searchLine->text());
    }
}

void MainWindow::onSave()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить книгу"), "", tr("Книга (*.pb)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    table().save(file);
    file.close();
}

void MainWindow::onLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Загрузить книгу"), "", tr("Книгу (*.pb)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
        return;
    table().load(file);
    file.close();

    fillTable(ui->searchLine->text());
}

void MainWindow::on_QTable_itemSelectionChanged()
{
    checkAndEnable();
}

//void MainWindow::on_QTable_cellDoubleClicked(int row, int column)
//{

//}


void MainWindow::on_QTable_cellClicked(int row, int column)
{
    checkAndEnable();
}

void MainWindow::on_QTable_customContextMenuRequested(const QPoint &pos)
{
    QMenu* itemMenu = new QMenu(ui->QTable);
    itemMenu->addAction(ui->actionEditContact);
    itemMenu->addAction(ui->actionDeleteContact);
    itemMenu->popup(ui->QTable->mapToGlobal(pos));
}
