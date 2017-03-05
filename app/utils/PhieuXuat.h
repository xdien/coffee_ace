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
class ChiTietPhieuXuat;

class PhieuXuat : public QSqlQueryModel
{
    Q_OBJECT
    //Q_PROPERTY( int count READ rowCount() NOTIFY countChanged())
public:
    explicit PhieuXuat(QObject *parent);
    void refresh();
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
        ///
   int taoPhieu(void);
   int inPhieu(void);
   int chuyenBan(void);
   int capNhatGhiChu(void);

   QString phieuXuatID;
   float chiecKhau;
   QTime gioVao;
   QTime gioRa;
   int tongTien;
   QString ghiChu;
   bool trangThaiKhoa;
   /* Ngay Lap tu chay theo he thong */
   QDateTime ngayLapHt;
   
   ChiTietPhieuXuat** chiTietPhieuXuat;

protected:
private:
   const static char* COLUMN_NAMES[];
      const static char* SQL_SELECT;
      QHash<int, QByteArray> m_roleNames;
};

#endif
