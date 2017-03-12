/***********************************************************************
 * Module:  ChiTietPhieuXuat.cpp
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:53:10 AM
 * Purpose: Implementation of the class ChiTietPhieuXuat
 * Comment: Ph�ng khi kh�ch y�u c?u
 ***********************************************************************/

#include "ChiTietPhieuXuat.h"

////////////////////////////////////////////////////////////////////////
// Name:       ChiTietPhieuXuat::chuyenBan()
// Purpose:    Implementation of ChiTietPhieuXuat::chuyenBan()
// Comment:    Chuyen ban cho tung item
// Return:     int
////////////////////////////////////////////////////////////////////////

int ChiTietPhieuXuat::chuyenBan(void)
{
    // TODO : implement
}

bool ChiTietPhieuXuat::capNhat()
{
    query.clear();
    query.prepare("update CHI_TIET_PHIEU_XUAT set SO_LUONG = :soLuong, CHIEC_KHAU=:chiecKhau,"
                  "TONG_TIEN=:tongTien,TEN_HANG=:tenHang,GIA_BAN_HIEN_TAI=:giaBanHienTai,"
                  "DA_THANH_TOAN=:daThanhToan where HANGHOAID = :hanghoaid");
    query.bindValue(":soLuong",soLuong);
    query.bindValue(":chiecKhau",chiecKhau);
    query.bindValue(":tongTien",tongTien);
    query.bindValue(":giaBanHienTai",giaBanHienTai);
    query.bindValue(":daThanhToan",daThanhToan);
    query.bindValue(":banid",banid);
    query.bindValue(":hanghoaid",hanghoaid);
    query.bindValue(":tenHang",tenHang);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Không thể cập nhật lại chi tiet phieu xuat kiểm tra lại mạng" <<query.lastError().text();
        return false;
    }

}

bool ChiTietPhieuXuat::insert()
{
    query.clear();
    query.prepare("INSERT INTO CHI_TIET_PHIEU_XUAT(PHIEUXUATID,HANGHOAID, SO_LUONG, CHIEC_KHAU,TONG_TIEN,"
                  "TEN_HANG, GIA_BAN_HIEN_TAI,DA_THANH_TOAN) VALUES (:pcid,:hanghoaid,:soLuong,:chiecKhau,"
                  ":tongTien,:tenHang,:giaBanHienTai,:daThanhToan) on DUPLICATE KEY "
                  "UPDATE SO_LUONG=:soLuong,TONG_TIEN=:tongTien");
    query.bindValue(":soLuong",soLuong);
    query.bindValue(":chiecKhau",chiecKhau);
    query.bindValue(":tongTien",tongTien);
    query.bindValue(":giaBanHienTai",giaBanHienTai);
    query.bindValue(":daThanhToan",daThanhToan);
    query.bindValue(":banid",banid);
    query.bindValue(":hanghoaid",hanghoaid);
    query.bindValue(":tenHang",tenHang);
    query.bindValue(":pcid",pcid);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Khong the them chi tiet hang" <<query.lastError().text();
        return false;
    }
}

bool ChiTietPhieuXuat::xoa(QString pcid, QString hanghoaid)
{
    query.clear();
    query.prepare("delete from CHI_TIET_PHIEU_XUAT where PHIEUXUATID = :pcid and HANGHOAID=:hanghoaid");
    query.bindValue(":hanghoaid",hanghoaid);
    query.bindValue(":pcid",pcid);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "KHong the xoa ct hang "<< query.lastError().text();
        return false;
    }
}
