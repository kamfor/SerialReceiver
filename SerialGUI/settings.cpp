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
