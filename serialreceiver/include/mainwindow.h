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

//!  Klasa MainWindow
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

//! openSerialPort
/*!
    Otwiera potr szeregowy o parametrach z klasy serial
*/
    void openSerialPort();

//! closeSerialPort
/*!
    \param idx - identyfikator wykonania
*/
    void closeSerialPort();

//! openSettings
/*!
    otwiera okno klasy settings
*/
    void openSettings();

//! clearConsole
/*!
    czysci konsolę wyświetlania
*/
    void clearConsole();

//! about
/*!
    wyświetla informacje o programie
*/
    void about();

//! writeData
/*!
    wysyła dane określone jako parametr (opcjonalnie)
    \param data danew do wysłania
*/
    void writeData(const QByteArray &data);

//! readData
/*!
    czyta dane z portu szeregowego i wysyła do konsoli bądź wykresu
*/
    void readData();

//! handleError
/*!
    obsługa błędów komunikacji szeregowej
    \param error - typ błędu otwarcia portu
*/
    void handleError(QSerialPort::SerialPortError error);

//! saveFile
/*!
    zapisuje dane z konsoli wyświetlania do pliku
*/
    void saveFile();

//! realtimeDataSlot
/*!
    dodaje punkt do wykresu
    \param int - aktualna wartość do wykresu
*/
    void realtimeDataSlot(int);

//! changePlotCaption
/*! 
    \param idx - identyfikator wykonania
*/
    void changePlotCaption();

//! savePlot
/*!
    zmienia sposób skalowania wykresu
*/
    void savePlot();

//! Slot extendPlotScale
/*!
    zapisuje wykres jako plik graficzny
*/
    void extendPlotScale();

//! dropPlotScale
/*!
    zwiększa skalę wykresu
*/
    void dropPlotScale();

//! setPlotColor
/*!
    zmniejsza skalę wykresu
*/
    void setPlotColor();

private:

//! generatePlot
/*!
    generuje osie wykresu i ogreśla styl wyświetlania
*/
    void generatePlot();

//! initActionsConnections
/*!
    inicjalizuje sloty obsługujące przyciski w menu
*/
    void initActionsConnections();

//! createLayouts
/*!
    tworzy schemat rozmieszczenia elementów w oknie głównym
*/
    void createLayouts();

//! connectActions
/*!
    ustawia akcje skrótów klawiaturowych
*/
    void connectActions();

//! showStatusMessage
/*!
    /param message - wyświetlana informacja
    wyświetla informacje na pasku stanu
*/
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui; /*!< interfejs graficzny */ 
    QLabel *status; /*!< pasek statusu */ 
    Console *console; /*!< konsola do wyświetlania danych */ 
    SettingsDialog *settings; /*!< okno dialogowe ustawień */ 
    QSerialPort *serial; /*!< obiekt klasy QSerialPort */ 
    QPushButton *buttons[4]; /*!< tablica przycisków */ 
    QGroupBox *buttonBox; /*!< kontener na przyciski */ 
    QVector<QByteArray> *filedata; /*!< wektor dancych do zapisania w pliku */ 
    QCustomPlot *customPlot; /*!< wykres */ 
    QAction *ctrlplus; /*!< akcja skrótu klawiaturowego */ 
    QAction *ctrlminus; /*!< akcja skrótu klawiaturowego */ 
    QAction *ctrls; /*!< akcja skrótu klawiaturowego */ 
    QAction *ctrlp; /*!< akcja skrótu klawiaturowego */ 
    bool autoscale; /*!< zmienna aktywacji autoskalowania */ 
};

#endif // MAINWINDOW_H
