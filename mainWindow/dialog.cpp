#include "dialog.h"
#include "ui_dialog.h"

#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    intWindow();
}

Dialog::~Dialog()
{
    delete ui;
}

#include <QAction>
#include <QMenu>

void Dialog::intWindow()
{
    m_opened = 0;

    ///////////////////////////////

    ui->label->installEventFilter(this);

    // 初始化动作
    QAction *newAction = new QAction("新建",this);
    // 初始化右键菜单
    QMenu *rightClickMenu = new QMenu(this);
    // 动作添加到右键菜单
    rightClickMenu->addAction(newAction);
    rightClickMenu->addSeparator();
//    rightClickMenu->addAction(ui->exitAction);
//    // 给动作设置信号槽
//    connect(ui->exitAction, &QAction::triggered, this, &MainWindow::on_exitAction_triggered);

    // 给控件设置上下文菜单策略:鼠标右键点击控件时会发送一个void QWidget::customContextMenuRequested(const QPoint &pos)信号
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}


bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->label)
    {
        if(event->type() == QEvent::Paint)
        {
            drawTest();
            return true; // 事件处理完毕
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QDialog::eventFilter(watched, event);
    }
}

void Dialog::drawTest()
{
//    QPainter painter(ui->label);
//    //绘制直线
//    // 反走样,防止出现锯齿状线条 painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));
//    // 绘制直线 两个参数，起点坐标和重点坐标
//    //QPoint是点的值是int型，QPointF的值是float型
//    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));
//    //绘制文本
//    QPainter painter(ui->label);
//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));
//    // 设置字体：微软雅黑、点大小50、斜体
//    QFont font;
//    font.setFamily("Microsoft YaHei");
//    font.setPointSize(50);//字号
//    font.setItalic(true);//斜体
//    painter.setFont(font);//设置字体
//    // 绘制文本
//    painter.drawText(rect(), Qt::AlignCenter, "哈哈");

    QPainter painter(ui->label);
    painter.setPen(Qt::blue);
    painter.drawEllipse(25, 25, 50, 50);
}

void Dialog::on_pushButton_clicked()
{
    emit sig_backMain(100, 200); // 发送信号
    qDebug() << "sending signal...";
    this->close();
}

void Dialog::myshow()
{
    this->show();
    m_opened = 1;
}

void Dialog::myclose()
{
    if (m_opened)
    {
        qDebug() << "will close";
        this->close();
    }
}

