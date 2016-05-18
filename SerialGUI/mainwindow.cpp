#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    con = new SerialPort("Baud9600", "NoParity", "OneStop", "Data8", "ttyACM0", "NoFlowControl");
    ui->statusBar->showMessage("Disconnected");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settButton_clicked()
{
    this->settings = new Settings(con,this);
    settings->setModal(true);
    settings->show();
}
