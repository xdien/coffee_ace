/***********************************************************************
 * Module:  ChiTietPhieuXuat.h
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:53:10 AM
 * Purpose: Declaration of the class ChiTietPhieuXuat
 * Comment: Ph�ng khi kh�ch y�u c?u
 ***********************************************************************/

#if !defined(__COFFEE_ACE_ChiTietPhieuXuat_h)
#define __COFFEE_ACE_ChiTietPhieuXuat_h
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <QDebug>
class ChiTietPhieuXuat
{
public:
   /* Chuyen ban cho tung item */
   int chuyenBan(void);
   bool capNhat();
   bool insert();
   QString pcid;
   int soLuong;
   float chiecKhau;
   int tongTien;
   QString tenHang;
   int giaBanHienTai;
   bool daThanhToan;
   QString hanghoaid;
   QString banid;
   bool xoa(QString pcid,QString hanghoaid);

protected:
private:
   QSqlQuery query;
};

#endif
