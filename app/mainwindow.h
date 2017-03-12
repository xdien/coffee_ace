#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lrreportengine.h"
#include "lrcallbackdatasourceintf.h"
#include <QQuickItem>
#include <QMainWindow>
#include <QSqlQuery>
#include <QMdiSubWindow>
#include "config/common.h"
#include <QLabel>
#include "login.h"
#include <QtSql>
#include <QMessageBox>
#include <QObjectList>
#include "about.h"
#include "chucnang/formquyen.h"
#include "chucnang/formtaikhoan.h"
#include "lrreportengine.h" //to add report engine
#include "lrcallbackdatasourceintf.h" //if you want use callback datasources
#include "config/common.h"
#include <QQmlApplicationEngine>
#include "utils/PhieuXuat.h"
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

#include "chucnang/dialogchitietban.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
signals:

private slots:
    void on_actionSQL_triggered();

    void on_actionAbout_Qt_triggered();
    void capnhatPhanQuyen(QString username);

   void on_actionAbout_triggered();
   void on_actionDan_nhap_triggered();

     void on_actionQuan_ly_NKH_triggered();

     void on_actionQuyen_triggered();

     void on_actionTai_Khoan_triggered();

     void on_actionNhapHang_triggered();

     void on_actionB_n_h_ng_triggered();
     void moFormChiTiet(QString banid);
     //void xemBill(QString pcid);
     void inPhieuVaRoiBan(QString pcid);

private:
    Ui::MainWindow *ui;
    QSqlQuery query;
    QSqlDatabase db;
    login *moi;
    QList<QMdiSubWindow*> subwindowList;
    QObjectList objl;
    QLabel *statusLabel, *tinhtrangsql;
    QPointer<QQuickView> view2;
    QPointer<FormTaiKhoan> formTaiKhoan;
    PhieuXuat *phieuXuatModel;

};

#endif // MAINWINDOW_H
