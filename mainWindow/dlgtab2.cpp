#include "dlgtab2.h"
#include "ui_dlgtab2.h"

dlgtab2::dlgtab2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgtab2)
{
    ui->setupUi(this);

    initWindow();
    //paintSerial();
}

dlgtab2::~dlgtab2()
{
    delete ui;
}

void dlgtab2::initWindow()
{
    m_rect.setRect(50,50,50,50);
    m_zoom = 1.0;

}

void dlgtab2::paintPixmap()
{
    QPainter p(this);
    QBrush brush;
    QPen pen;

    //设置坐标系
    p.translate(CurrentCoordinates);
    //反锯齿
    p.setRenderHint(QPainter::Antialiasing);
    //设置画笔颜色，边框的颜色
    brush.setColor(Qt::blue);
    //设置填充的风格，不设置默认不填充
    brush.setStyle(Qt::SolidPattern);
    //设置画刷的颜色，矩形填充的颜色
    pen.setColor(Qt::red);
    //将画笔和画刷给QPainter
    p.setPen(pen);
    p.setBrush(brush);
    //画矩形
    p.drawRect(m_rect);
}


//放大缩小函数
void dlgtab2::zoomPixmap()
{
    float width,hight;

    width = m_rect.width();
    hight = m_rect.height();
    width = width*m_zoom;
    hight = hight*m_zoom;
    m_rect.setWidth(width);
    m_rect.setHeight(hight);
}
//鼠标按键按下事件
void dlgtab2::mousePressEvent(QMouseEvent *ev)
{
    //鼠标按下时记录当前按下的坐标
    if(ev->button() == Qt::LeftButton)
    {
        if(ev->x()>m_rect.x() && ev->x()<m_rect.x()+m_rect.width())
        {
            if(ev->y()>m_rect.y() && ev->y()<m_rect.y()+m_rect.height())
            {
                LastCoordinates = ev->pos();
            }
        }
    }
}
//鼠标滚轮事件
void dlgtab2::wheelEvent(QWheelEvent *ev)
{

    //如果滚轮向上滚动就放大尺寸
    if(ev->delta() > 0)
    {
        m_zoom = 1.1;
    }
    else//如果滚轮向下滚动就缩小尺寸
    {
        m_zoom = 0.9;
    }
    zoomPixmap();
    update();
}
//鼠标移动事件
void dlgtab2::mouseMoveEvent(QMouseEvent *ev)
{
    //当鼠标左键按下且移动
    if(ev->buttons() & Qt::LeftButton){
        //计算当前需要移动的距离，保存本次的坐标
        CurrentCoordinates = CurrentCoordinates - LastCoordinates + ev->pos();
        LastCoordinates = ev->pos();
        ev->accept();
        this->update();
    }
}

void dlgtab2::paintSimple()
{
    QPainter painter(this);
    painter.setPen(Qt::blue);

    // 画圆，椭圆 参数需要的是矩形，画的是矩形的内接椭圆，如果矩形为正方形，则画的是圆形。
    painter.drawEllipse(100, 100, 50, 50);

    painter.drawRect(100, 100, 50, 50);

    painter.drawLine(100, 100, 150, 150);

    // 画点，并设置大小、颜色
    QPen pen = painter.pen();
    pen.setStyle(Qt::DotLine); // SolidLine
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(125, 125);

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

void dlgtab2::paintSerial()
{
    QChart* m_chart = new QChart();
    QSplineSeries *series1 = new QSplineSeries();//实例化一个QLineSeries对象
    series1->setColor(QColor(0,100,255));
    series1->append(QPointF(0,qrand()%200)) ;
    series1->append(QPointF(30,qrand()%200)) ;
    series1->append(QPointF(60,qrand()%200)) ;
    series1->append(QPointF(90,qrand()%200)) ;
    series1->append(QPointF(120,qrand()%200)) ;
    series1->setName("线条1");

    series1->setVisible(true);
    series1->setPointLabelsFormat("(@xPoint,@yPoint)");
    series1->setPointLabelsVisible(true);


    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    m_chart->setDropShadowEnabled(true);//背景阴影
    m_chart->setAutoFillBackground(true);  //设置背景自动填充

    m_chart->addSeries(series1);//添加系列到QChart上


    m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    m_chart->setTitle("曲线图");



    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,150);    //默认则坐标为动态计算大小的
    axisX->setLabelFormat("%dS");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,250);    //默认则坐标为动态计算大小的
    axisY->setTitleText("value值");

    m_chart->setAxisX(axisX,series1);
    m_chart->setAxisY(axisY,series1);
    //m_chart->createDefaultAxes();             //或者创建默认轴

    //修改说明样式
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    m_chart->legend()->setMaximumHeight(50);
    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(chartView);

    resize(960, 720);
}

