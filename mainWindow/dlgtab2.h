#ifndef DLGTAB2_H
#define DLGTAB2_H

#include <QDialog>

#include <QPainter>

namespace Ui {
class dlgtab2;
}

class dlgtab2 : public QDialog
{
    Q_OBJECT

public:
    explicit dlgtab2(QWidget *parent = nullptr);
    ~dlgtab2();

    void paintEvent(QPaintEvent *event);

private:
    Ui::dlgtab2 *ui;
};

#endif // DLGTAB2_H
