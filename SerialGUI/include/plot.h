#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include "../plots/qcustomplot.h"

namespace Ui {
class Plot;
}

class Plot : public QDialog
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = 0);
    ~Plot();
    void generatePlot();


private:
    Ui::Plot *ui;
    QCustomPlot *customPlot;

private slots:
    void realtimeDataSlot(double,double);

};

#endif // PLOT_H
