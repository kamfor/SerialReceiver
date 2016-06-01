#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QVector>
#include <QAction>
#include "../plots/qcustomplot.h"


QT_BEGIN_NAMESPACE

class QLabel;
class QGroupBox;
class QPushButton;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;
class Plot;

//!  Klasa okna głównego
/*!
    Klasa głownego okna aplikacji 
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Konstruktor klasy
    /*!
        Połączenie sygnałów i slotów, konfiguracja rozmieszczenia elementów
    */
    explicit MainWindow(QWidget *parent = 0);

    //! Destruktor
    ~MainWindow();

private slots:
    //! Slot klasy
    /*!
        Otwiera potr szeregowy o parametrach z klasy serial
    */
    void openSerialPort();
    //! Slot klasy
    /*!
        \parametr idx - identyfikator wykonania
    */
    void closeSerialPort();
    //! Slot klasy
    /*!
        otwiera okno klasy settings
    */
    void openSettings();
    //! Slot klasy
    /*!
        czysci konsolę wyświetlania
    */
    void clearConsole();
    //! Slot klasy
    /*!
        wyświetla informacje o programie
    */
    void about();
    //! Slot klasy
    /*!
        wysyła dane określone jako parametr (opcjonalnie)
        \parametr data danew do wysłania
    */
    void writeData(const QByteArray &data);
    //! Slot klasy
    /*!
        czyta dane z portu szeregowego i wysyła do konsoli bądź wykresu
    */
    void readData();
    //! Slot klasy
    /*!
        obsługa błędów komunikacji szeregowej
        \parametr error - typ błędu otwarcia portu
    */
    void handleError(QSerialPort::SerialPortError error);
    //! Slot klasy
    /*!
        zapisuje dane z konsoli wyświetlania do pliku
    */
    void saveFile();
    //! Slot klasy
    /*!
        dodaje punkt do wykresu
        \parametr int - aktualna wartość do wykresu
    */
    void realtimeDataSlot(int);
    //! Slot klasy
    /*! 
        \parametr idx - identyfikator wykonania
    */
    void changePlotCaption();
    //! Slot klasy
    /*!
        zmienia sposób skalowania wykresu
    */
    void savePlot();
    //! Slot klasy
    /*!
        zapisuje wykres jako plik graficzny
    */
    void extendPlotScale();
    //! Slot klasy
    /*!
        zwiększa skalę wykresu
    */
    void dropPlotScale();
    //! Slot klasy
    /*!
        \zmniejsza skalę wykresu
    */
    void setPlotColor();

private:
    //! Metoda klasy
    /*!
        generuje osie wykresu i ogreśla styl wyświetlania
    */
    void generatePlot();
    //! Metoda klasy
    /*!
        inicjalizuje sloty obsługujące przyciski w menu
    */
    void initActionsConnections();
    //! Metoda klasy
    /*!
        tworzy schemat rozmieszczenia elementów w oknie głównym
    */
    void createLayouts();
    //! Metoda klasy
    /*!
        ustawia akcje skrótów klawiaturowych
    */
    void connectActions();
    //! Metoda klasy
    /*!
        /parametr message - wyświetlana informacja
        wyświetla informacje na pasku stanu
    */
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    QLabel *status;
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;
    QPushButton *buttons[4];
    QGroupBox *buttonBox;
    QVector<QByteArray> *filedata;
    QCustomPlot *customPlot;
    QAction *ctrlplus;
    QAction *ctrlminus;
    QAction *ctrls;
    QAction *ctrlp;
    bool autoscale;

signals:
    void sendToPlot(int);
};

#endif // MAINWINDOW_H
