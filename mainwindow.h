#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ctable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:

private:
    void checkAndEnable();
    int getCurrentRowIdx();

private slots:
    void onAddContact();
    void onEditContact(int row, int column);
    void onEditContact();
    void onDeleteContact();

    void onSave();
    void onLoad();

    void fillTable(QString search = "");

    void on_QTable_itemSelectionChanged();
    void on_QTable_cellClicked(int row, int column);

    void on_QTable_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
