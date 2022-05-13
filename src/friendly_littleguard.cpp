#include "gamemap.h"
#include "loc.h"
#include "friendly_littleguard.h"

FrdLittleGuard::FrdLittleGuard(CellLoc loc, Dir dir, GameMap &gmp) :
    Friendly(100, 0, "Little Guard", -1, loc, dir, gmp)
{
    update_range();
}

void FrdLittleGuard::update()
{
    this->Friendly::update();
    return;
}


bool FrdLittleGuard::attack(Enemy *enm)
{
    enm = NULL;
    return false;
}

void FrdLittleGuard::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    QPolygon p;
    p.setPoints(5, \
                loc.first * cellSize + 30, loc.second * cellSize + 30, \
                loc.first * cellSize + 30, loc.second * cellSize + 50, \
                loc.first * cellSize + 50, loc.second * cellSize + 70, \
                loc.first * cellSize + 70, loc.second * cellSize + 50, \
                loc.first * cellSize + 70, loc.second * cellSize + 30);
    painter.drawPolygon(p);
    Friendly::paint(painter);
}

void FrdLittleGuard::update_range()
{
    return;
}

void FrdLittleGuard::draw_attack_effect(QPainter &painter)
{
    return;
}
