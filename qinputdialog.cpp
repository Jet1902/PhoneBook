#include "qinputdialog.h"
#include "ui_qinputdialog.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>

QInputDialog::QInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QInputDialog)
{
    ui->setupUi(this);
    connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkAndEnable()));
    connect(ui->surnameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkAndEnable()));
    connect(ui->numberLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkAndEnable()));
    checkAndEnable();
}

CContact QInputDialog::getData()
{
    return CContact(ui->nameLineEdit->text(), ui->surnameLineEdit->text(), ui->numberLineEdit->text());
}

QInputDialog::~QInputDialog()
{
    delete ui;
}

void QInputDialog::setData(const CContact &contact)
{
    ui->nameLineEdit->setText(contact.name());
    ui->surnameLineEdit->setText(contact.surname());
    ui->numberLineEdit->setText(contact.number());
}

void QInputDialog::checkAndEnable()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(ui->nameLineEdit->text().isEmpty() ||
                                                             ui->surnameLineEdit->text().isEmpty() ||
                                                             ui->numberLineEdit->text().size() != 16);
}

