#include "friendly_guard.h"
#include "gamemap.h"
#include "loc.h"

FrdGuard::FrdGuard(CellLoc loc, Dir dir, GameMap &gmp) :
    Friendly(3000, 0, "Guard", -1, loc, dir, gmp)
{
    update_range();
}

void FrdGuard::update()
{
    this->Friendly::update();
    return;
}


bool FrdGuard::attack(Enemy *enm)
{
    enm = NULL;
    return false;
}

void FrdGuard::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    QPolygon p;
    p.setPoints(5, \
                loc.first * cellSize + 20, loc.second * cellSize + 20, \
                loc.first * cellSize + 20, loc.second * cellSize + 50, \
                loc.first * cellSize + 50, loc.second * cellSize + 80, \
                loc.first * cellSize + 80, loc.second * cellSize + 50, \
                loc.first * cellSize + 80, loc.second * cellSize + 20);
    painter.drawPolygon(p);
    Friendly::paint(painter);
}

void FrdGuard::update_range()
{
    return;
}

void FrdGuard::draw_attack_effect(QPainter &painter)
{
    return;
}
