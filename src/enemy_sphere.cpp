#include "enemy_sphere.h"

EnmSphere::EnmSphere(Route &route, GameMap &gmp, Player &player):
    Enemy(50, 20, "Sphere", 1000, 1, Fly::ground, 1, route, gmp, player)
{}

void EnmSphere::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    rangeCells.push_back(gmp.get_cell(this->get_cell_loc()));
    rangeCells.push_back(gmp.get_cell(this->get_cell_loc() + dir));

    // check if there are friends in attack range
    bool frd_in_range = false;
    if (!rangeCells[0]->is_passable())
        frd_in_range = true;

    // if no, move
    if (!frd_in_range)
        move();
    // if yes, and has experienced a whole attack gap time, attack
    else if (now - lastAtkTime >= atkGap)
        for (Cell *rangeCell : rangeCells)
            if (rangeCell->get_route_state() == Cell::onRoute && !rangeCell->is_passable())
                if (attack(rangeCell->get_friend()))
                    lastAtkTime = now;

    this->Enemy::update();
}

bool EnmSphere::attack(Friendly *frd)
{
    attackEffectCnt = attackEffectShowFrame * 2;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();
    return true;
}

void EnmSphere::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(3, \
                (int)(loc.first * cellSize + 50), (int)(loc.second * cellSize + 20), \
                (int)(loc.first * cellSize + 20), (int)(loc.second * cellSize + 80), \
                (int)(loc.first * cellSize + 80), (int)(loc.second * cellSize + 80));
    painter.drawPolygon(p);

    Enemy::paint(painter);
}

void EnmSphere::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        painter.setPen(Qt::red);

        ObjLoc tempLoc = loc + (ObjLoc)(dir * 2);
        painter.drawLine((loc.first + ((ObjLoc)dir).second / 2) * cellSize + cellSize / 2, \
                         (loc.second + ((ObjLoc)dir).first / 2) * cellSize + cellSize / 2, \
                         tempLoc.first * cellSize + cellSize / 2, tempLoc.second * cellSize + cellSize / 2);
        painter.drawLine((loc.first - ((ObjLoc)dir).second / 2) * cellSize + cellSize / 2, \
                         (loc.second - ((ObjLoc)dir).first / 2) * cellSize + cellSize / 2, \
                         tempLoc.first * cellSize + cellSize / 2, tempLoc.second * cellSize + cellSize / 2);

        painter.setPen(Qt::black);
    }
}
