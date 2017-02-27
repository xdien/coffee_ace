/***********************************************************************
 * Module:  ThamSo.h
 * Author:  xdien
 * Modified: Thursday, November 17, 2016 3:03:08 PM
 * Purpose: Declaration of the class ThamSo
 * Comment: Tham so tinh luong
 ***********************************************************************/

#if !defined(__NHAN_SU_ThamSo_h)
#define __NHAN_SU_ThamSo_h
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
class ThamSo
{
public:
   bool layHeSo(void);

   /* Phieu luong */
   float phanTramBh;
   float phanTramBhCongTy;
   int tienTrucChuNhat;
   int tienTrucLe;
   int tienTrucNgayThuong;
   int heSoGiamTruGc;
   int phanTramTncnPhaiDong;
   int soTienBatDauDongTncn;
   int moc0;
   float moc0hs;
   int moc0st;
   int moc1;
   float moc1hs;
   int moc1st;
   int moc2;
   float moc2hs;
   int moc2st;
   int moc3;
   float moc3hs;
   int moc3st;
   int moc4;
   float moc4hs;
   int moc4st;
   int moc5;
   float moc5hs;
   int moc5st;
   int moc6;
   float moc6hs;
   int moc6st;

protected:
private:

};

#endif
