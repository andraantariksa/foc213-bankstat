#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BankStatement
{
    Q_GADGET
public:
    enum class Panggilan
    {
        Sedikit,
        Sedang,
        Cukup,
        Banyak,
    };
    Q_ENUM(Panggilan)

    enum class Kartu
    {
        Prabayar,
        Pascabayar,
    };
    Q_ENUM(Kartu)

    enum class Blok
    {
        Rendah,
        Sedang,
        Tinggi,
    };
    Q_ENUM(Blok)

    QString name;
    Panggilan panggilan;
    Kartu kartu;
    Blok blok;
    bool bonus;
};
Q_DECLARE_METATYPE(BankStatement::Panggilan)
Q_DECLARE_METATYPE(BankStatement::Kartu)
Q_DECLARE_METATYPE(BankStatement::Blok)

class BankStatementModel: public QAbstractTableModel
{
private:
    QList<BankStatement> data_list;
public:
    int rowCount(const QModelIndex &) const override {
        return data_list.count();
    }
    int columnCount(const QModelIndex &) const override
    {
        return 5;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        if (role != Qt::DisplayRole && role != Qt::EditRole) return {};

        const auto & bank_statement = data_list[index.row()];

        switch (index.column()) {
        case 0: return bank_statement.name;
        case 1: return QVariant::fromValue(bank_statement.panggilan).toString();
        case 2: return QVariant::fromValue(bank_statement.kartu).toString();
        case 3: return QVariant::fromValue(bank_statement.blok).toString();
        case 4: return bank_statement.bonus;
        default: return {};
        };
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};

        switch (section) {
        case 0: return "Name";
        case 1: return "Panggilan";
        case 2: return "Jenis Kartu";
        case 3: return "Blok";
        case 4: return "Bonus";
        default: return {};
        }
    }

    void append(const BankStatement & bank_statement) {
        beginInsertRows({}, data_list.count(), data_list.count());

        data_list.append(bank_statement);

        endInsertRows();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;

    BankStatementModel model;
};
#endif // MAINWINDOW_H
