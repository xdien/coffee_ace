#ifndef DIALOGNHOMQUYEN_H
#define DIALOGNHOMQUYEN_H

#include <QDialog>

namespace Ui {
class DialogNhomQuyen;
}

class DialogNhomQuyen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNhomQuyen(QWidget *parent = 0);
    ~DialogNhomQuyen();

private:
    Ui::DialogNhomQuyen *ui;
};

#endif // DIALOGNHOMQUYEN_H
