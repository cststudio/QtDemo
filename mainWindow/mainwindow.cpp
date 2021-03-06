﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMainWindow();

    initWindow();

    initTabWidget();
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
    //winFlags = Qt::WindowFullscreenButtonHint;
    setWindowFlags(winFlags);
}

// 布局、控件、信号等初始化
void MainWindow::initWindow()
{
    // 这里是成员变量初始化
    m_pressMouse = 0;
    dlg = nullptr;

    m_stsEmpty = nullptr;
    m_stsDebugInfo = nullptr;
    m_stsSysTime = nullptr;
    m_stsCopyright = nullptr;

    // 主窗体初始化（注：如果和其它子窗体有前后顺序的，需要注意）
    //initStatusBar(); // 状态栏
    initStatusBar2(); // 状态栏

    // 额外的窗体初始化
    if (dlg == nullptr)
    {
        dlg = new Dialog;
    }

    // 菜单栏
    // 打开、关闭 子对话框。注：myshow是公开的slot函数
    //ui->actionclose->setEnabled(false); // 有些互斥的，应该要考虑其逻辑关系，此处从略
    connect(ui->actionopen, &QAction::triggered, dlg, &Dialog::myshow);
    connect(ui->actionclose, &QAction::triggered, dlg, &Dialog::myclose);


    ui->pushButton->setToolTip("button tips");
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setValue(30);
    ui->spinBox->setRange(0, 100);
    ui->spinBox->setValue(30);

    ui->radioButton->setChecked(true);


    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);


    ui->label_3->installEventFilter(this);

}

void MainWindow::initStatusBar()
{
    // 状态栏分别为：
    // 临时信息（可不用）做一空的label占位
    // 提示信息（可多个）
    // 系统时间
    // 版本信息（或版权声明）

    //ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 不显示边框
    ui->statusbar->setSizeGripEnabled(false);//去掉状态栏右下角的三角

    m_stsPinned = new QLabel();
    m_stsEmpty = new QLabel();
    m_stsDebugInfo = new QLabel();
    m_stsSysTime = new QLabel();
    m_stsCopyright = new QLabel();
    m_stsExit = new QLabel();

    // 置顶图标
    m_stsPinned->installEventFilter(this); // 安装事件过滤，以便获取其单击事件
    m_stsPinned->setMinimumWidth(20);
    // 贴图
    QPixmap pinnedIcon(":/images/unpinned.bmp");
    m_stsPinned->setPixmap(pinnedIcon);
    ui->statusbar->addWidget(m_stsPinned);

    m_stsEmpty->setMinimumWidth(100);
    ui->statusbar->addWidget(m_stsEmpty);
    m_stsDebugInfo->setMinimumWidth(this->width()/3);
    ui->statusbar->addWidget(m_stsDebugInfo);

    //ui->statusbar->showMessage(tr("临时信息!"),2000);//显示临时信息2000ms 前面的正常信息被覆盖 当去掉后一项时，会一直显示

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
    m_stsSysTime->setText(timeStr);
    ui->statusbar->addPermanentWidget(m_stsSysTime);

    // 版权信息
    m_stsCopyright->setFrameStyle(QFrame::NoFrame);
    m_stsCopyright->setText(tr("  <a href=\"https://www.latelee.org\">技术主页</a>  "));
    m_stsCopyright->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(m_stsCopyright);

    // 退出图标
    m_stsExit->installEventFilter(this); // 安装事件过滤，以便获取其单击事件
    m_stsExit->setToolTip("Exit App");
    // 贴图
    QPixmap exitIcon(":/images/exit.jpg");
    m_stsExit->setMinimumWidth(32);
    m_stsExit->setPixmap(exitIcon);
    ui->statusbar->addPermanentWidget(m_stsExit);
    
    connect(this, &MainWindow::sig_exit, qApp, &QApplication::quit); // 直接关联到全局的退出槽
}

