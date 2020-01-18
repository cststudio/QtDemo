#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>

#include <QDateTime>
#include <QDebug>

#include "dialog.h"

// 界面显示中文，文件需要使用UTF8 BOM格式保存，否则乱码--windows vs编译器测试
#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void initMainWindow();
    void initWindow();
    void initStatusBar();

    void mousePressEvent(QMouseEvent *event); // 鼠标按下
    void mouseMoveEvent(QMouseEvent *event); // 鼠标移动
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放
    void mouseDoubleClickEvent(QMouseEvent *event); // 鼠标双击

    int m_pressMouse; // 当点击下拉框时，窗口跳动，加上判断
    QPoint m_startPos;
    QPoint m_windowPos;

    bool eventFilter(QObject *watched, QEvent *event);
    void keyPressEvent(QKeyEvent *event);   // 按键按下
    void keyReleaseEvent(QKeyEvent *event); // 按键释放


    QLabel* m_stsEmpty;
    QLabel* m_stsDebugInfo;
    QLabel* m_stsSysTime;
    QLabel* m_stsCopyright;
    QLabel* m_stsExit;

signals:
    void sig_exit();

private slots:
    void on_reshow(int a, int b); // 必须是slot

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    Dialog* dlg;
};
#endif // MAINWINDOW_H
