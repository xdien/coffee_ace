#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
    QSqlQuery query;
    QSqlDatabase db;
    login *moi;
    QList<QMdiSubWindow*> subwindowList;
    QObjectList objl;
    QLabel *statusLabel, *tinhtrangsql;
    QPointer<FormTaiKhoan> formTaiKhoan;

};

#endif // MAINWINDOW_H
