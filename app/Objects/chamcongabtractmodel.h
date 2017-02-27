#ifndef CHAMCONGABTRACTMODEL_H
#define CHAMCONGABTRACTMODEL_H
#define LE "L"
#define PHEP "P"
#define NGHIBU "NB"
#define NGHICHEDO "CD"
#define OM "O"
#define CHEDOBH "BH"
#define VIECRIENG "VR"
#define KHONGPHEP "KP"
#define NGHITB "TB"
#define NGOAIGIONT "NGNT"
#define NGOAIGIOCN "NGCN"
#define NGOAIGIOLE "NGLE"
#define NGOAIGIO "NG"
#define TRUC "TR"
#define TRUCCN "TC"
#define TRUCLE "TL"
#define TONGCONG "TONG"
#define NGAY "NGAY"
#define CONGTAC "CT"
#define NGAYCONG "CONGCHINH"
#define CHINH "X"
#define STR_NGOAI_GIO "NGOÀI GIỜ"
#define STR_CHINH "CHÍNH"
#define STR_HE_SO "HỆ SỐ"
#define STR_NGAY "NGÀY"

#include <QObject>
#include <QAbstractTableModel>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <utils/ChamCong.h>
#include <QColor>
#include <QBrush>
class ChamCongAbtractModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ChamCongAbtractModel(ChamCong *danhSachNgay, QObject *parent = 0);
    ~ChamCongAbtractModel();
    bool laMayChaml;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    //cho phep sua du lieu
    Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value, int role);
signals:
     void thayDoiHeSo(int index);
private:
    ChamCong *chamCong;
    void setKyHieu(int rowIndex, const QString value);
    //tinh mau cho tung dong
    QColor calculateColorForRow(int row) const;
public slots:
};

#endif // CHAMCONGABTRACTMODEL_H
