#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainWindow();

    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 对主窗口的初始化
void MainWindow::initMainWindow()
{
    setWindowTitle(tr("MainWindow Demo"));
    setMinimumSize(480, 320);

    Qt::WindowFlags winFlags  = Qt::Dialog;
    winFlags = winFlags | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;

    setWindowFlags(winFlags);
}

// 布局、控件、信号等初始化
void MainWindow::initWindow()
{
    m_pressMouse = 0;

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        //记录鼠标的世界坐标
        m_startPos = event->globalPos();
        //记录窗体的世界坐标
        m_windowPos = this->frameGeometry().topLeft();
        m_pressMouse = 1;
    }
    else if(event->button() == Qt::RightButton)
    {

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if (m_pressMouse)
        {
        //移动中的鼠标位置相对于初始位置的相对位置
        QPoint relativePos = event->globalPos() - m_startPos;
        //然后移动窗体即可
        this->move(m_windowPos + relativePos );

        }
    }
    else if(event->button() == Qt::RightButton)
    {

    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressMouse = 0;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier) // 特殊按键
    {
        if(event->key() == Qt::Key_M)
        {
            qDebug() << "M press";
        }
    }
//    else
//    {
//        QMainWindow::keyPressEvent(event);
//    }

    if(event->key() == Qt::Key_Up)
    {
        if(event->isAutoRepeat())   return;
        qDebug() << "Up press";

    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier) // 特殊按键
    {
        if(event->key() == Qt::Key_M)
        {
            qDebug() << "M release";
        }
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }

    if(event->key() == Qt::Key_Up)
    {
        if(event->isAutoRepeat())   return;
        qDebug() << "Up release";
    }
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::about(this, "关于", "这是带html标签的<font color='red'>信息</font>");
    //QMessageBox::information(this, tr("提示标题"), tr("这是信息窗口"));
    //QMessageBox::question(this, tr("询问标题"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    // 加其它按钮
    //QMessageBox::question(this, tr("询问标题"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Discard | QMessageBox::Save, QMessageBox::Yes);
    //QMessageBox::warning(this, tr("警告标题"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //QMessageBox::critical(this, tr("严重问题"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    //带交互的
    QMessageBox message(QMessageBox::NoIcon, "测试", "Yes 关于 No显示带图片的窗口", QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Discard | QMessageBox::Save, nullptr);
    int ret = message.exec();
    if (ret == QMessageBox::Yes)
    {
        QMessageBox::about(this, "关于", "这是带html标签的<font color='red'>信息</font>");
    }
    else if (ret == QMessageBox::No)
    {
        QMessageBox msg(QMessageBox::NoIcon, "关于", "关于本程序，左侧是图片");
        msg.setIconPixmap(QPixmap(":images/logo1.jpg"));
        //msg.setIconPixmap(QPixmap(":subprefix/images/logo.png")); // 有前缀
        msg.exec();
    }
    else if (ret == QMessageBox::Abort)
    {
        //QMessageBox::critical(this, tr("放弃"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        QMessageBox::critical(this, tr("写入文件"), tr("打开文件 %1 失败, 无法写入\n%2").arg("foo.bat").arg("错误：文件不存在"), QMessageBox::Ok);
    }
    else if (ret == QMessageBox::Retry)
    {
        QMessageBox::question(this, tr("重试"), tr("信息体信息体信息体信息体"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    static bool isTop = true;

    // 置顶 注：切换时会有闪烁
    Qt::WindowFlags winFlags  = Qt::Dialog;

    if (isTop)
    {
        winFlags |= Qt::WindowStaysOnTopHint;
        setWindowFlags(winFlags);
        showNormal();
        isTop = false;
        ui->pushButton_2->setText(tr("取消置顶"));
        ui->pushButton->setEnabled(false);
    }
    else
    {
        winFlags  &= ~Qt::WindowStaysOnTopHint;
        setWindowFlags(winFlags);
        showNormal();
        isTop = true;
        ui->pushButton_2->setText(tr("置顶"));
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setText(tr("退出程序"));
    ui->pushButton_3->setIcon(QIcon(":images/exit.png"));
}

void MainWindow::on_pushButton_4_clicked()
{
    QStringList list;
    list.clear();
    list << "1200" << "2400" << "4800" << "9600" << "14400" << \
         "19200" << "38400" << "43000" << "57600" << "76800" << \
         "115200" << "230400" << "256000" << "460800" << "921600";
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentText(tr("115200"));
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << ui->comboBox->currentText();
    qDebug() << ui->comboBox->currentIndex();
}
