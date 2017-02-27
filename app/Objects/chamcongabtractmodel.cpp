#include "chamcongabtractmodel.h"

ChamCongAbtractModel::ChamCongAbtractModel(ChamCong *danhSachNgay, QObject *parent) :
    QAbstractTableModel(parent)
{
   chamCong = danhSachNgay;
}

ChamCongAbtractModel::~ChamCongAbtractModel()
{
    qDebug() << "xoa ChamCongAbtractModel";
}

QVariant ChamCongAbtractModel::data(const QModelIndex &index, int role) const
{
    int vitri = index.row();
    switch (role) {//xac dinh quy dinh dang yeu cau
    case Qt::DisplayRole:
    {
        switch (index.column()) {
        case 0: //ngay N
            return chamCong->danhSachNgay.at(vitri)->value(NGAY).toString();
            break;
        case 1: //Cong CONG
            return chamCong->danhSachNgay.at(vitri)->value(NGAYCONG).toString();
            if(chamCong)
                break;
        case 2://NGOAI GIO NG
            return chamCong->danhSachNgay.at(vitri)->value(NGOAIGIO).toString();
            break;
        case 3://NGOAI GIO TONG
            return chamCong->danhSachNgay.at(vitri)->value(TONGCONG).toDouble(0);
            break;
        default:
            return QVariant();
            break;
        }
    }
        break;
    case Qt::BackgroundRole:
    {
        QColor color = calculateColorForRow(vitri);
        return QBrush(color);
    }
        break;
    default:
        return QVariant::Invalid;
        break;
    }

}

QVariant ChamCongAbtractModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
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

    return QVariant();
}

int ChamCongAbtractModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return chamCong->danhSachNgay.size();
}

int ChamCongAbtractModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

Qt::ItemFlags ChamCongAbtractModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool ChamCongAbtractModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (index.isValid() && role == Qt::EditRole) {
        qDebug() << "gia tri truoc: "<< index.data().toString();
        qDebug() << "gia tri sau: " << index.row();
        int vitri = index.row();
        switch (index.column()) {
        case 0:
            chamCong->danhSachNgay.at(vitri)->insert(NGAY,value.toString());
            break;
        case 1:
        {
            setKyHieu(vitri, value.toString());
            emit thayDoiHeSo(vitri);
        }
            break;
        case 2:
            chamCong->danhSachNgay.at(vitri)->insert(NGOAIGIO,value.toString());
            emit thayDoiHeSo(vitri);
            break;
        case 3:{
            chamCong->danhSachNgay.at(vitri)->insert(TONGCONG,value.toFloat(0));
            emit thayDoiHeSo(vitri);
        }
            break;
        default:
            break;
        }

        return true;
    }

    return false;
}

void ChamCongAbtractModel::setKyHieu(int rowIndex, const QString value)
{
    if(value != ""){//neu = rong thi set he so = 0
        chamCong->danhSachNgay.at(rowIndex)->insert(NGAYCONG,value);
        //co thay doi he so, kiem tra he so neu # 1 vs 0.5
        if(value.right(1) == "2"){
            chamCong->danhSachNgay.at(rowIndex)->insert(TONGCONG,0.5);
        }else{
            chamCong->danhSachNgay.at(rowIndex)->insert(TONGCONG,1);
        }
    }else{
        chamCong->danhSachNgay.at(rowIndex)->insert(TONGCONG,0.5);
    }
}

QColor ChamCongAbtractModel::calculateColorForRow(int row) const
{
    if(chamCong->danhSachNgay.at(row)->value(LE).toInt() == 2) //ngay tb hoi do
        return QColor::fromRgb(204, 153, 255);
    if(chamCong->danhSachNgay.at(row)->value(LE).toInt() == 1)// ngay le hoi xanh
        return QColor::fromRgb(102, 153, 255);
    if(chamCong->danhSachNgay.at(row)->value(THU).toInt(0) == 7)//ngay chu nhat
        return QColor::fromRgb(240, 168, 204);
    return Qt::white;
}



