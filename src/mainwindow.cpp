#include <QtWidgets>
#include "calculations.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lbl_Acc.reset(findChild<QLabel*>("label_acc"));
    lbl_TruePos.reset(findChild<QLabel*>("label_posVir"));
    lbl_FalsePos.reset(findChild<QLabel*>("label_posNoVir"));
    lbl_TrueNeg.reset(findChild<QLabel*>("label_negNoVir"));
    lbl_FalseNeg.reset(findChild<QLabel*>("label_negVir"));

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
    TotalCont[0].reset(tableWidget->item(tableWidget->rowCount() - 1, tableWidget->columnCount() - 3));
    TotalCont[1].reset(tableWidget->item(tableWidget->rowCount() - 1, tableWidget->columnCount() - 2));
    TotalRap[0].reset(tableWidget->item(tableWidget->rowCount() - 3, tableWidget->columnCount() - 1));
    TotalRap[1].reset(tableWidget->item(tableWidget->rowCount() - 2, tableWidget->columnCount() - 1));
    TotalData.reset(tableWidget->item(tableWidget->rowCount() - 1, tableWidget->columnCount() - 1));
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
    // Example to get data on 0,0 (starts from top left)
    // tableWidget->item(0, 0)->data(Qt::DisplayRole).toInt();

    // TODO
    // Display the result of the calculation here
    //lineEdit->setText(QString::number(random() % 101));
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

        TotalCont[x]->setData(Qt::DisplayRole, acc_y);
    }

    int acc_x;
    for (int y = 0; y < tableWidget->rowCount() - 1; ++y)
    {
        acc_x = 0;

        for (int x = 0; x < tableWidget->columnCount() - 1; ++x)
        {
            acc_x += tableWidget->item(y, x)->text().toInt();
        }

        TotalRap[y]->setData(Qt::DisplayRole, acc_x);
    }

    int covPos = tableWidget->item(0, 0)->text().toInt();
    int covNeg = tableWidget->item(1, 0)->text().toInt();
    int freePos = tableWidget->item(0, 1)->text().toInt();
    int freeNeg = tableWidget->item(1, 1)->text().toInt();

    QString PTruePos  = QString::number(int(Calc:: ProbTruePositive(covPos, freePos, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt())  * 100));
    QString PFalsePos = QString::number(int(Calc:: ProbFalsePositive(covPos, freePos, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt()) * 100));
    QString PTrueNeg  = QString::number(int(Calc:: ProbTrueNegative(covNeg, freeNeg, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt())  * 100));
    QString PFalseNeg = QString::number(int(Calc:: ProbFalseNegative(covNeg, freeNeg, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt()) * 100));

    lbl_TruePos->setText(PTruePos+" %");
    lbl_TrueNeg->setText(PTrueNeg+" %");
    lbl_FalsePos->setText(PFalsePos+" %");
    lbl_FalseNeg->setText(PFalseNeg+" %");
    TotalData->setData(Qt::DisplayRole, TotalRap[0]->text().toInt() + TotalRap[1]->text().toInt());
}
