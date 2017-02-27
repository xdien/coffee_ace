#ifndef NHANVIENTABLEFREEZE_H
#define NHANVIENTABLEFREEZE_H

#include <QTableView>
//! [Widget definition]
class NhanVienTableFreeze : public QTableView {
     Q_OBJECT

public:
      NhanVienTableFreeze(QWidget *parent = 0);
      ~NhanVienTableFreeze();
      void aa();

protected:
      virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
      virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

private:
      QTableView *frozenTableView;
      void init();
      void updateFrozenTableGeometry();


private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

};
//! [Widget definition]
#endif // NHANVIENTABLEFREEZE_H
