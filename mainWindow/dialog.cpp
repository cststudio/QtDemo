#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_opened = 0;
}

Dialog::~Dialog()
{
    delete ui;
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
