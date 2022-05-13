#include "enemy_archer.h"

EnmArcher::EnmArcher(Route &route, GameMap &gmp, Player &player):
    Enemy(100, 10, "Archer", 1000, 0.5, Fly::ground, 1, route, gmp, player)
{
}

void EnmArcher::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    for (int i = -2; i <= 2; ++i)
        for (int j = -2; j <= 2; ++j)
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

bool EnmArcher::attack(Friendly *frd)
{
    attackEffectCnt = attackEffectShowFrame;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();
    return true;
}

void EnmArcher::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(4, \
                (int)(loc.first * cellSize + 50), (int)(loc.second * cellSize + 20), \
                (int)(loc.first * cellSize + 90), (int)(loc.second * cellSize + 90), \
                (int)(loc.first * cellSize + 50), (int)(loc.second * cellSize + 70), \
                (int)(loc.first * cellSize + 10), (int)(loc.second * cellSize + 90));
    painter.drawPolygon(p);

    Enemy::paint(painter);
}

void EnmArcher::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_laser(painter);
    }
}
