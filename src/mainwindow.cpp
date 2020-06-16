#include <QtWidgets>
#include "calculations.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label_acc.reset(findChild<QLabel*>("label_acc"));
    label_truePos.reset(findChild<QLabel*>("label_posVir"));
    label_falsePos.reset(findChild<QLabel*>("label_posNoVir"));
    label_trueNeg.reset(findChild<QLabel*>("label_negNoVir"));
    label_falseNeg.reset(findChild<QLabel*>("label_negVir"));
    tableWidget_main.reset(findChild<QTableWidget*>("tableWidget_main"));

    tableWidget_main->insertRow(tableWidget_main->rowCount());
    tableWidget_main->insertColumn(tableWidget_main->columnCount());
    tableWidget_main->setVerticalHeaderItem(tableWidget_main->rowCount() - 1, new QTableWidgetItem("Total"));
    tableWidget_main->setHorizontalHeaderItem(tableWidget_main->columnCount() - 1, new QTableWidgetItem("Total"));

    tableWidget_main->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int x = 0; x < tableWidget_main->columnCount(); ++x)
    {
        for (int y = 0; y < tableWidget_main->rowCount(); ++y)
        {
            auto temp = new QTableWidgetItem;
            temp->setData(Qt::DisplayRole, 0);
            // If on bottom or right edge
            if (x == tableWidget_main->columnCount() - 1 || y == tableWidget_main->rowCount() - 1)
            {
                temp->setFlags(Qt::NoItemFlags);
            }
            tableWidget_main->setItem(y, x, temp);
        }
    }
    tableWidget_main->setEditTriggers(QAbstractItemView::AllEditTriggers);
    TotalCont[0].reset(tableWidget_main->item(tableWidget_main->rowCount() - 1, tableWidget_main->columnCount() - 3));
    TotalCont[1].reset(tableWidget_main->item(tableWidget_main->rowCount() - 1, tableWidget_main->columnCount() - 2));
    TotalRap[0].reset(tableWidget_main->item(tableWidget_main->rowCount() - 3, tableWidget_main->columnCount() - 1));
    TotalRap[1].reset(tableWidget_main->item(tableWidget_main->rowCount() - 2, tableWidget_main->columnCount() - 1));
    TotalData.reset(tableWidget_main->item(tableWidget_main->rowCount() - 1, tableWidget_main->columnCount() - 1));
}

MainWindow::~MainWindow()
{
    // Vibe check for the pointer
    label_acc.~unique_ptr();
    label_truePos.~unique_ptr();
    label_falsePos.~unique_ptr();
    label_trueNeg.~unique_ptr();
    label_falseNeg.~unique_ptr();
    TotalData.~unique_ptr();
    TotalCont[0].~unique_ptr();
    TotalCont[1].~unique_ptr();
    TotalRap[0].~unique_ptr();
    TotalRap[1].~unique_ptr();
    tableWidget_main.~unique_ptr();

    delete ui;
}


void MainWindow::on_actionClose_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_tableWidget_main_itemChanged(QTableWidgetItem *item)
{
    if (tableWidget_main->editTriggers() == QAbstractItemView::AllEditTriggers)
    {
        populateTotal();
        calcProbs();
    }
}

void MainWindow::populateTotal()
{
    int accY;
    for (int x = 0; x < tableWidget_main->columnCount() - 1; ++x)
    {
        accY = 0;
        for (int y = 0; y < tableWidget_main->rowCount() - 1; ++y)
        {
            accY += tableWidget_main->item(y, x)->text().toInt();
        }

        TotalCont[x]->setData(Qt::DisplayRole, accY);
    }

    int accX;
    for (int y = 0; y < tableWidget_main->rowCount() - 1; ++y)
    {
        accX = 0;

        for (int x = 0; x < tableWidget_main->columnCount() - 1; ++x)
        {
            accX += tableWidget_main->item(y, x)->text().toInt();
        }

        TotalRap[y]->setData(Qt::DisplayRole, accX);
    }

    TotalData->setData(Qt::DisplayRole, TotalRap[0]->text().toInt() + TotalRap[1]->text().toInt());
}

// Calculate probabilities and test accuracy
void MainWindow::calcProbs() {
    int covPos = tableWidget_main->item(0, 0)->text().toInt();
    int covNeg = tableWidget_main->item(1, 0)->text().toInt();
    int freePos = tableWidget_main->item(0, 1)->text().toInt();
    int freeNeg = tableWidget_main->item(1, 1)->text().toInt();

    double pTruePos  = Calc::ProbTruePositive(covPos, freePos, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt());
    double pTrueNeg  = Calc::ProbTrueNegative(covNeg, freeNeg, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt());
    double pFalsePos = Calc::ProbFalsePositive(covPos, freePos, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt());
    double pFalseNeg = Calc::ProbFalseNegative(covNeg, freeNeg, TotalCont[0]->text().toInt(), TotalCont[1]->text().toInt());
    double acc = (pTruePos + pTrueNeg) / 2.0;

    // Check zero division
    if (acc > 0)
    {
        label_acc->setText(QString::number(acc * 100.0) + " %");
    }
    else
    {
        label_acc->setText("- %");
    }

    if (pTruePos > 0)
    {
        label_truePos->setText(QString::number(pTruePos * 100.0) + " %");
    }
    else
    {
        label_truePos->setText("- %");
    }

    if (pTrueNeg > 0)
    {
        label_trueNeg->setText(QString::number(pTrueNeg * 100.0) + " %");
    }
    else
    {
        label_trueNeg->setText("- %");
    }

    if (pFalsePos > 0)
    {
        label_falsePos->setText(QString::number(pFalsePos * 100.0) + " %");
    }
    else
    {
        label_falsePos->setText("- %");
    }

    if (pFalseNeg > 0)
    {
        label_falseNeg->setText(QString::number(pFalseNeg * 100.0) + " %");
    }
    else
    {
        label_falseNeg->setText("- %");
    }
}
