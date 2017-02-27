#ifndef FORMQUYEN_H
#define FORMQUYEN_H

#include <QDialog>
#include "utils/quyen.h"
#include "utils/manageindex.h"
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QStandardItem>
#include <QMenu>
#include "config/common.h"

namespace Ui {
class FormQuyen;
}

class FormQuyen : public QDialog
{
    Q_OBJECT

public:
    explicit FormQuyen(QWidget *parent = 0);
    ~FormQuyen();
    Quyen *quyen;
    //ham set quyen hien tai
    ///
    /// \brief setQuyen khong biet giai thich, lay thong tin quyen hien tai set len form
    /// ham nay phai duoc goi sau khi khoi dong, neu khong thi loi
    /// \param quyenid
    ///
    void setQuyen(int quyenid);
private slots:
    void on_pushButton_2_clicked();

    void on_listViewPhongBanCC_doubleClicked(const QModelIndex &index);

    void on_listViewPhongBanTL_doubleClicked(const QModelIndex &index);

    void on_listViewPhongBanDS_doubleClicked(const QModelIndex &index);
    void customMenuRequestedCC(QPoint pos);
    void customMenuRequestedTL(QPoint pos);
    void customMenuRequestedDS(QPoint pos);

    void xoaCC();
    void xoaTL();
    void xoaDS();



    void on_pushButtonCapNhat_clicked();
    //lay gia tri tu form
    void layGiaTri();

private:
    Ui::FormQuyen *ui;
    QSqlQueryModel *phongBanModel;
    QStandardItemModel *chamCongDC;
    QStandardItemModel *tinhLuongDC;
    QStandardItemModel *danhSachDC;
    //
    QScopedPointer<QMenu> contextMenuCC;
    QAction *action_xoaCC;
    //
    QScopedPointer<QMenu> contextMenuTL;
    QAction *action_xoaTL;
    //
    QScopedPointer<QMenu> contextMenuDS;
    QAction *action_xoaDS;
    QList<QStandardItem *> append(const QString &tenPhongBan,
                                             const QString &phongBanid);
    QSqlQuery query;
    int m_quyenid;
};

#endif // FORMQUYEN_H
