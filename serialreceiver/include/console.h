#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit> //add thread to make it faster https://www.youtube.com/watch?v=yazMHbIew0Q


//! Klasa Console
/*!
	Klasa odpowiada za wyświetlanie przychodzących danych w oknie
*/
class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:

//! Sygnał getData
/*!
  \param data to dane wpisane z klawiatury
*/
    void getData(const QByteArray &data);
    void dataReady(bool); //flaga gotowosci

//! Konstruktor 
/*!
	W konstruktorze ustawiane są parametry początkowe klasy
	\param parent okresla klasę nadrzędną
*/
public:
    explicit Console(QWidget *parent = 0);

//! putData
/*!
	Umożliwia wypisanie danych w oknie
  	\param data to dane do wypisania
*/
    void putData(const QByteArray &data);

protected:
//! Wirtualne funkcje obecnie nieużywane
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);

};

#endif // CONSOLE_H
