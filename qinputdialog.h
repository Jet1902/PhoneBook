#ifndef QINPUTDIALOG_H
#define QINPUTDIALOG_H

#include <QDialog>
#include "ccontact.h"

namespace Ui {
class QInputDialog;
}

class QInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QInputDialog(QWidget *parent = nullptr);
    ~QInputDialog();

    CContact getData();
    void setData(const CContact& contact);


private slots:
    void checkAndEnable();

private:
    Ui::QInputDialog *ui;
};

#endif // QINPUTDIALOG_H
