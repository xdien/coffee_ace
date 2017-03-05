/***********************************************************************
 * Module:  Ban.cpp
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:53:49 AM
 * Purpose: Implementation of the class Ban
 ***********************************************************************/

#include "PhieuXuat.h"
#include "Ban.h"

////////////////////////////////////////////////////////////////////////
// Name:       Ban::them()
// Purpose:    Implementation of Ban::them()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Ban::them(void)
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Ban::capNhat()
// Purpose:    Implementation of Ban::capNhat()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Ban::capNhat(void)
{
    query.clear();
    query.prepare("update BAN set TRANG_THAI_TRONG = :trangThaiTrong, ID_PHIEU_XUAT_HT=:idPhieuXuatHt where BANID = :banID");
    query.bindValue(":trangThaiTrong",trangThaiTrong);
    query.bindValue(":idPhieuXuatHt",idPhieuXuatHt);
    query.bindValue(":banID",banID);
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Không thể cập nhật lại bàn kiểm tra lại mạng" <<query.lastError().text();
        return false;
    }
}

bool Ban::layThongTinBan(QString banid)
{
    this->banID = banid;
    query.clear();
    query.prepare("SELECT BANID,"
                  "TEN,"
                  "TRANG_THAI_TRONG,"
                  "ID_PHIEU_XUAT_HT "
                  "FROM BAN where BANID = :banid");
    query.bindValue(":banid",banid);
    if(query.exec()){
        if(query.next()){
            this->ten = query.value("TEN").toString();
            this->trangThaiTrong = query.value("TRANG_THAI_TRONG").toBool();
            this->idPhieuXuatHt = query.value("ID_PHIEU_XUAT_HT").toString();
            return true;
        }else{
            qDebug() << "Không thể lấy thông tin bàn theo yêu cầu "<< query.lastError().text();
            return false;
        }
    }else{
        qDebug() << "Khong the truy van den server or sai cu phap "<< query.lastError().text();
        return false;
    }
}

bool Ban::roiBan(QString banid)
{
    query.clear();
    bool ok;
    //kiem tra thanh toan
    ok = phieuXuat->kiemTraThanhToan(banid);
    if(ok){
        //tien hanh xoa pc, tra lai trang thai ban trong
        this->idPhieuXuatHt = "";
        this->trangThaiTrong =true;
        capNhat();
    }
}
