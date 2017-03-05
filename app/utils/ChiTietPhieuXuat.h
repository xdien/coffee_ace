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
class ChiTietPhieuXuat
{
public:
   /* Chuyen ban cho tung item */
   int chuyenBan(void);

   int soLuong;
   float chiecKhau;
   int tongTien;
   QString tenHang;
   int giaBanHienTai;

protected:
private:

};

#endif
