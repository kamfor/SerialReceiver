#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/console.h"
#include "../include/settingsdialog.h"
#include "../include/plot.h"

#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);

    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    //plot = new Plot(this);
    filedata = new QVector<QByteArray>;
    customPlot = new QCustomPlot(this);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    createButtonBox();
    initActionsConnections();

    buttons[0]->setEnabled(true);
    buttons[1]->setEnabled(true);
    buttons[2]->setEnabled(true);

    QGroupBox *left = new QGroupBox;
    QSizePolicy spLeft(QSizePolicy::Minimum, QSizePolicy::Minimum);
    spLeft.setVerticalStretch(2);
    left->setSizePolicy(spLeft);
    QVBoxLayout *leftlayout = new QVBoxLayout;
    leftlayout->addWidget(console);
    leftlayout->addWidget(buttonBox);
    left->setLayout(leftlayout);

    QGroupBox *right = new QGroupBox;
    QSizePolicy spRight(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spRight.setVerticalStretch(2);
    right->setSizePolicy(spRight);
    QVBoxLayout *rightlayout = new QVBoxLayout;
    rightlayout->addSpacerItem(new QSpacerItem(600,1));
    rightlayout->addWidget(customPlot,1000);
    right->setLayout(rightlayout);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    //mainLayout->addWidget(console);
    //mainLayout->addWidget(buttonBox);
    mainLayout->addWidget(left);
    mainLayout->addWidget(right);
    QWidget *mainWidget = new QWidget;

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle(tr("SerialReceiver"));


    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(console, &Console::getData, this, &MainWindow::writeData);

    //connect(this, SIGNAL(sendToPlot(double,double)), plot, SLOT(realtimeDataSlot(double,double))); make it in one window

}

MainWindow::~MainWindow(){
    delete settings;
    delete serial;
    delete filedata;
    delete console;
    delete ui;
    delete plot;
}

void MainWindow::openSerialPort(){
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        buttons[0]->setEnabled(false);
        buttons[1]->setEnabled(false);
        buttons[2]->setEnabled(true);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort(){
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    buttons[0]->setEnabled(true);
    buttons[1]->setEnabled(true);
    buttons[2]->setEnabled(false);
    showStatusMessage(tr("Disconnected"));
}

void MainWindow::about(){

    QMessageBox::about(this, tr("O programie"),
                       tr("Serial Receiver to prosty program bazujązy na bibliotece Qt \n"
                          "umożliwia odbieranie i analize dancych z portu szeregowego"));
}

void MainWindow::openSettings(){

    settings->show();
}

void MainWindow::openPlot(){

    plot->show();
    plot->generatePlot();
}

void MainWindow::clearConsole(){

    console->clear();
    filedata->clear();
}

void MainWindow::writeData(const QByteArray &data){

    serial->write(data);
}

void MainWindow::readData(){

    QByteArray data = serial->readAll();
    console->putData(data);
    filedata->push_back(data);
    data = data.simplified();

    qDebug() <<data.toDouble();

    emit sendToPlot(data.toDouble(),0);
}


void MainWindow::handleError(QSerialPort::SerialPortError error){

    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections(){

    connect(buttons[0], SIGNAL (released()), this, SLOT (openSettings()));
    connect(buttons[1], SIGNAL (released()), this, SLOT (openSerialPort()));
    connect(buttons[2], SIGNAL (released()), this, SLOT (closeSerialPort()));
    connect(buttons[3], SIGNAL (released()), this, SLOT (clearConsole()));
    connect(buttons[4], SIGNAL (released()), this, SLOT (openPlot()));
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

void MainWindow::showStatusMessage(const QString &message){

    status->setText(message);
}

void MainWindow::createButtonBox(){

    buttonBox = new QGroupBox(tr("Menu"));
    QHBoxLayout *layout = new QHBoxLayout;


    buttons[0] = new QPushButton("Settings",this);
    layout->addWidget(buttons[0]);
    buttons[1] = new QPushButton("Connect",this);
    layout->addWidget(buttons[1]);
    buttons[2] = new QPushButton("Disconnect",this);
    layout->addWidget(buttons[2]);
    buttons[3] = new QPushButton("Clear",this);
    layout->addWidget(buttons[3]);
    buttons[4] = new QPushButton("Plot",this);
    layout->addWidget(buttons[4]);

    buttonBox->setLayout(layout);
}

void MainWindow::saveFile(){

    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),tr(""),tr("Text Files(*.txt)"));
    QFile file(filename);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    for(int i=0; i<filedata->size();i++){
            file.write(filedata->at(i));
    }
    file.close();

}
