#include "gameoverdlg.h"
#include "ui_gameoverdlg.h"

GameOverDlg::GameOverDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDlg)
{
    ui->setupUi(this);
}

GameOverDlg::~GameOverDlg()
{
    delete ui;
}
