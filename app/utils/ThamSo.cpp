/***********************************************************************
 * Module:  ThamSo.cpp
 * Author:  xdien
 * Modified: Thursday, November 17, 2016 3:03:08 PM
 * Purpose: Implementation of the class ThamSo
 * Comment: Tham so tinh luong
 ***********************************************************************/

#include "ThamSo.h"

////////////////////////////////////////////////////////////////////////
// Name:       ThamSo::layHeSo()
// Purpose:    Implementation of ThamSo::layHeSo()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ThamSo::layHeSo(void)
{
   // TODO : implement
    QSqlQuery query;
    if(query.exec("select * from THAM_SO limit 1")){
        if(query.next()){
            phanTramBh = query.value("PHAN_TRAM_BH").toFloat();
            phanTramBhCongTy = query.value("PHAN_TRAM_BH_CONG_TY").toFloat();
            tienTrucChuNhat = query.value("TIEN_TRUC_CHU_NHAT").toInt();
            tienTrucLe = query.value("TIEN_TRUC_LE").toInt();
            tienTrucNgayThuong = query.value("TIEN_TRUC_NGAY_THUONG").toInt();
            //tncn
            heSoGiamTruGc = query.value("HE_SO_GIAM_TRU_GC").toFloat();
            phanTramTncnPhaiDong = query.value("PHAN_TRAM_TNCN_PHAI_DONG").toFloat();
            soTienBatDauDongTncn = query.value("SO_TIEN_BAT_DAU_DONG_TNCN").toInt();
            moc0 = query.value("MOC0").toInt();
            moc1 = query.value("MOC1").toInt();
            moc2 = query.value("MOC2").toInt();
            moc3 = query.value("MOC3").toInt();
            moc4 = query.value("MOC4").toInt();
            moc5 = query.value("MOC5").toInt();
            moc6 = query.value("MOC6").toInt();
            moc0hs = query.value("MOC0HS").toFloat();
            moc1hs = query.value("MOC1HS").toFloat();
            moc2hs = query.value("MOC2HS").toFloat();
            moc3hs = query.value("MOC3HS").toFloat();
            moc4hs = query.value("MOC4HS").toFloat();
            moc5hs = query.value("MOC5HS").toFloat();
            moc6hs = query.value("MOC6HS").toFloat();
            moc0st = query.value("MOC0ST").toInt();
            moc1st = query.value("MOC1ST").toInt();
            moc2st = query.value("MOC2ST").toInt();
            moc3st = query.value("MOC3ST").toInt();
            moc4st = query.value("MOC4ST").toInt();
            moc5st = query.value("MOC5ST").toInt();
            moc6st = query.value("MOC6ST").toInt();
            return true;
        }else{
            qDebug()<<"Khong nhan duoc ket qua";
            return false;
        }
    }else{
        qDebug() << "Khong the lay duoc du lieu";
        return false;
    }

}
