#include "friendly_thorn.h"
#include "enemy.h"

FrdThorn::FrdThorn(CellLoc loc, Dir dir, GameMap &gmp):
    Friendly(100, 4, "Thorn", 250, loc, dir, gmp, true)
{
    update_range();
}

void FrdThorn::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();
    if (now - this->lastAtkTime >= this->atkGap)
        for (CellLoc rangeLoc : this->range)
            for (Enemy *enm : gmp.get_cell(rangeLoc)->get_enemy())
                if (attack(enm))
                    this->lastAtkTime = now;

    this->Friendly::update();
}

bool FrdThorn::attack(Enemy *enm)
{
    if (!enm->is_flying())
    {
        enm->be_damaged(this->damage);
        return true;
    }
    return false;
}

void FrdThorn::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(7, \
                loc.first * cellSize + 0, loc.second * cellSize + 100, \
                loc.first * cellSize + 10, loc.second * cellSize + 80, \
                loc.first * cellSize + 20, loc.second * cellSize + 100, \
                loc.first * cellSize + 50, loc.second * cellSize + 20, \
                loc.first * cellSize + 80, loc.second * cellSize + 100, \
                loc.first * cellSize + 90, loc.second * cellSize + 80, \
                loc.first * cellSize + 100, loc.second * cellSize + 100);
    painter.drawPolygon(p);

    Friendly::paint(painter);
}

void FrdThorn::update_range()
{
    range.push_back(loc);
}

void FrdThorn::draw_attack_effect(QPainter &painter)
{
    return;
}
