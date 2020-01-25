#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    int m_opened;

signals:
    void sig_backMain(int a, int b); // 通知主界面信号，参数仅作示例

public slots:
    void myshow();
    void myclose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
