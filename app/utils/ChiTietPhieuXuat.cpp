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
                  "DA_THANH_TOAN=:daThanhToan where BANID = :banid and HANGHOAID = :hanghoaid");
    query.bindValue(":soLuong",soLuong);
    query.bindValue(":chiecKhau",chiecKhau);
    query.bindValue(":tongTien",tenHang);
    query.bindValue(":giaBanHienTai",giaBanHienTai);
    query.bindValue(":daThanhToan",daThanhToan);
    query.bindValue(":banid",banid);
    query.bindValue(":hanghoaid",hanghoaid);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Không thể cập nhật lại chi tiet phieu xuat kiểm tra lại mạng" <<query.lastError().text();
        return false;
    }

}
