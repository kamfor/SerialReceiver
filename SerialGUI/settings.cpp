#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->portcombo->addItem("sample");

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ok_clicked()
{
    this->hide();
}

void Settings::on_cancel_clicked()
{
    this->hide();
}
