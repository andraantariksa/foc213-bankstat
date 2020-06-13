#include <QtWidgets>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "DelegateComboBox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tableWidget.reset(findChild<QTableWidget*>("tableWidget"));
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->insertColumn(tableWidget->columnCount());
    tableWidget->setVerticalHeaderItem(tableWidget->rowCount() - 1, new QTableWidgetItem("Total"));
    tableWidget->setHorizontalHeaderItem(tableWidget->columnCount() - 1, new QTableWidgetItem("Total"));

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int x = 0; x < tableWidget->columnCount(); ++x)
    {
        for (int y = 0; y < tableWidget->rowCount(); ++y)
        {
            auto temp = new QTableWidgetItem;
            temp->setData(Qt::DisplayRole, 0);
            // If on bottom or right edge
            if (x == tableWidget->columnCount() - 1 || y == tableWidget->rowCount() - 1)
            {
                temp->setFlags(Qt::NoItemFlags);
            }
            tableWidget->setItem(y, x, temp);
        }
    }
    tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionClose_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if (tableWidget->editTriggers() == QAbstractItemView::AllEditTriggers)
    {
        populateTotal();
    }

    // TODO
    // Calculation
}

void MainWindow::populateTotal()
{
    int acc_y;
    for (int x = 0; x < tableWidget->columnCount() - 1; ++x)
    {
        acc_y = 0;
        for (int y = 0; y < tableWidget->rowCount() - 1; ++y)
        {
            acc_y += tableWidget->item(y, x)->text().toInt();
        }

        tableWidget->item(tableWidget->rowCount() - 1, x)->setData(Qt::DisplayRole, acc_y);
    }

    int acc_x;
    for (int y = 0; y < tableWidget->rowCount() - 1; ++y)
    {
        acc_x = 0;

        for (int x = 0; x < tableWidget->columnCount() - 1; ++x)
        {
            acc_x += tableWidget->item(y, x)->text().toInt();
        }

        tableWidget->item(y, tableWidget->columnCount() - 1)->setData(Qt::DisplayRole, acc_x);
    }
}
