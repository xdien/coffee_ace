#ifndef DIALOGDOIMATKHAU_H
#define DIALOGDOIMATKHAU_H

#include <QDialog>
#include "utils/taikhoan.h"
#include <QMessageBox>

namespace Ui {
class DialogDoiMatKhau;
}

class DialogDoiMatKhau : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDoiMatKhau(QString username, QWidget *parent = 0);
    ~DialogDoiMatKhau();

private slots:
    void on_buttonBox_accepted();

private:
    QString m_username;
    Ui::DialogDoiMatKhau *ui;
};

#endif // DIALOGDOIMATKHAU_H
