#include "enemy_bat.h"

EnmBat::EnmBat(Route &route, GameMap &gmp, Player &player):
    Enemy(50, 2, "Bat", 100, 1.2, Fly::flying, 1, route, gmp, player)
{
}

void EnmBat::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    rangeCells.push_back(gmp.get_cell(this->get_cell_loc()));

    // always move
    move();
    // if has experienced a whole attack gap time, attack
    if (now - lastAtkTime >= atkGap)
        for (Cell *rangeCell : rangeCells)
            if (!rangeCell->is_passable())
                if (attack(rangeCell->get_friend()))
                {
                    lastAtkTime = now;
                    break;
                }

    this->Enemy::update();
}

bool EnmBat::attack(Friendly *frd)
{
    attackEffectCnt = attackEffectShowFrame;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();
    return true;
}

void EnmBat::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(5, \
                (int)(loc.first * cellSize + 20), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 50), (int)(loc.second * cellSize + 40), \
                (int)(loc.first * cellSize + 80), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 60), (int)(loc.second * cellSize + 70), \
                (int)(loc.first * cellSize + 40), (int)(loc.second * cellSize + 70));
    painter.drawPolygon(p);

    Enemy::paint(painter);
}

void EnmBat::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_fight(painter);
    }
}
