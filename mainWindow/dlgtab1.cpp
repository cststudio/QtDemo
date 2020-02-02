#include "dlgtab1.h"
#include "ui_dlgtab1.h"

DlgTab1::DlgTab1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTab1)
{
    ui->setupUi(this);

    initWindow();
}

DlgTab1::~DlgTab1()
{
    delete ui;
}

// 布局、控件、信号等初始化
void DlgTab1::initWindow()
{

    ui->lineEdit->setPlaceholderText("username");
    ui->lineEdit->setText("lineEdit");
    //ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setAlignment(Qt::AlignHCenter);
    ui->lineEdit->setMaxLength(12);
    //QFont qFont;
    QFont qFont("Times", 10, QFont::Bold);
    qFont.setBold(true);
    ui->lineEdit->setFont(qFont);

    // QLineEdit::Password 文字用圆点替换，
    // QLineEdit::PasswordEchoOnEdit 输入时显示，结束后圆点替换
    // QLineEdit::NoEcho // 不显示任何内容，用于长度保护
    ui->lineEdit->setEchoMode(QLineEdit::Password);


    ui->plainTextEdit->setPlaceholderText("sth text here");
    ui->plainTextEdit->setPlainText("foo\r\n");
    ui->plainTextEdit->appendHtml("<font color=\"red\"> red </font>");
    ui->plainTextEdit->appendPlainText("add");
    ui->plainTextEdit->setFont(qFont);
    //ui->plainTextEdit->setReadOnly(true);


    ui->textEdit->setPlaceholderText("sth text here");
    ui->textEdit->setText("foo\r\n");
    ui->textEdit->append("<font color=\"red\"> red </font>");
    //ui->textEdit->setFont(qFont);
    //ui->textEdit->setReadOnly(true);

    //ui->textBrowser->setHtml("a<br>b");
    ui->textBrowser->setText("hello world\n");
    ui->textBrowser->append("a<br>b");

}

void DlgTab1::on_lineEdit_textChanged(const QString &arg1)
{
    QString strUsername = ui->lineEdit->text();
    ui->plainTextEdit->setPlainText(strUsername);
}

void DlgTab1::on_lineEdit_editingFinished()
{
    QString strUsername = ui->lineEdit->text();
    ui->textEdit->setPlainText(strUsername);
}


#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
void DlgTab1::on_pushButton_19_clicked()
{
    QStringListModel *Model = NULL;
    QStandardItemModel *ItemModel = NULL;

    ItemModel = new QStandardItemModel(this);

    QStringList lst;
    lst << "foo" << "bar" << "123" << "hello world";

    QList<QStandardItem *> items;

    foreach (QString itm, lst)
    {
        QStandardItem *item = new QStandardItem(itm);
        items.push_back(item);
        //ItemModel->appendRow(item);
        //ItemModel->appendColumn(item);
    }
    ItemModel->appendColumn(items);

    ui->listView->setModel(ItemModel);
    // 复杂的应用待议
}

void DlgTab1::on_listView_doubleClicked(const QModelIndex &index)
{
    QString strTemp;
    strTemp = index.data().toString();
//    QMessageBox msg;
//    msg.setText(strTemp);
//    msg.exec();
//    showDebugInfo(strTemp);
}

void DlgTab1::on_pushButton_20_clicked()
{
    QStandardItemModel* model = new QStandardItemModel(5, 3, this);
    ui->tableView->setModel(model);

    // 头部
    QStringList headList;
    headList << "序号" << "姓名" << "年龄";
    for (int i = 0; i < headList.size(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, headList.at(i));
        ui->tableView->setColumnWidth(i, 40); // 宽度
    }

    // 序号
    for (int i = 0; i < 5; i++)
    {
        QStandardItem *item = new QStandardItem(QString::number(i+1));
        model->setItem(i, 0, item);
        model->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
    }

    // 数据
    model->setItem(0, 1, new QStandardItem("Jim"));
    model->setItem(0, 2, new QStandardItem("35"));
    model->setItem(1, 1, new QStandardItem("Tom"));
    model->setItem(1, 2, new QStandardItem("32"));

    // 隔一行变色，用以区分
    ui->tableView->setAlternatingRowColors(true);
}

void DlgTab1::on_pushButton_21_clicked()
{
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    ui->treeView->setModel(model);

    // 头部
    QStringList headList;
    headList << "树形列表";
    model->setHorizontalHeaderLabels(headList);

    QStandardItem* itemProject = new QStandardItem("项目");
    model->appendRow(itemProject);

    QStandardItem* itemChild = new QStandardItem("子项");
    itemProject->appendRow(itemChild);

    QStandardItem* itemChild11 = new QStandardItem("子子项");
    itemChild->appendRow(itemChild11);

    QStandardItem* itemChild2 = new QStandardItem("子项2");
    itemProject->appendRow(itemChild2);
#if 0
    // 头部
    QStringList headList;
    headList << "项目" << "详细信息";
    model->setHorizontalHeaderLabels(headList);
    //ui->treeView->setColumnWidth(0, 40); // 第一列宽度

    QStandardItem* itemProject = new QStandardItem("项目");
    model->appendRow(itemProject);
    model->setItem(model->indexFromItem(itemProject).row(), 1, new QStandardItem("项目信息说明"));

    QStandardItem* itemChild = new QStandardItem("子项");
    itemProject->appendRow(itemChild);

    itemProject->setChild(itemChild->index().row(), 1, new QStandardItem("信息说明"));

    QStandardItem* itemChild11 = new QStandardItem("子子项");
    itemChild->appendRow(itemChild11);

    QStandardItem* itemChild2 = new QStandardItem("子项2");
    itemProject->appendRow(itemChild2);
#endif

}

void DlgTab1::on_pushButton_clicked()
{
    QStringList applications;

    for (int i = 1; i <= 30; ++i)
        applications.append(tr("Application %1").arg(i));
    ui->listWidget->insertItems(0, applications);
}

void DlgTab1::on_pushButton_2_clicked()
{
    // TODO：去掉默认的序号？？
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setAlternatingRowColors(true);
    for (int i = 0; i < 5; i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(i+1));
        ui->tableWidget->setItem(i, 0, newItem);
    }

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(tr("Jim")));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(tr("Tom")));
}

void DlgTab1::on_pushButton_3_clicked()
{
    ui->treeWidget->setHeaderItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("treeHeader"))));

    ui->treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    ui->treeWidget->insertTopLevelItems(0, items);
}
