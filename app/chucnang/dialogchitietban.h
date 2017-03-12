#ifndef DIALOGCHITIETBAN_H
#define DIALOGCHITIETBAN_H

#include <QDialog>
#include <QStandardItemModel>
#include <QCompleter>
#include <QSqlQueryModel>
#include "utils/Ban.h"
#include "utils/PhieuXuat.h"
#include "utils/manageindex.h"
#include "utils/ChiTietPhieuXuat.h"
#include <QMessageBox>
#include "config/common.h"
#include <QMenu>

namespace Ui {
class DialogChiTietBan;
}

class DialogChiTietBan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChiTietBan(QString banid, PhieuXuat *phieuXuatModel, QWidget *parent = 0);
    ~DialogChiTietBan();

private slots:
    void on_pushButton_4_released();

    void on_pushButtonVaoban_clicked();
    void layGiaTriTuTenQCompleter(const QModelIndex index);
    void layGiaTriTuIdQCompleter(const QModelIndex index);

    void on_spinBoxSoluong_valueChanged(int arg1);

    void on_spinBoxDonGia_valueChanged(int arg1);

    void on_pushButton_4_clicked();
    void tinhTongTienHangChuaTT();

    void on_doubleSpinBoxChiecKhau_valueChanged(double arg1);

    void on_spinBoxSoTienDaTra_valueChanged(int arg1);

    void on_spinBoxSoTienConTra_valueChanged(int arg1);

    void on_spinBoxSoTienChieckhau_valueChanged(int arg1);

    void on_spinBoxTongSoTienTruocCK_valueChanged(int arg1);
    void themMoiMatHang();
    void capNhatMatHang();
    void customMenuRequested(QPoint pos);
    void xoaMotMatHang();

    void on_spinBoxSoTienDaTra_editingFinished();

    void on_pushButton_3_clicked();

private:
    Ui::DialogChiTietBan *ui;
    QStandardItemModel *danhSachHangModel;
    QList<QStandardItem *> add(const QString hangHoaID,
                                              const QString ten,
                                                 const QString soLuong,
                                                 const QString donGia,
                                                 const QString tongTien,
                                                 const QString daThanhToan);
    QCompleter *tenComplete;
    QCompleter *idComplete;
    QSqlQueryModel *tenhangHoaModel;
    QSqlQueryModel *idhangHoaModel;
    ChiTietPhieuXuat *chiTietPhieuXuat;
    PhieuXuat *phieuXuat;
    QSqlQuery query;
    QString m_banid;
    Ban *ban;
    int tongTienChuaThanhToan;
    int soTienDaTra;
    QScopedPointer<QMenu> contextMenu;
    QAction *action_xoa;


};

#endif // DIALOGCHITIETBAN_H
