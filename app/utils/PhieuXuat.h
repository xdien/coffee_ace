/***********************************************************************
 * Module:  PhieuXuat.h
 * Author:  xdien
 * Modified: Wednesday, March 01, 2017 2:52:36 AM
 * Purpose: Declaration of the class PhieuXuat
 ***********************************************************************/

#if !defined(__COFFEE_ACE_PhieuXuat_h)
#define __COFFEE_ACE_PhieuXuat_h
#include <QString>
#include <QTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "utils/manageindex.h"
#include "config/common.h"
#include "lrreportengine.h"
#include "lrcallbackdatasourceintf.h"
#include <QApplication>
#include <QPrinter>
class ChiTietPhieuXuat;

class PhieuXuat : public QSqlQueryModel
{
    Q_OBJECT
    //Q_PROPERTY( int count READ rowCount() NOTIFY countChanged())
public:
    explicit PhieuXuat(QObject *parent);
    ~PhieuXuat();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
        ///
   int taoPhieu(QString banid);
   int inPhieu(void);
   int chuyenBan(void);
   int capNhatGhiChu(void);
   int kiemTraThanhToan(QString banid);
   void layThongTinPhieu(QString pcid);

   Q_INVOKABLE bool roiBan(const QString pcid, bool khongUpDateTongTien);

   QString phieuXuatID;
   float chiecKhau;
   QString gioVao;
   QString gioRa;
   int tongTien;
   QString ghiChu;
   bool trangThaiKhoa;
   bool daThanhToan;
   QString tenBan;
   int traTruoc;
   /* Ngay Lap tu chay theo he thong */
   QDateTime ngayLapHt;
   
   ChiTietPhieuXuat** chiTietPhieuXuat;
   bool capNhatSoTienTraTruoc(QString pcid);
   Q_INVOKABLE void xemBill(const QString pcid);
   Q_INVOKABLE void inBill(const QString pcid);

protected:
private:
   QSqlQuery query;
   const static char* COLUMN_NAMES[];
   const static char* SQL_SELECT;
   QHash<int, QByteArray> m_roleNames;
   QPointer<LimeReport::ReportEngine> report;
   QPrinter *printer;

};

#endif
