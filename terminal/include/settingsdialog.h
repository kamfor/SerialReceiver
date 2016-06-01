#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class SettingsDialog;
}

class QIntValidator;

QT_END_NAMESPACE

//!  Klasa okna dialogowego
/*!
    Klasa okna dialogowego ustawień portu szeregowego. 
*/
class SettingsDialog : public QDialog{

    Q_OBJECT

public:

    //! Struktura ustawień
    /*! Zawiera obiekty klasy QSerialPort i ich nazwy */
    struct Settings {
        QString name;/*!< Nazwa portu */ 
        qint32 baudRate;/*!< Szybkosc transmisji */ 
        QString stringBaudRate;/*!< Szybkość transmisji string */ 
        QSerialPort::DataBits dataBits;/*!< Obiekt liczby bitów danych */ 
        QString stringDataBits;/*!< Liczba bitów danych */ 
        QSerialPort::Parity parity;/*!< Obiekt parzystości */ 
        QString stringParity;/*!< Nazwa parzystości */ 
        QSerialPort::StopBits stopBits;/*!< Obiekt bitów stopu */ 
        QString stringStopBits;/*!< Nazwa bitów stopu */ 
        QSerialPort::FlowControl flowControl;/*!< Obiekt kontroli przepływu */ 
        QString stringFlowControl;/*!< Nazwa kontroli przepływu */ 
    };

    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    Settings settings() const;

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SettingsDialog *ui;
    Settings currentSettings;
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