void dlgtab2::paintPie()
{
    QChart* m_chart = new QChart();

        QPieSeries *series = new QPieSeries();
        series->append("水果:30%",3);     //添加标签"水果:30%" 和 百分值30%
        series->append("零食:20%",2);
        series->append("主食:50%",5);

        series->setLabelsVisible(true);
        series->setUseOpenGL(true);
        series->slices().at(0)->setColor(QColor(13,128,217));   //设置颜色
        series->slices().at(0)->setLabelColor(QColor(13,128,217));

        series->slices().at(1)->setColor(QColor(69,13,217));
        series->slices().at(1)->setLabelColor(QColor(69,13,217));

        series->slices().at(2)->setColor(QColor(13,217,152));
        series->slices().at(2)->setLabelColor(QColor(13,217,152));

        m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
        m_chart->setDropShadowEnabled(true);//背景阴影
        m_chart->addSeries(series);//添加系列到QChart上

        m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
        m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
        m_chart->setTitle("饼状图");

        //修改说明样式
        m_chart->legend()->setVisible(true);
        m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
        m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
        m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
        m_chart->legend()->setMaximumHeight(50);

        QChartView *chartView = new QChartView(m_chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QVBoxLayout *pVLayout = new QVBoxLayout(this);
        pVLayout->addWidget(chartView);

        resize(960, 720);
}

void dlgtab2::paintBar()
{
    QChart* m_chart = new QChart();

        //创建3个条线数据
        QBarSet *set0 = new QBarSet("零食");
        QBarSet *set1 = new QBarSet("水果");
        QBarSet *set2 = new QBarSet("主食");

        *set0 << 158 << 685 << 458 << 260 << 354;    //向零食数据添加这4个月的销售数据
        *set1 << 350 << 725 << 602 << 523 << 458;
        *set2 << 222 << 350 << 598 << 480 << 687;

        set0->setLabelColor(QColor(0,0,255));       //设置条形数据颜色
        set1->setLabelColor(QColor(0,0,255));
        set2->setLabelColor(QColor(0,0,255));

        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->setVisible(true);
        series->setLabelsVisible(true);

        m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
        m_chart->setDropShadowEnabled(true);//背景阴影
        m_chart->addSeries(series);//添加系列到QChart上

        m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
        m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
        m_chart->setTitle("超市销售条形图");

        //创建X轴和Y轴
        QBarCategoryAxis *axisX = new QBarCategoryAxis;
        axisX->append("一月");
        axisX->append("二月");
        axisX->append("三月");
        axisX->append("四月");
        axisX->append("五月");
        axisX->setLabelsColor(QColor(7,28,96));

        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0,1000);   //改为setRange(0,1);则表示坐标为动态计算大小的
        axisY->setTitleText("价格");
        axisY->setLabelFormat("%d$");

        m_chart->setAxisX(axisX,series);
        m_chart->setAxisY(axisY,series);

        //修改说明样式
        m_chart->legend()->setVisible(true);
        m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
        m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
        m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
        m_chart->legend()->setMaximumHeight(50);

        QChartView *chartView = new QChartView(m_chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QVBoxLayout *pVLayout = new QVBoxLayout(this);
        pVLayout->addWidget(chartView);

        resize(960, 720);
}

void dlgtab2::paintEvent(QPaintEvent *event)
{
    //paintSimple();
    //paintSerial();
    paintPixmap();
}

void dlgtab2::on_pushButton_clicked()
{
    paintSerial();
}

void dlgtab2::on_pushButton_2_clicked()
{
    paintPie();
}

void dlgtab2::on_pushButton_3_clicked()
{
    paintBar();
}
