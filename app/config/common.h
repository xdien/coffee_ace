#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QComboBox>

#include <QDate>
#include <string>
#include <QSqlQueryModel>
#include <math.h>
#include <QDebug>
#include <QVector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#define AAA "aaaa"

using namespace std;
namespace tenquyen {
const QString capSo = "capSo";
const QString traSo = "traSo";
const QString taoHD = "taoHD";
const QString xemChiTietNV = "xemChiTietNV";
const QString thayDoiTKNH = "thayDoiTKNH";
const QString quyDinhLuong = "quyDinhLuong";
const QString taiKhoanNganHang = "taiKhoanNganHang";
const QString taoHDThuViec = "taoHDThuViec";
const QString xemSinhNhat = "xemSinhNhat";
const QString xemHopDongGanHetHan="HDGanHetHan";
const QString tamUng = "tamUng";
//phan quyen he thong
const QString quiDinhHeSo = "quiDinhHeSo";
const QString phanQuyen = "phanQuyen";
const QString taiKhoan = "taoTK";
const QString thayDoiTK = "thaiDoiTK";
const QString xemTinhLuong = "xemTinhLuong";
//menu
const QString QLHopDong = "qlHD";
const QString QLHocThuViec = "qlThuViec";
const QString QLChucVu = "qlChucVu";
const QString QLBaoHiem = "qlBaoHiem";
const QString QLTuyenNV = "qlTuyenNV";
const QString QLQuyetDinh = "qlQuyetDinh";
const QString QLNghiLuu = "qlNghiLuu";
const QString QLTamUng = "qlTamUng";
const QString Quyen = "Quyen";
const QString QLThuong = "qlthuong";


}
class Common
{
public:
    enum QUYEN{
        NV_TIMKIEM,
        NV_XEM_SINH_NHAT,
        NV_XEM_HD_HET_HAN,
        NV_XEM_DS_PHONGBAN,
        MV_MN_TAO_HD,
        NV_THU_VIEC,
        NV_CAP_SO,
        NV_TRA_SO,
        NV_STK_NGAN_HANG,
        NV_CHI_TIET//ta ca quyen tren nhan vien do
    };
    enum FORMCHINH{
        FORM_CHAMCONG,
        FORM_DANHSACH
    };

    //them phong ban
    static void themPBTheoQuyen(QComboBox *comBoBox, FORMCHINH f);
    //tim quyen tuong ung
    static bool timQuyen(const QString q);

    static QScopedPointer<QJsonArray> coQuyen;
    static QUYEN CACQUYEN;
    static QString TEN_DN;
    static QString DIA_CHI_DN;
    static int NGAY_BAT_DAU_TINH_LUONG;
    static int NGAY_BAT_DAU_CHAM_CONG;
    static int NAM_HIEN_TAI;
    static int kyHienTai;
    static int findIndex(QSqlQueryModel *model,QString value, int columnNum);
    static void readblock3(char scr[],char result[]);
    static QString dochangchuc(int so, bool daydu);
    static QString docblock(int so, bool daydu);
    static QString dochangtrieu(int so, bool daydu);
    static QString docso(int so);

    //static QVector<QString> mangso = {'không','một','hai','ba','bốn','năm','sáu','bảy','tám','chín'};
    static QStringList  mangso;
    static QString chuoi;
    Common();
    //static int findIndex(QSqlQueryModel *model, QString value, int columnNum) const;
private:

};

#endif // COMMON_H
