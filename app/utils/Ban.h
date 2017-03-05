/***********************************************************************
 * Module:  Ban.h
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:53:49 AM
 * Purpose: Declaration of the class Ban
 ***********************************************************************/

#if !defined(__COFFEE_ACE_Ban_h)
#define __COFFEE_ACE_Ban_h

class PhieuXuat;

class Ban
{
public:
   int them(void);
   int capNhat(void);

   std::string banID;
   std::string ten;
   /* Tr?ng thái bàn */
   bool trangThaiTrong;
   
   PhieuXuat** phieuXuat;

protected:
private:

};

#endif