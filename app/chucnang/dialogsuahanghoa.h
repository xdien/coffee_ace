#ifndef DIALOGSUAHANGHOA_H
#define DIALOGSUAHANGHOA_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class DialogSuaHangHoa;
}

class DialogSuaHangHoa : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSuaHangHoa(QWidget *parent = 0);
    ~DialogSuaHangHoa();

private slots:
    void on_pushButtonThemHang_clicked();

private:
    Ui::DialogSuaHangHoa *ui;
    QSqlTableModel *hangHoaModel;
    QSqlQuery query;
};

#endif // DIALOGSUAHANGHOA_H
