/***********************************************************************
 * Module:  HangHoa.h
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:50:12 AM
 * Purpose: Declaration of the class HangHoa
 ***********************************************************************/

#if !defined(__COFFEE_ACE_HangHoa_h)
#define __COFFEE_ACE_HangHoa_h

class ChiTietPhieuXuat;

class HangHoa
{
public:
   int them(void);
   int capNhatGia(void);
   int capNhatTenHang(void);

   QString hangHoaID;
   QString ten;
   int giaBan;
   int slTon;
   
   ChiTietPhieuXuat** chiTietPhieuXuat;

protected:
private:

};

#endif