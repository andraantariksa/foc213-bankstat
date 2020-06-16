#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClose_triggered();
    void on_tableWidget_main_itemChanged(QTableWidgetItem *item);

private:
    void populateTotal();
    void calcProbs();

    std::unique_ptr<QTableWidgetItem> TotalCont[2], TotalRap[2], TotalData; // instant use for "total" cells
    std::unique_ptr<QTableWidget> tableWidget_main;
    std::unique_ptr<QLabel> label_acc, label_truePos, label_falsePos, label_trueNeg, label_falseNeg;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
