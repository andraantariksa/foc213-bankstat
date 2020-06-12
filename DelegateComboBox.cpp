#include "DelegateComboBox.h"

#include <QMetaEnum>

#include "mainwindow.h"

DelegateComboBox::DelegateComboBox(QObject *parent)
: QItemDelegate(parent)
{
}

QWidget *DelegateComboBox::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 0: return new QLineEdit(parent);
    case 1: return createComboBoxFromEnum<BankStatement::Panggilan>(parent, option, index);
    case 2: return createComboBoxFromEnum<BankStatement::Kartu>(parent, option, index);
    case 3: return createComboBoxFromEnum<BankStatement::Blok>(parent, option, index);
    }
    return QItemDelegate::createEditor(parent, option, index);
}

void DelegateComboBox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant data = index.model()->data(index, Qt::EditRole);
    switch (index.column())
    {
    case 0:
        {
            QLineEdit* line_edit = (QLineEdit*)editor;
            line_edit->setText(data.toString());

            break;
        }
    case 1:
    case 2:
    case 3:
        {
            QComboBox* combo_box = (QComboBox*)editor;
            combo_box->setCurrentIndex(combo_box->findText(data.toString()));

            break;
        }
    }
}

void DelegateComboBox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 0:
        {
            auto line_edit = (QLineEdit*)editor;
            QString value = line_edit->text();
            model->setData(index, value, Qt::EditRole);

            break;
        }
    case 1:
    case 2:
    case 3:
        {
            auto combo_box = (QComboBox*)editor;
            int value = combo_box->currentIndex();
            model->setData(index, value, Qt::EditRole);

            break;
        }
    }
}

void DelegateComboBox::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

template<typename T>
QWidget *DelegateComboBox::createComboBoxFromEnum(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto cell = new QComboBox(parent);
    auto meta_enum = QMetaEnum::fromType<T>();
    for (int i = 0; i < meta_enum.keyCount(); ++i)
    {
        cell->addItem(meta_enum.valueToKey(i));
    }
    cell->setCurrentIndex(0);
    return cell;
}
