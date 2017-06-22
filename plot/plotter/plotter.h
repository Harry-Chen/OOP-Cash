//产品系列2的基类
#ifndef PLOTTER_H
#define PLOTTER_H

#include <qcustomplot.h>

class Plotter : public QWidget
{

public:
    Plotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector< QVector<int> > _values)
        :fieldnames_(_fieldnames),
          dates_(_dates),
          values_(_values)
    {}
    virtual void plot(QCustomPlot * custom_plot) = 0;
    virtual ~Plotter(){}
protected:
    const QVector<QString> fieldnames_;
    const QVector<QDate> dates_;
    const QVector< QVector<int> > values_;
};

#endif // PLOTTER_H
