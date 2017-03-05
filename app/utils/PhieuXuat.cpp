/***********************************************************************
 * Module:  PhieuXuat.cpp
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:52:36 AM
 * Purpose: Implementation of the class PhieuXuat
 ***********************************************************************/

#include "ChiTietPhieuXuat.h"
#include "PhieuXuat.h"
#include <QDebug>
const char* PhieuXuat::COLUMN_NAMES[] = {
    /*"PHIEUXUATID","BANID","CHIEC_KHAU",
    "GIO_VAO","GIO_RA","TONG_TIEN","GHI_CHU",
    "TRANG_THAI_KHOA","TRANG_THAI_KHOA","NGAY_LAP_HT",*/
    "BANID",
    "TEN",
    "TRANG_THAI_TRONG",
    NULL
};
const char* PhieuXuat::SQL_SELECT =
    "SELECT * from BAN";
////////////////////////////////////////////////////////////////////////
// Name:       PhieuXuat::taoPhieu()
// Purpose:    Implementation of PhieuXuat::taoPhieu()
// Return:     int
////////////////////////////////////////////////////////////////////////

PhieuXuat::PhieuXuat(QObject *parent):
    QSqlQueryModel(parent)
{
    int idx = 0;

    qDebug() << "Khoi tao phieuXuatModel";
    while( COLUMN_NAMES[idx]) {
        m_roleNames[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    //setRoleNames(roleNames);
    refresh();
}
QHash<int, QByteArray> PhieuXuat::roleNames() const
{
    return m_roleNames;
}
void PhieuXuat::refresh()
{
    this->setQuery(SQL_SELECT);
}

QVariant PhieuXuat::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
        if(role < Qt::UserRole)
        {
            value = QSqlQueryModel::data(index, role);
        }
        else
        {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
        return value;
}

int PhieuXuat::taoPhieu(void)
{
   // TODO : implement

}

////////////////////////////////////////////////////////////////////////
// Name:       PhieuXuat::inPhieu()
// Purpose:    Implementation of PhieuXuat::inPhieu()
// Return:     int
////////////////////////////////////////////////////////////////////////

int PhieuXuat::inPhieu(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       PhieuXuat::chuyenBan()
// Purpose:    Implementation of PhieuXuat::chuyenBan()
// Return:     int
////////////////////////////////////////////////////////////////////////

int PhieuXuat::chuyenBan(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       PhieuXuat::capNhatGhiChu()
// Purpose:    Implementation of PhieuXuat::capNhatGhiChu()
// Return:     int
////////////////////////////////////////////////////////////////////////

int PhieuXuat::capNhatGhiChu(void)
{
   // TODO : implement
}
