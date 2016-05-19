#include "settings.h"
#include "ui_settings.h"


Settings::Settings(SerialPort *connection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    con = connection;
    QString item;
    for(con->portname.current = con->portname.value.begin(); con->portname.current!=con->portname.value.end(); con->portname.current++){
        item = QString::fromStdString(con->portname.getstring());
        ui->portcombo->addItem(item);
    }
    for(con->baudrate.current = con->baudrate.value.begin(); con->baudrate.current!=con->baudrate.value.end(); con->baudrate.current++){
        item = QString::fromStdString(con->baudrate.getstring());
        ui->baudcombo->addItem(item);
    }
    for(con->databits.current = con->databits.value.begin(); con->databits.current!=con->databits.value.end(); con->databits.current++){
        item = QString::fromStdString(con->databits.getstring());
        ui->datacombo->addItem(item);
    }
    for(con->stopbits.current = con->stopbits.value.begin(); con->stopbits.current!=con->stopbits.value.end(); con->stopbits.current++){
        item = QString::fromStdString(con->stopbits.getstring());
        ui->stopcombo->addItem(item);
    }
    for(con->parity.current = con->parity.value.begin(); con->parity.current!=con->parity.value.end(); con->parity.current++){
        item = QString::fromStdString(con->parity.getstring());
        ui->paritycombo->addItem(item);
    }
    for(con->flowcontrol.current = con->flowcontrol.value.begin(); con->flowcontrol.current!=con->flowcontrol.value.end(); con->flowcontrol.current++){
        item = QString::fromStdString(con->flowcontrol.getstring());
        ui->flowcombo->addItem(item);
    }
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ok_clicked()
{
    QString temp;
    temp = ui->portcombo->currentText();
    con->portname.set(temp.toStdString());
    temp = ui->baudcombo->currentText();
    con->baudrate.set(temp.toStdString());
    temp = ui->datacombo->currentText();
    con->databits.set(temp.toStdString());
    temp = ui->stopcombo->currentText();
    con->stopbits.set(temp.toStdString());
    temp = ui->paritycombo->currentText();
    con->parity.set(temp.toStdString());
    temp = ui->flowcombo->currentText();
    con->flowcontrol.set(temp.toStdString());
    QMessageBox::information(this,QString::fromStdString(con->baudrate.getstring()),tr("ok"));
    this->hide();
}

void Settings::on_cancel_clicked()
{
    this->hide();
}