void MainWindow::initStatusBar2()
{
    // 状态栏分别为：
    // 临时信息（可不用）做一空的label占位
    // 提示信息（可多个）
    // 系统时间
    // 版本信息（或版权声明）

    m_stsEmpty = new QLabel();
    m_stsDebugInfo = new QLabel();
    m_stsSysTime = new QLabel();
    m_stsCopyright = new QLabel();
    m_stsExit = new QLabel();

    m_stsEmpty->setMinimumWidth(100);
    ui->statusbar->addPermanentWidget(m_stsEmpty);
    m_stsEmpty->setText("cnt: 250");

    m_stsDebugInfo->setMinimumWidth(100);
    ui->statusbar->addPermanentWidget(m_stsDebugInfo);

    ui->statusbar->showMessage(tr("临时信息!"), 500);

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
    m_stsSysTime->setText(timeStr);
    ui->statusbar->addPermanentWidget(m_stsSysTime);

    // 版权信息
    m_stsCopyright->setFrameStyle(QFrame::NoFrame);
    m_stsCopyright->setText(tr("  <a href=\"https://www.latelee.org\">技术主页</a>  "));
    m_stsCopyright->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(m_stsCopyright);

    // 退出图标
    m_stsExit->installEventFilter(this); // 安装事件过滤，以便获取其单击事件
    m_stsExit->setToolTip("Exit App");
    // 贴图
    QPixmap exitIcon(":/images/exit.jpg");
    m_stsExit->setMinimumWidth(22);
    m_stsExit->setPixmap(exitIcon);
    ui->statusbar->addPermanentWidget(m_stsExit);

    connect(this, &MainWindow::sig_exit, qApp, &QApplication::quit); // 直接关联到全局的退出槽
}

void MainWindow::showDebugInfo(QString str)
{
    //m_stsDebugInfo->setText(str);
    ui->statusbar->showMessage(str, 500);
}

void MainWindow::showDebugInfo(int& value)
{
    ui->statusbar->showMessage(QString::number(value), 500);
}

#include <QTextEdit>
void MainWindow::initTabWidget()
{
    ui->tabWidget->clear();//清空选项卡

    // 选项卡的方位，右、下、左、上 <--> 东南西北，默认在上方，即北
    //ui->tabWidget->setTabPosition(QTabWidget::North);
    //ui->tabWidget->setTabPosition(QTabWidget::West);


    ui->tabWidget->addTab(new dlgtab2(), "画图测试");
    ui->tabWidget->addTab(new DlgTab1(), "列表测试");

    QTextEdit *page = new QTextEdit();
    page->setText("这是即时创建的一个控件");
    ui->tabWidget->addTab(page, " 单独控件");
    //ui->tabWidget->setTabShape(QTabWidget::Triangular);//设置选项卡的形状
}

void MainWindow::initSystemTray()
{
    trayicon = new QSystemTrayIcon(this);
    QAction *quit = new QAction(tr("exit"), this);
    trayiconMenu = new QMenu(this);
    trayiconMenu->addAction(quit); //这里可以添加多个菜单
    // trayiconMenu->addSeparator();

    QIcon icon(":images/logo.png");
    trayicon->setIcon(icon);
    trayicon->setToolTip(tr("mainWindow"));
    trayicon->setContextMenu(trayiconMenu);

    connect(quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    //connect(this, &MainWindow::sig_exit, qApp, &QApplication::quit);
    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));

    trayicon->show();
}

//下面处理不同情况下，单击托盘图标的操作
void MainWindow::on_systemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    //单击
    case QSystemTrayIcon::Trigger:
    {
        //恢复窗口显示
        if(this->isVisible())//判断窗口是否可见
        {
            if(this->isMinimized())//窗口是否是最小化
            {
                this->setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
                //  this->setWindowFlags(Qt::Widget);//取消置顶
                this->setWindowState(Qt::WindowActive);
                this->setGeometry(this->geometry());//使得每次显示窗口为上次的位置
                this->show();
            }
            else
            {
                this->hide();
            }
        }
        else
        {
            this->setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
            //  this->setWindowFlags(Qt::Widget);//取消置顶
            this->setWindowState(Qt::WindowActive);
            this->setGeometry(this->geometry());
            this->show();
        }
    }
    break;
    default:
    break;
    }
}

