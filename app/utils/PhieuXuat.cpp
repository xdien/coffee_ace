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
    "BANID",
    "TEN",
    "TRANG_THAI_TRONG",
    "CHIEC_KHAU",
    "GIO_VAO",
    "GIO_RA",
    "TONG_TIEN",
    "GHI_CHU",
    "TRANG_THAI_KHOA",
    "PHIEUXUATID",
    NULL
};
const char* PhieuXuat::SQL_SELECT =
    "SELECT BAN.BANID,TEN,TRANG_THAI_TRONG,CHIEC_KHAU,"
        "GIO_VAO,GIO_RA,TONG_TIEN,GHI_CHU,"
        "TRANG_THAI_KHOA,ID_PHIEU_XUAT_HT from BAN left join PHIEU_XUAT on PHIEU_XUAT.PHIEUXUATID = ID_PHIEU_XUAT_HT";
////////////////////////////////////////////////////////////////////////
// Name:       PhieuXuat::taoPhieu()
// Purpose:    Implementation of PhieuXuat::taoPhieu()
// Return:     int
////////////////////////////////////////////////////////////////////////

PhieuXuat::PhieuXuat(QObject *parent):
    QSqlQueryModel(parent)
{
    int idx = 0;
    printer = new QPrinter();
    qDebug() << "Khoi tao phieuXuatModel";
    while( COLUMN_NAMES[idx]) {
        m_roleNames[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    //setRoleNames(roleNames);
    refresh();
}

PhieuXuat::~PhieuXuat()
{
    delete report;
    delete printer;
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
   phieuXuatID = phieuXuatIndex;
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
   if(query.exec()){
       return true;
   }
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

void PhieuXuat::layThongTinPhieu(QString pcid)
{
    query.clear();
    if(query.exec("select PHIEUXUATID,BAN.BANID as BANID,CHIEC_KHAU,GIO_VAO,GIO_RA,TONG_TIEN,GHI_CHU,"
                  "TRA_TRUOC,BAN.TEN as TEN from PHIEU_XUAT left join BAN on BAN.BANID = PHIEU_XUAT.BANID "
                  "where PHIEUXUATID = '"+pcid+"'"))
    {
        if(query.next()){
            tongTien = query.value("TONG_TIEN").toInt();
            traTruoc= query.value("TRA_TRUOC").toInt();
            tenBan = query.value("TEN").toString();
            gioVao = query.value("GIO_VAO").toString();
        }else{
            qDebug() << "Khong co thong tin tra ve: "<< query.lastError().text();
        }
    }else{
        qDebug() << "Khong the chay query lay thong tin: "<< query.lastError().text();
    }
}
///
/// \brief PhieuXuat::roiBan update da thanh toan = true, gio roi ban, trang thai ban trong, tong_tien
/// trang thai phieu xuat
/// \param banid
/// \return
///
bool PhieuXuat::roiBan(const QString pcid,bool khongUpDateTongTien = false)
{
    query.clear();
    if(!khongUpDateTongTien){
        query.prepare("update PHIEU_XUAT set DA_THANH_TOAN = true,"
                      "GIO_RA = NOW(),TONG_TIEN=:tongTien,CHIEC_KHAU =:chiecKhau where PHIEUXUATID =:pcid; "
                      "update BAN set ID_PHIEU_XUAT_HT = '',TRANG_THAI_TRONG=true where ID_PHIEU_XUAT_HT = :idpc1");
        query.bindValue(":tongTien",tongTien);
        query.bindValue(":chiecKhau",chiecKhau);
    }else{
        query.prepare("update PHIEU_XUAT set DA_THANH_TOAN = true,"
                      "GIO_RA = NOW() where PHIEUXUATID =:pcid; "
                      "update BAN set ID_PHIEU_XUAT_HT = '',TRANG_THAI_TRONG=true where ID_PHIEU_XUAT_HT = :idpc1");
    }
    query.bindValue(":pcid",pcid);
    query.bindValue(":idpc1",pcid);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Khong the roi ban"<< query.lastError().text();
        return false;

    }
}

bool PhieuXuat::capNhatSoTienTraTruoc(QString pcid)
{
    query.clear();
    query.prepare("update PHIEU_XUAT set TRA_TRUOC = :traTruoc where PHIEUXUATID = :pcid");
    query.bindValue(":traTruoc",traTruoc);
    query.bindValue(":pcid",pcid);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Khong the cap nhat tra truoc "<< query.lastError().text();
        return false;
    }
}

void PhieuXuat::xemBill(const QString pcid)
{
    this->phieuXuatID = pcid;
    QScopedPointer<QSqlQueryModel> hocThuViecModel;
    hocThuViecModel.reset(new QSqlQueryModel());
    hocThuViecModel->setQuery("SELECT * from CHI_TIET_PHIEU_XUAT "
                              " where PHIEUXUATID = '"+pcid+"'");
    layThongTinPhieu(pcid);
    if(report.isNull()){
        report = new LimeReport::ReportEngine();
        report->loadFromFile(QApplication::applicationDirPath()+"/reports/bill_coffee.lrxml");
        report->dataManager()->removeModel("chitietpc");
        report->dataManager()->addModel("chitietpc",hocThuViecModel.data(),false);
        report->dataManager()->setReportVariable("tenBan",tenBan);
        report->dataManager()->setReportVariable("tongTien",tongTien);
        report->dataManager()->setReportVariable("traTruoc",traTruoc);
        int conPhaiTra = tongTien - traTruoc;
        report->dataManager()->setReportVariable("conPhaiTra",conPhaiTra);
        report->previewReport();
        report->deleteLater();
    }

}

void PhieuXuat::inBill(const QString pcid)
{
    this->phieuXuatID = pcid;
    QScopedPointer<QSqlQueryModel> hocThuViecModel;
    hocThuViecModel.reset(new QSqlQueryModel());
    hocThuViecModel->setQuery("SELECT * from CHI_TIET_PHIEU_XUAT "
                              " where PHIEUXUATID = '"+pcid+"'");
    layThongTinPhieu(pcid);
    if(report.isNull()){
        report = new LimeReport::ReportEngine();
        report->loadFromFile(QApplication::applicationDirPath()+"/reports/bill_coffee.lrxml");
        report->dataManager()->removeModel("chitietpc");
        report->dataManager()->addModel("chitietpc",hocThuViecModel.data(),false);
        qDebug() << tenBan << tongTien << traTruoc;
        report->dataManager()->setReportVariable("tenBan",tenBan);
        report->dataManager()->setReportVariable("tongTien",tongTien);
        report->dataManager()->setReportVariable("traTruoc",traTruoc);
        report->dataManager()->setReportVariable("gioVao",gioVao);
        int conPhaiTra = tongTien - traTruoc;
        report->dataManager()->setReportVariable("conPhaiTra",conPhaiTra);
        report->printReport(printer);
        report->deleteLater();
    }
}

