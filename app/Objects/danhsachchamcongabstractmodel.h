#ifndef DANHSACHCHAMCONGABSTRACTMODEL_H
#define DANHSACHCHAMCONGABSTRACTMODEL_H

#include <QAbstractTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QColor>
#include <QBrush>
#include <QDebug>
class DanhSachChamCongAbstractModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DanhSachChamCongAbstractModel(int kyid);
    ~DanhSachChamCongAbstractModel();
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    //cho phep sua du lieu
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    QSqlQuery *query;
    int m_kyid;
    QColor calculateColorForRow(int row) const;
};

#endif // DANHSACHCHAMCONGABSTRACTMODEL_H
