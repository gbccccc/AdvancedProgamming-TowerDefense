#include "enemy_dragon.h"

EnmDragon::EnmDragon(Route &route, GameMap &gmp, Player &player):
    Enemy(400, 40, "Dragon", 1000, 0.25, Fly::flying, 2, route, gmp, player)
{
}

void EnmDragon::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            rangeCells.push_back(gmp.get_cell(this->get_cell_loc() + Dir(i, j)));

    // check if there are friends in attack range
    bool frd_in_range = false;
    for (Cell *rangeCell : rangeCells)
        if (!rangeCell->is_passable())
        {
            frd_in_range = true;
            break;
        }

    // if no, move
    if (!frd_in_range)
        move();
    // if yes, and has experienced a whole attack gap time, attack
    else if (now - lastAtkTime >= atkGap)
        for (Cell *rangeCell : rangeCells)
            if (!rangeCell->is_passable())
                if (attack(rangeCell->get_friend()))
                {
                    lastAtkTime = now;
                    break;
                }

    this->Enemy::update();
}

bool EnmDragon::attack(Friendly *frd)
{
    attackEffectCnt = attackEffectShowFrame;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();
    return true;
}

void EnmDragon::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(6, \
                (int)(loc.first * cellSize + 30), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 40), (int)(loc.second * cellSize + 50), \
                (int)(loc.first * cellSize + 30), (int)(loc.second * cellSize + 70), \
                (int)(loc.first * cellSize + 70), (int)(loc.second * cellSize + 70), \
                (int)(loc.first * cellSize + 90), (int)(loc.second * cellSize + 10), \
                (int)(loc.first * cellSize + 70), (int)(loc.second * cellSize + 30));
    painter.drawPolygon(p);

    Enemy::paint(painter);
}

void EnmDragon::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_laser(painter);

        QColor color(Qt::red);
        color.setAlpha(100);
        painter.setPen(color);
        painter.setBrush(color);
        painter.drawEllipse(QPoint(attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2), 20, 20);
        painter.setPen(Qt::black);
    }
}
