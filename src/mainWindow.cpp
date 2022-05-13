#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "loc.h"
#include "gameoverdlg.h"

MainWindow:: MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Display)
    , timer(new QTimer)
    , game("C:/Users/gbc/Desktop/C/game/untitled/maps/map2.txt")
      //    , game("./maps/map2.txt")
    , dir(1, 0)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(my_update()));
    timer->start(20);
    resize(windowLength, windowWidth);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::my_update()
{
    bool endFlag = game.update();
    this->update();

    if (endFlag)
    {
        timer->stop();
        GameOverDlg ggDlg;
        ggDlg.exec();
        this->close();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    game.paint(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->x() >= startx && e->x() <= windowLength - startx && e->y() >= starty && e->y() <= windowWidth - starty)
    {
        // place friendly
        CellLoc loc((e->x() - startx) / cellSize, (e->y() - starty) / cellSize);
        if (e->button() == Qt::LeftButton)
            game.choose(loc);
        else if (e->button() == Qt::RightButton)
        {
            game.rm_friend(loc);
            game.unchoose();
        }
    }
    else
        game.unchoose();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    // WASD for changing friendly direction
    case Qt::Key_D:
        game.turn_chosen(Dir(1, 0));
        break;
    case Qt::Key_A:
        game.turn_chosen(Dir(-1, 0));
        break;
    case Qt::Key_W:
        game.turn_chosen(Dir(0, -1));
        break;
    case Qt::Key_S:
        game.turn_chosen(Dir(0, 1));
        break;

    // QE for changing friendly type
    case Qt::Key_Q:
        game.change_friend_index(-1);
        break;
    case Qt::Key_E:
        game.change_friend_index(1);
        break;

    // pause and resume
    case Qt::Key_P:
        if (timer->isActive())
            timer->stop();
        else
        {
            game.resume_time_set();
            timer->start();
        }
        break;

    // sudo generate enemies, only for performance
    case Qt::Key_0:
        game.sudo_generate_enemy(0);
        break;
    case Qt::Key_1:
        game.sudo_generate_enemy(1);
        break;
    case Qt::Key_2:
        game.sudo_generate_enemy(2);
        break;
    case Qt::Key_3:
        game.sudo_generate_enemy(3);
        break;
    case Qt::Key_4:
        game.sudo_generate_enemy(4);
        break;
    case Qt::Key_5:
        game.sudo_generate_enemy(5);
        break;
    }
}
