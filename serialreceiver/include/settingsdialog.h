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

//!  Klasa SettingsDialog
/*!
    Klasa okna dialogowego ustawień portu szeregowego. 
*/
class SettingsDialog : public QDialog{

    Q_OBJECT

public:

//! Struktura Settings
/*! Zawiera obiekty klasy QSerialPort i ich nazwy */
    struct Settings {
        QString name; /*!< Nazwa portu */ 
        qint32 baudRate; /*!< Szybkosc transmisji */ 
        QString stringBaudRate; /*!< Szybkość transmisji string */ 
        QSerialPort::DataBits dataBits; /*!< Obiekt liczby bitów danych */ 
        QString stringDataBits; /*!< Liczba bitów danych */ 
        QSerialPort::Parity parity; /*!< Obiekt parzystości */ 
        QString stringParity; /*!< Nazwa parzystości */ 
        QSerialPort::StopBits stopBits; /*!< Obiekt bitów stopu */ 
        QString stringStopBits; /*!< Nazwa bitów stopu */ 
        QSerialPort::FlowControl flowControl; /*!< Obiekt kontroli przepływu */ 
        QString stringFlowControl; /*!< Nazwa kontroli przepływu */ 
        QString stringSpacer; /*!< Znak rozdzielajacy ramki */
    };
//! Konstruktor klasy
/*!
    Inicjalizacja sygnałów i slotów
*/
    explicit SettingsDialog(QWidget *parent = 0);

//! Destruktor
    ~SettingsDialog();

//! settings
/*!
    \retval Setttings akrualne ustawienia
*/
    Settings settings() const;

private slots:

//! showPortInfo
/*!
    \param idx - identyfikator wykonania
*/
    void showPortInfo(int idx);

//! apply
/*!
    wywoływany po naciśnięciu przycisku ok
*/
    void apply();

//! checkCustomBaudRatePolicy
/*!
    sprawdza czy wporowadzona przez użytkownika wartość  prędkości jest możliwa
    \param idx - wartość do sprawdzenia 
*/
    void checkCustomBaudRatePolicy(int idx);

//! checkCustomDevicePathPolicy
/*!
    sprawdza czy wporowadzona przez użytkownika nazwa portu jest możliwa
    \param idx - wartość do sprawdzenia 
*/
    void checkCustomDevicePathPolicy(int idx);

//! CustomSpacerPolicy
/*!
    konfiguruje pole do wpisania nietypowego znamku rozdzielajacego
*/
    void CustomSpacerPolicy();

private:

//! fillPortsParameters
/*!
    ustawia mozliwe do wyboru wartosci w listach
*/
    void fillPortsParameters();

//! fillPortsInfo
/*!
    wypisuje informacje o akualnie wybranym porcie
*/
    void fillPortsInfo();

//! updateSettings
/*!
    przypisuje własciwości połączenia do obiektu typu Serial
*/
    void updateSettings();

    Ui::SettingsDialog *ui;

//! Obiekt klasy Settings
    Settings currentSettings;
    
//! Obiekt klasy QIntValidator z biblioteki Qt
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
