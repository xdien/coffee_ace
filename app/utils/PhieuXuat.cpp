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

int PhieuXuat::taoPhieu(QString banid)
{
   query.clear();
   QString phieuXuatIndex;
   QScopedPointer<ManageIndex> mnIndex;
   mnIndex.reset(new ManageIndex());
   phieuXuatIndex = mnIndex->getNextIndexCode("PHIEU_XUAT","PC");
   query.prepare("INSERT INTO PHIEU_XUAT "
                 "(PHIEUXUATID,"
                 "BANID,"
                 "CHIEC_KHAU,"
                 "GIO_VAO,"
                 "GIO_RA,"
                 "TONG_TIEN,"
                 "GHI_CHU,"
                 "TRANG_THAI_KHOA,"
                 "NGAY_LAP_HT,"
                 "DA_THANH_TOAN) "
                 "VALUES"
                 "(:phieuXuatID,:banid,:chiecKhau,:gioVao,:gioRa,:tongTien,:ghiChu,:trangThaiKhoa,NOW(),:daThanhToan); "
                 "update BAN set TRANG_THAI_TRONG = false, ID_PHIEU_XUAT_HT=:pcid where BANID = :banid1");
   query.bindValue(":phieuXuatID",phieuXuatIndex);
   query.bindValue(":banid",banid);
   query.bindValue(":chiecKhau",chiecKhau);
   query.bindValue(":gioVao",gioRa);
   query.bindValue(":tongTien",tongTien);
   query.bindValue(":ghiChu",ghiChu);
   query.bindValue(":trangThaiKhoa",trangThaiKhoa);//khoa phieu phong khi khach hang yeu cau
   query.bindValue(":daThanhToan",daThanhToan);
   query.bindValue(":banid1",banid);
   query.bindValue(":pcid",phieuXuatIndex);
   if(query.exec())
       return true;
   else
   {
       qDebug() << "Không thể tạo phiếu xuất "<< query.lastError().text();
       return false;
   }

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

int PhieuXuat::kiemTraThanhToan(QString banid)
{
    query.clear();
    query.prepare("select * from BAN left join PHIEU_XUAT on BAN.ID_PHIEU_XUAT_HT = PHIEU_XUAT.ID_PHIEU_XUAT "
                  "where BAN.BANID = :banid");
    query.bindValue(":banid",banid);
    if(query.exec())
        if(query.next()){
            return query.value("DA_THANH_TOAN").toBool();
        }else{
            qDebug() << "Khong the lay phieu xuat tu ban nay"<< query.lastError().text();
            return false;
        }
    else{
        qDebug() << "Khong the kiem tra duoc trang thai thanh toan, kiem tra lai mang"<< query.lastError().text();
        return false;
    }
}
