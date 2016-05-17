#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    con = new SerialPort("Baud9600", "NoParity", "OneStop", "Data8", "ttyACM0", "NoFlowControl");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settButton_clicked()
{
    Settings settings(con);
    settings.setModal(true);
    settings.exec();
}
