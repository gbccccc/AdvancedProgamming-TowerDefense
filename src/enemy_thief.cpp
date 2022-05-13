#include "enemy_thief.h"

EnmThief::EnmThief(Route &route, GameMap &gmp, Player &player):
    Enemy(100, 5, "Sphere", 200, 1, Fly::ground, 1, route, gmp, player)
{}

void EnmThief::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    rangeCells.push_back(gmp.get_cell(this->get_cell_loc()));

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

bool EnmThief::attack(Friendly *frd)
{
    attackEffectCnt = attackEffectShowFrame;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();
    return true;
}

void EnmThief::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    painter.drawEllipse(QPointF(loc.first * cellSize + cellSize / 2, loc.second * cellSize + cellSize / 2), 30, 30);
    Enemy::paint(painter);
}

void EnmThief::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_fight(painter);
    }
}
