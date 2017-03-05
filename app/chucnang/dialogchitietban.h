#ifndef DIALOGCHITIETBAN_H
#define DIALOGCHITIETBAN_H

#include <QDialog>
#include <QStandardItemModel>
#include <QCompleter>
#include <QSqlQueryModel>

namespace Ui {
class DialogChiTietBan;
}

class DialogChiTietBan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChiTietBan(QWidget *parent = 0);
    ~DialogChiTietBan();

private slots:
    void on_pushButton_4_released();

private:
    Ui::DialogChiTietBan *ui;
    QStandardItemModel *danhSachHangModel;
    QList<QStandardItem *> add(const QString hangHoaID,
                                              const QString ten,
                                                 const int soLuong,
                                                 const int donGia,
                                                 const int tongTien,
                                                 const bool daThanhToan);
    QCompleter *complete;
    QSqlQueryModel *hangHoaModel;
};

#endif // DIALOGCHITIETBAN_H
