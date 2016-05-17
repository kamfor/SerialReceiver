#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "../app/include/serial.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(SerialPort*, QWidget *parent = 0);
    ~Settings();
    SerialPort* con;

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
