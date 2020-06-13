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
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    void populateTotal();
    std::unique_ptr<QTableWidget> tableWidget;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H