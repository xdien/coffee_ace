/***********************************************************************
 * Module:  ThongTin.h
 * Author:  xdien
 * Modified: Tuesday, August 02, 2016 2:25:23 PM
 * Purpose: Declaration of the class ThongTin
 * Comment: Thong tin cau hinh, co the dung sqlite
 ***********************************************************************/

#if !defined(__NHAN_SU_ThongTin_h)
#define __NHAN_SU_ThongTin_h
#include <QString>
class ThongTin
{
public:
   void capNhat(void);
   bool themMoi(void);

   QString tenGiamDoc;
   QString tenChucVu;
   QString tenCongTy;
   QString dienThoaiCongTy;
   QString diaChiCongTy;
   /* vd: cai rang, binh thuy */
   QString huyenTp;
   QString hdCongViecPhaiLam;
   QString hdTienThuong;
   QString hdThoaThuanKhac;
   QString noiTaoHopDong;

protected:
private:

};

#endif
