#ifndef FORMTAIKHOAN_H
#define FORMTAIKHOAN_H

#include <QWidget>
#include "utils/taikhoan.h"
#include <QSqlRelationalTableModel>
#include "Objects/otaikhoan.h"
#include "chucnang/formphanquyen.h"
#include <QMenu>
#include <QScopedPointer>
#include "chucnang/chitiet/dialogdoimatkhau.h"

namespace Ui {
class FormTaiKhoan;
}

class FormTaiKhoan : public QWidget
{
    Q_OBJECT

public:
    explicit FormTaiKhoan(QWidget *parent = 0);
    ~FormTaiKhoan();

private slots:
    void on_pushButtonThemTaiKHoan_clicked();

    void on_tableViewTaiKhoan_doubleClicked(const QModelIndex &index);

    void on_capNhat_clicked();
    void customMenuRequested(QPoint pos);
    void xoaMotTaiKhoan();
    void mo_formDoiMatKhau();

private:
    Ui::FormTaiKhoan *ui;
    QSqlTableModel *taiKhoanTableModel;
    TaiKhoan *taiKhoan;
    FormPhanQuyen *phanQuyen;
    //danh cho menu xoa
    QScopedPointer<QMenu> contextMenu;
    QAction *actionXoa;
    QAction *actionDoiMK;

};

#endif // FORMTAIKHOAN_H
