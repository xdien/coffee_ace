#ifndef DIALOGCHITIETBAN_H
#define DIALOGCHITIETBAN_H

#include <QDialog>
#include <QStandardItemModel>
#include <QCompleter>
#include <QSqlQueryModel>
#include "utils/Ban.h"
#include "utils/PhieuXuat.h"
#include "utils/manageindex.h"
#include <QMessageBox>

namespace Ui {
class DialogChiTietBan;
}

class DialogChiTietBan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChiTietBan(QString banid, QWidget *parent = 0);
    ~DialogChiTietBan();

private slots:
    void on_pushButton_4_released();

    void on_pushButtonVaoban_clicked();
    void layGiaTriTuTenQCompleter(const QModelIndex index);
    void layGiaTriTuIdQCompleter(const QModelIndex index);

    void on_spinBoxSoluong_valueChanged(int arg1);

    void on_spinBoxDonGia_valueChanged(int arg1);

    void on_pushButton_4_clicked();

private:
    Ui::DialogChiTietBan *ui;
    QStandardItemModel *danhSachHangModel;
    QList<QStandardItem *> add(const QString hangHoaID,
                                              const QString ten,
                                                 const QString soLuong,
                                                 const QString donGia,
                                                 const QString tongTien,
                                                 const bool daThanhToan);
    QCompleter *tenComplete;
    QCompleter *idComplete;
    QSqlQueryModel *tenhangHoaModel;
    QSqlQueryModel *idhangHoaModel;
    PhieuXuat *phieuXuat;
    QSqlQuery query;
    QString m_banid;
    Ban *ban;
};

#endif // DIALOGCHITIETBAN_H
