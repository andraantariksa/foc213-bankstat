#include <QtWidgets>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableView* table = findChild<QTableView*>("tableView");

    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });

    table->setModel(&model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionClose_triggered()
{
    QCoreApplication::quit();
}
