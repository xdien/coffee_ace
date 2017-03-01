#ifndef DIALOGCHITIETBAN_H
#define DIALOGCHITIETBAN_H

#include <QDialog>

namespace Ui {
class DialogChiTietBan;
}

class DialogChiTietBan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChiTietBan(QWidget *parent = 0);
    ~DialogChiTietBan();

private:
    Ui::DialogChiTietBan *ui;
};

#endif // DIALOGCHITIETBAN_H
