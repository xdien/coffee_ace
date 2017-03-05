/***********************************************************************
 * Module:  Ban.h
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:53:49 AM
 * Purpose: Declaration of the class Ban
 ***********************************************************************/

#if !defined(__COFFEE_ACE_Ban_h)
#define __COFFEE_ACE_Ban_h
#include <QDebug>
#include <QSqlQuery>
#include "utils/PhieuXuat.h"

class PhieuXuat;

class Ban
{
public:
   int them(void);
   int capNhat(void);
   bool layThongTinBan(QString banid);
   bool roiBan(QString banid);//ra khach di ve
   bool doiBan();

   QString banID;
   QString ten;
   QString idPhieuXuatHt;
   /* Tr?ng thái bàn */
   bool trangThaiTrong;
   
   PhieuXuat* phieuXuat;

protected:
private:
   QSqlQuery query;
};

#endif
