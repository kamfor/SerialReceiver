#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../app/include/serial.h"
#include "settings.h"
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SerialPort* con;
    Settings* settings;

private slots:

    void on_settButton_clicked();

    void on_ConButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
