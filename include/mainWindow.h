#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Display; }
QT_END_NAMESPACE

class  MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void my_update();

private:
    Ui::Display *ui;
    QTimer *timer;
    Game game;
    Dir dir;

    const static int windowLength = 1600;
    const static int windowWidth = 1000;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
};
#endif // MAINWINDOW_H
