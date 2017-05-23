#include "graphdock.h"
#include "ui_graphdock.h"

GraphDock::GraphDock(ProcessorBase *_pProcessor, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GraphDock),
    pProcessor(_pProcessor)
{
    ui->setupUi(this);
    //setupDemo1(ui->QCP);
    //setupDemo2(ui->QCP);
    setupMyDemo(ui->QCP);
}

GraphDock::~GraphDock()
{
    delete ui;
}
/*

void GraphDock::setupFinancialDemo(QCustomPlot *customPlot)
{
  //demoName = "Financial Charts Demo";
  customPlot->legend->setVisible(true);

  // generate two sets of random walk data (one for candlestick and one for ohlc chart):
  int n = 500;
  QVector<int> time(n), value1(n), value2(n);
  QDateTime start = QDateTime(QDate(2014, 6, 11));
  start.setTimeSpec(Qt::UTC);
  double startTime = start.toTime_t();
  double binSize = 3600*24; // bin data in 1 day intervals
  time[0] = startTime;
  value1[0] = 60;
  value2[0] = 20;
  qsrand(9);
  for (int i=1; i<n; ++i)
  {
    time[i] = startTime + 3600*i;
    value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
    value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
  }

  // create bottom axis rect for volume bar chart:
  QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
  customPlot->plotLayout()->addElement(volumeAxisRect);
  volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX/2));
  volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
  volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
  // bring bottom and main axis rect closer together:
  //customPlot->plotLayout()->setRowSpacing(0);
  //volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
  //volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
  // create two bar plottables, for positive (green) and negative (red) volume bars:
  customPlot->setAutoAddPlottableToLegend(false);
  QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  for (int i=0; i<n/5; ++i)
  {
    int v = qrand()%20000+qrand()%20000+qrand()%20000-10000*3;
    (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
  }
  volumePos->setWidth(3600*4);
  volumePos->setPen(Qt::NoPen);
  volumePos->setBrush(QColor(100, 180, 110));
  volumeNeg->setWidth(3600*4);
  volumeNeg->setPen(Qt::NoPen);
  volumeNeg->setBrush(QColor(180, 90, 90));

  // interconnect x axis ranges of main and bottom axis rects:
  //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
  //connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
  // configure axes of both main and bottom axis rect:
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd. MMMM");
  volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
  volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
  customPlot->xAxis->setBasePen(Qt::NoPen);
  customPlot->xAxis->setTickLabels(false);
  customPlot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
  customPlot->xAxis->setTicker(dateTimeTicker);
  customPlot->rescaleAxes();
  //customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
  //customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

  // make axis rects' left side line up:
  QCPMarginGroup *group = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
  volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);
}

*/

void GraphDock::setupDemo1(QCustomPlot *customPlot)
{
    // add two new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

void GraphDock::setupDemo2(QCustomPlot *customPlot)
{
    // set locale to english, so we get english month names:
   // customPlot->setLocale(QLocale::China);
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:
    for (int gi=0; gi<5; ++gi)
    {
      customPlot->addGraph();
      QColor color(20+200/4.0*gi,70*(1.6-gi/4.0), 150, 150);
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(QPen(color.lighter(200)));
      customPlot->graph()->setBrush(QBrush(color));
      // generate random walk data:
      QVector<QCPGraphData> timeData(250);
      for (int i=0; i<250; ++i)
      {
        timeData[i].key = now + 24*3600*i;
        if (i == 0)
          timeData[i].value = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
        else
          timeData[i].value = qFabs(timeData[i-1].value)*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      }
      customPlot->graph()->data()->set(timeData);
    }
    // configure bottom axis to show date instead of number:
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    customPlot->xAxis->setTicker(dateTicker);
    // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(10, "a bit\nlow");
    textTicker->addTick(50, "quite\nhigh");
    customPlot->yAxis->setTicker(textTicker);
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, now+24*3600*249);
    customPlot->yAxis->setRange(0, 60);
    // show legend with slightly transparent background brush:
    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void GraphDock::setupMyDemo(QCustomPlot *customPlot)
{
    //customPlot->setLocale(QLocale::China);
    QVector<double> time_double;
    QVector<QVector<double>> value_double;
    QVector<double> temp;
    const QVector<QDate> & time_date = pProcessor->getXvector();
    const QVector<QString> & names = pProcessor->getYvector();
    const QVector<QVector<int>> &value = pProcessor->getMatrix();

//    std::cout << time_date[0].toString("dd.MM.yyyy").toStdString() << std::endl;
//    std::cout << names.size() << std::endl;
//    std::cout << time_date.size() << std::endl;
    //std::cout << Y.size() << std::endl;
    //std::cout << Y.size() << std::endl;

    for(int i = 0; i < names.size(); i++)
    {
        for(int j = 0; j < time_date.size(); j++)
            temp.push_back((double)value[i][j]);
        value_double.push_back(temp);
        temp.clear();
     }
    for(int i = 0; i < time_date.size(); ++i)
        time_double.push_back( (double)QDateTime(time_date[i]).toTime_t());


    for (int gi=0; gi < names.size(); ++gi)
    {
      customPlot->addGraph();
      QColor color(20+300/4.0*gi,70*(1.6-gi/4.0), 150, 200);
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(QPen(color.lighter(200)));
      customPlot->graph()->setName(names[gi]);
      customPlot->graph()->setData(time_double, value_double[gi]);
      //customPlot->graph()->setBrush(QBrush(color));
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    //customPlot->graph(0)->setData(time_double, value_double[0]);
    //customPlot->graph(1)->setData(x, y1);


    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    customPlot->xAxis->setTicker(dateTicker);
    // configure left axis text labels:
    //QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    //textTicker->addTick(10, "a bit\nlow");
    //textTicker->addTick(50, "quite\nhigh");
    //customPlot->yAxis->setTicker(textTicker);
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Quantity");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    //double now = QDateTime::currentDateTime().toTime_t();
    customPlot->graph()->rescaleAxes();
    //customPlot->xAxis->setRange(now-24*3600*10, now);
    //customPlot->yAxis->setRange(0.0, 10.0);
    // show legend with slightly transparent background brush:
    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}
