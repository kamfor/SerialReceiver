#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/console.h"
#include "../include/settingsdialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QDataStream>
#include <QFile>
#include <QSpacerItem>
#include <QVector>
#include <QDebug>
#include <QScreen>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    console = new Console;
    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    filedata = new QVector<QByteArray>;
    customPlot = new QCustomPlot(this);
    status = new QLabel;

    ui->statusBar->addWidget(status);

    createLayouts();
    initActionsConnections();
    generatePlot();
    connectActions();

    buttons[0]->setEnabled(true);
    buttons[1]->setEnabled(true);
    buttons[2]->setEnabled(true);
    console->setEnabled(false);
    autoscale = true;
    changePlotCaption();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(console, &Console::getData, this, &MainWindow::writeData);
    connect(this, SIGNAL(sendToPlot(double)), this, SLOT(realtimeDataSlot(double)));

}

MainWindow::~MainWindow(){
    delete settings;
    delete serial;
    delete filedata;
    delete console;
    delete ui;
    delete customPlot;
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

    emit sendToPlot(data.toDouble());
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
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionAuto_scale_on, &QAction::triggered, this, &MainWindow::changePlotCaption);
    connect(ui->actionZoom, &QAction::triggered, this, &MainWindow::extendPlotScale);
    connect(ui->actionZoom_2, &QAction::triggered, this, &MainWindow::dropPlotScale);
}

void MainWindow::showStatusMessage(const QString &message){

    status->setText(message);
}

void MainWindow::createLayouts(){

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

    buttonBox->setLayout(layout);

    QGroupBox *left = new QGroupBox;
    QSizePolicy spLeft(QSizePolicy::Maximum, QSizePolicy::Minimum);
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
    mainLayout->addWidget(left);
    mainLayout->addWidget(right);
    QWidget *mainWidget = new QWidget;

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle(tr("SerialReceiver"));
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

void MainWindow::generatePlot(){

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  customPlot->graph(0)->setAntialiasedFill(false);
  //customPlot->addGraph(); // red line
  //customPlot->graph(1)->setPen(QPen(Qt::red));
  //customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  //customPlot->addGraph(); // red dot
  //customPlot->graph(3)->setPen(QPen(Qt::red));
  //customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  //customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  customPlot->replot();
}

void MainWindow::realtimeDataSlot(double value0){

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      // add data to lines:
      customPlot->graph(0)->addData(key, value0);
      //customPlot->graph(1)->addData(key, value1);
      // set data of dots:
      customPlot->graph(1)->clearData();
      customPlot->graph(1)->addData(key, value0);
      //customPlot->graph(3)->clearData();
      //customPlot->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      customPlot->graph(0)->removeDataBefore(key-8);
      //customPlot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      if (autoscale){
          customPlot->graph(0)->rescaleValueAxis();
      }
      //customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    customPlot->replot();
}

void MainWindow::changePlotCaption(){

    if(autoscale){
        autoscale = false;
        ui->actionAuto_scale_on->setText("Auto scale on");
    }
    else{
        autoscale = true;
        ui->actionAuto_scale_on->setText("Auto scale off");
    }
}

void MainWindow::extendPlotScale(){

    if(autoscale == false){
        customPlot->yAxis->setRange(customPlot->yAxis->range()*2);
        customPlot->replot();
    }
}

void MainWindow::dropPlotScale(){

    if(autoscale == false){
        customPlot->yAxis->setRange(customPlot->yAxis->range()/2);
        customPlot->replot();
    }
}

void MainWindow::savePlot(){

}

void MainWindow::connectActions(){
    ctrlplus = new QAction(this);
    ctrlminus = new QAction(this);
    ctrls = new QAction(this);
    ctrlp = new QAction(this);

    ctrlplus->setShortcut(QKeySequence::ZoomIn);
    ctrlminus->setShortcut(QKeySequence::ZoomOut);
    ctrls->setShortcut(QKeySequence::Save);
    ctrlp->setShortcut(QKeySequence::Print);

    connect(ctrlplus, SIGNAL(triggered()), this, SLOT(extendPlotScale()));
    connect(ctrlminus, SIGNAL(triggered()), this, SLOT(dropPlotScale()));
    connect(ctrls, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ctrlp, SIGNAL(triggered()), this, SLOT(savePlot()));

    this->addAction(ctrlplus);
    this->addAction(ctrlminus);
    this->addAction(ctrls);
    this->addAction(ctrlp);
}
