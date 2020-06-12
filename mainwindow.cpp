#include <QtWidgets>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "DelegateComboBox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO
    QTableView* table = findChild<QTableView*>("tableView");

    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });
    model.append({ "Test", BankStatement::Panggilan::Cukup, BankStatement::Kartu::Prabayar, BankStatement::Blok::Sedang, false });

    auto delegate_combobox = new DelegateComboBox();
    table->setItemDelegate(delegate_combobox);
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
