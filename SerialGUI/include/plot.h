#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include "../plots/qcustomplot.h"

namespace Ui {
class Plot;
}

//!  QDialog class for handling plot finctions
/*!
  Class contains methods to handle and generate realdata plots.
*/
class Plot : public QDialog
{
    Q_OBJECT

public:
    //! A constructor.
    /*!
      Constructor
    */
    explicit Plot(QWidget *parent = 0);

    //! A destructor.
    /*!
      A more elaborate description of the destructor.
    */
    ~Plot();

    //! A normal member taking two arguments and returning an integer value.
    /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
    void generatePlot();


private:
    Ui::Plot *ui;
    QCustomPlot *customPlot;

private slots:
    //! A pure virtual member.
    /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
    void realtimeDataSlot(double,double);

};

#endif // PLOT_H
