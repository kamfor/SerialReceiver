#include "../include/plot.h"
#include "ui_plot.h"
#include <QVector>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

Plot::Plot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    customPlot = ui->widget;
    generatePlot();
}

Plot::~Plot()
{
    delete ui;
    delete customPlot;
}

void Plot::generatePlot(){

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  customPlot->graph(0)->setAntialiasedFill(false);
  //customPlot->addGraph(); // red line
  //customPlot->graph(1)->setPen(QPen(Qt::red));
  //customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  //customPlot->addGraph(); // red dot
  //customPlot->graph(3)->setPen(QPen(Qt::red));
  //customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  //customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  customPlot->replot();
}

void Plot::realtimeDataSlot(double value0, double value1){

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      // add data to lines:
      customPlot->graph(0)->addData(key, value0);
      //customPlot->graph(1)->addData(key, value1);
      // set data of dots:
      customPlot->graph(1)->clearData();
      customPlot->graph(1)->addData(key, value0);
      //customPlot->graph(3)->clearData();
      //customPlot->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      customPlot->graph(0)->removeDataBefore(key-8);
      //customPlot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      customPlot->graph(0)->rescaleValueAxis();
      //customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    customPlot->replot();
}
