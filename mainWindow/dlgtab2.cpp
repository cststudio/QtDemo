#include "dlgtab2.h"
#include "ui_dlgtab2.h"

dlgtab2::dlgtab2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgtab2)
{
    ui->setupUi(this);

    //initPaint();
}

dlgtab2::~dlgtab2()
{
    delete ui;
}

void dlgtab2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawEllipse(25, 25, 50, 50);

    //绘制直线
    // 反走样,防止出现锯齿状线条 painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色
    painter.setPen(QColor(0, 160, 230));
    // 绘制直线 两个参数，起点坐标和重点坐标
    //QPoint是点的值是int型，QPointF的值是float型
    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));

    //绘制文本
    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(50);//字号
    font.setItalic(true);//斜体
    painter.setFont(font);//设置字体
    // 绘制文本
    painter.drawText(rect(), Qt::AlignCenter, "哈哈");
}
