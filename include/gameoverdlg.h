#ifndef GAMEOVERDLG_H
#define GAMEOVERDLG_H

#include <QDialog>

namespace Ui {
class GameOverDlg;
}

class GameOverDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDlg(QWidget *parent = nullptr);
    ~GameOverDlg();

private:
    Ui::GameOverDlg *ui;
};

#endif // GAMEOVERDLG_H
