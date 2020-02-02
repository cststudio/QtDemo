#ifndef DLGTAB1_H
#define DLGTAB1_H

#include <QDialog>

// 界面显示中文，文件需要使用UTF8 BOM格式保存，否则乱码--windows vs编译器测试
#pragma execution_character_set("utf-8")


namespace Ui {
class DlgTab1;
}

class DlgTab1 : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTab1(QWidget *parent = nullptr);
    ~DlgTab1();

    void initWindow();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_pushButton_19_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DlgTab1 *ui;
};

#endif // DLGTAB1_H
