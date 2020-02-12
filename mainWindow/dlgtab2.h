#ifndef DLGTAB2_H
#define DLGTAB2_H

#include <QDialog>

#include <QPainter>

#include <QtCharts>
//QT_CHARTS_USE_NAMESPACE

// 界面显示中文，文件需要使用UTF8 BOM格式保存，否则乱码--windows vs编译器测试
#pragma execution_character_set("utf-8")

namespace Ui {
class dlgtab2;
}

class dlgtab2 : public QDialog
{
    Q_OBJECT

public:
    explicit dlgtab2(QWidget *parent = nullptr);
    ~dlgtab2();

    void initWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    void paintPixmap();
    void zoomPixmap();

    void paintSimple();
    void paintSerial();
    void paintPie();
    void paintBar();

    QRect m_rect;
    float m_zoom;//缩放系数
    QPoint CurrentCoordinates,LastCoordinates;//当前的坐标,上一次移动的坐标


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::dlgtab2 *ui;
};

#endif // DLGTAB2_H