// 异常
void MainWindow::changeEvent(QEvent * event)
{
//    if (event->type() != QEvent::WindowStateChange)
//    {
//        return;
//    }
//    if (this->windowState() == Qt::WindowMaximized)
//    {

//    }
//    else if (this->windowState() == Qt::WindowMinimized)
//    {
//        if (trayicon->isVisible())
//        {
//            //this->hide();
//            //this->close();
//            //event->ignore();
//        }
//    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_stsExit) // 程序退出
    {
        //判断事件
        if(event->type() == QEvent::MouseButtonPress)
        {
            m_stsDebugInfo->setText("press exit label");
            // TODO：直接退出还是发信号？
            emit sig_exit();
            return true; // 事件处理完毕
        }
        else
        {
            return false;
        }
    }
    else if (watched == m_stsPinned) // 置顶
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            static bool isTop = true;
            Qt::WindowFlags winFlags  = Qt::Dialog;
            winFlags = winFlags | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
            if (isTop)
            {
                winFlags |= Qt::WindowStaysOnTopHint;
                setWindowFlags(winFlags);
                showNormal();
                QPixmap pinnedIcon(":/images/pinned.bmp");
                m_stsPinned->setPixmap(pinnedIcon);
                isTop = false;
            }
            else
            {
                winFlags  &= ~Qt::WindowStaysOnTopHint;
                setWindowFlags(winFlags);
                showNormal();
                QPixmap pinnedIcon(":/images/unpinned.bmp");
                m_stsPinned->setPixmap(pinnedIcon);
                isTop = true;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (watched == ui->label_3)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMenu *menu = new QMenu();
            QAction *test = new QAction("测试",this);

            menu->addAction(test);
            menu->exec(QCursor::pos());
            //connect(test, SIGNAL(triggered(bool)), this, SLOT(onTest()));
            return true; // 事件处理完毕
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QMainWindow::eventFilter(watched, event);
    }
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

    ui->pushButton->setVisible(false);

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
        ui->pushButton->setVisible(true);
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
        m_stsDebugInfo->setText("置顶");
    }
    else
    {
        winFlags  &= ~Qt::WindowStaysOnTopHint;
        setWindowFlags(winFlags);
        showNormal();
        isTop = true;
        ui->pushButton_2->setText(tr("置顶"));
        ui->pushButton->setEnabled(true);
        m_stsDebugInfo->setText("置顶取消");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setText(tr("退出程序"));
    ui->pushButton_3->setIconSize(ui->pushButton_3->rect().size()); // 设置大小
    ui->pushButton_3->setIcon(QIcon(":images/exit.png"));

    //窗口左上角的位置(含边框)
        qDebug() << this->frameGeometry().x() << this->frameGeometry().y();//1
        qDebug() << this->x()  << this->y();//2
        qDebug() << this->pos().x() << this->pos().y();//3
        //窗口的宽度和高度(含边框)
        qDebug() << this->frameGeometry().width() << this->frameGeometry().height();
        //窗口左上角的位置(不含边框)
        qDebug() << this->geometry().x() << this->geometry().y();
        //窗口的宽度和高度(不含边框)
        qDebug() << this->geometry().width() << this->geometry().height();//1
        qDebug() << this->width() << this->height();//2
        qDebug() << this->rect().width() << this->rect().height();//3
        qDebug() << this->size().width() << this->size().height();//4
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
    QString str;
    str = "current text: " + ui->comboBox->currentText();
    m_stsDebugInfo->setText(str);

    qDebug() << ui->comboBox->currentText();
    qDebug() << ui->comboBox->currentIndex();
}

#include "dialog.h"
void MainWindow::on_pushButton_6_clicked()
{
    if (dlg == nullptr)
    {
        dlg = new Dialog;
    }

    // 如果要隐藏界面，则要将进行signal与slot的关联
    // sig_backMain为子窗口发送的信号
    // 主界面保持的话，无须如此
    //connect(dlg, SIGNAL(sig_backMain(int, int)), this, SLOT(on_reshow(int, int))); // 旧格式
    connect(dlg, &Dialog::sig_backMain, this, &MainWindow::on_reshow); // 新格式
    this->hide(); // 隐藏主界面
    dlg->show(); // 显示子界面

    m_stsDebugInfo->setText("show sub dialog");
}

void MainWindow::on_reshow(int a, int b)
{
    qDebug() << a;
    qDebug() << b;
    this->show();
}

#include "common.h"

void MainWindow::on_pushButton_7_clicked()
{
    QString name = "Video";
    registryWrite(name, 720, 480);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString name;
    int width, height;
    registryRead(name, width, height);

    qDebug() << name;
    qDebug() << width;
    qDebug() << height;

}

