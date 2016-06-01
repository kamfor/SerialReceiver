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
    //! Konstruktor klasy
    /*!
        Inicjalizacja sygnałów i slotów
    */
    explicit SettingsDialog(QWidget *parent = 0);

    //! Destruktor
    ~SettingsDialog();

    //! Metoda klasy
    /*!
        \zwraca akrualne ustawienia
    */
    Settings settings() const;

private slots:
    //! Slot klasy
    /*!
        \parametr idx - identyfikator wykonania
    */
    void showPortInfo(int idx);
    //! Slot klasy
    /*!
        wywoływany po naciśnięciu przycisku ok
    */
    void apply();
    //! Slot klasy
    /*!
        sprawdza czy wporowadzona przez użytkownika wartość  prędkości jest możliwa
        \parametr idx - wartość do sprawdzenia 
    */
    void checkCustomBaudRatePolicy(int idx);
    //! Slot klasy
    /*!
        sprawdza czy wporowadzona przez użytkownika nazwa portu jest możliwa
        \parametr idx - wartość do sprawdzenia 
    */
    void checkCustomDevicePathPolicy(int idx);

private:
    //! Metoda klasy
    /*!
        ustawia mozliwe do wyboru wartosci w listach
    */
    void fillPortsParameters();
    //! Metoda klasy
    /*!
        wypisuje informacje o akualnie wybranym porcie
    */
    void fillPortsInfo();
    //! Metoda klasy
    /*!
        przypisuje własciwości połączenia do obiektu typu Serial
    */
    void updateSettings();

private:
    Ui::SettingsDialog *ui;
    //! Obiekt klasy Settings
    Settings currentSettings;
    //! Obiekt klasy QIntValidator z biblioteki Qt
    QIntValidator *intValidator;
};

#endif // SETTINGSDIALOG_H
