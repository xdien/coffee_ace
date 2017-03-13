#ifndef DIALOGBAOCAODOANHTHU_H
#define DIALOGBAOCAODOANHTHU_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class DialogBaoCaoDoanhThu;
}

class DialogBaoCaoDoanhThu : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBaoCaoDoanhThu(QWidget *parent = 0);
    ~DialogBaoCaoDoanhThu();

private slots:
    void on_pushButtonXem_clicked();

private:
    Ui::DialogBaoCaoDoanhThu *ui;
    QSqlQueryModel *baoCaoModel;
    QSqlQuery query;
};

#endif // DIALOGBAOCAODOANHTHU_H