void MainWindow::on_pushButton_9_clicked()
{
    static int init = 1;
    static QMovie *pMovie = nullptr; // 可做成员变量
    if (init)
    {
        pMovie = new QMovie(":images/run.gif");
        init = 0;
    }

    static int play = 1;
    if (play == 1)
    {
        ui->label->setFixedSize(329, 247);
        ui->label->setScaledContents(true);
        ui->label->setMovie(pMovie);
        pMovie->start();
        ui->pushButton_9->setText("停止动画");
        play = 0;
    }
    else
    {
        pMovie->stop();
        ui->label->clear();
        ui->pushButton_9->setText("播放动画");
        play = 1;
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    QPixmap pixmap(":images/logo.png");
    ui->label->setPixmap(pixmap);
    ui->label->setFixedSize(128, 128);
    ui->label->setScaledContents(true);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    showDebugInfo(value);
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    showDebugInfo(value);
}

void MainWindow::on_pushButton_11_clicked()
{
    int val = ui->horizontalSlider->value();
    QString tmp = "val: " + QString::number(val);
    //QString tmp = QString::asprintf("value: %d", val);
    ui->pushButton_11->setText(tmp);
}

void MainWindow::on_pushButton_12_clicked()
{
    int val = ui->spinBox->value();
    QString tmp = "val: " + QString::number(val);
    ui->pushButton_12->setText(tmp);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    showDebugInfo(arg1);
}

// 按钮添加菜单
void MainWindow::on_pushButton_13_clicked()
{
    QMenu *mymenu=new QMenu;
    QList<QAction*> aList;
    for (int i = 0; i < 4; i++)
    {
        QAction *click=new QAction("菜单按钮"+QString::number(i),this);
        aList.append(click);
    }

    mymenu->addActions(aList);
    ui->pushButton_13->setStyleSheet("QPushButton::menu-indicator{image:none}");
    ui->pushButton_13->setMenu(mymenu);
    // TODO：如何响应事件
}

void MainWindow::on_pushButton_14_clicked()
{

}

// 使用槽实现定时响应事件
void MainWindow::on_pushButton_15_clicked()
{
    static int init = 1;
    if (init)
    {
        // 注：创建定时器，到点自动触发timeout信息，关联到自定义的槽
        m_timer = new QTimer(this);
        connect(m_timer,&QTimer::timeout,[=](){
            QDateTime dateTime(QDateTime::currentDateTime());
            QString timeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
            ui->label_2->setText(timeStr);

            static int i = 0;
            i++;
            ui->lcdNumber->display(i);
        });
        init = 0;
    }

    static int play = 1;
    if (play == 1)
    {
        if (m_timer->isActive() == false)
        {
           m_timer->start(500);
        }
        ui->pushButton_15->setText("停止");
        play = 0;
    }
    else
    {
        if(m_timer->isActive() == true)
        {
            m_timer->stop();
        }
        ui->pushButton_15->setText("开始");
        play = 1;
    }
}

// 另一种方式实现定时器
void MainWindow::on_pushButton_16_clicked()
{
    static int play = 1;
    if (play == 1)
    {
        // 返回定时器ID，timerEvent中会用到，程序只有一个时，可以不判断
        id1 = startTimer(1000);
        id2 = startTimer(1000);
        ui->pushButton_16->setText("停止");
        play = 0;
    }
    else
    {
        killTimer(id1); // 停止
        ui->pushButton_16->setText("开始");
        play = 1;
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1)
    {
        QDateTime dateTime(QDateTime::currentDateTime());
        QString timeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
        ui->label_2->setText(timeStr);
    }
    else if (event->timerId() == id2)
    {
        static int i = 0;
        i++;
        ui->lcdNumber->display(i);
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    delete dlg;
    dlg = new Dialog;

    dlg->setModal(true); // 默认为非模态，这里设为模态
    dlg->show();
}

void MainWindow::on_pushButton_18_clicked()
{
    for (int i = 0; i < 100; i++)
    {
        ui->progressBar->setValue(i+1);

        // 业务操作，如读取文件，发送数据等
        // 延时示例
        for (int j = 0; j < 100000; j++)
            for (int k = 0; k < 100; k++);
    }
}
