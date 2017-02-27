#include "danhsachchamcongabstractmodel.h"

DanhSachChamCongAbstractModel::DanhSachChamCongAbstractModel(int kyid):
    m_kyid(kyid)
{
    m_kyid= kyid;
    query = new QSqlQuery();
    query->exec("select * from CHAMCONG where KYID = "+QString::number(kyid));
}

DanhSachChamCongAbstractModel::~DanhSachChamCongAbstractModel()
{
    query->clear();
    delete query;
}

QVariant DanhSachChamCongAbstractModel::data(const QModelIndex &index, int role) const
{
    int vitri = index.row();
    //qDebug() << index;
    switch (role) {//xac dinh quy dinh dang yeu cau
    case Qt::DisplayRole:
    {
        return query->value(index.row());
        break;
    }
    case Qt::BackgroundRole://set mau
    {
        QColor color = calculateColorForRow(vitri);
        return QBrush(color);
        break;
    }
    default:
        return QVariant::Invalid;
        break;
    }

}

QVariant DanhSachChamCongAbstractModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    /*if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case 0:
            return STR_NGAY;
            break;
        case 1:
            return STR_CHINH;
            break;
        case 2:
            return STR_NGOAI_GIO;
            break;
        case 3:
            return STR_HE_SO;
            break;
        default:
            break;
        }
    }
    */
    return QVariant();
}

int DanhSachChamCongAbstractModel::rowCount(const QModelIndex &parent) const
{
    return query->size();
}

int DanhSachChamCongAbstractModel::columnCount(const QModelIndex &parent) const
{
    return query->record().count();
}

QColor DanhSachChamCongAbstractModel::calculateColorForRow(int row) const
{
    return Qt::white;
}

