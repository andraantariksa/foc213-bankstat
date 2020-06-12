#ifndef DELEGATECOMBOBOX_H
#define DELEGATECOMBOBOX_H

#include <QObject>
#include <QItemDelegate>
#include <QModelIndex>
#include <QComboBox>

class DelegateComboBox : public QItemDelegate
{
public:
    explicit DelegateComboBox(QObject *parent = 0);

    QWidget* createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    template<typename T>
    QWidget* createComboBoxFromEnum(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATECOMBOBOX_H
