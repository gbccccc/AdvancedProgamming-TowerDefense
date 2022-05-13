#include "friendly_sphere.h"
#include "gamemap.h"
#include "loc.h"

FrdSphere::FrdSphere(CellLoc loc, Dir dir, GameMap &gmp):
    Friendly(400, 10, "Sphere", 1000, loc, dir, gmp)
{
    update_range();
}

void FrdSphere::update()
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

bool FrdSphere::attack(Enemy *enm)
{
    if (!enm->is_flying())
    {
        attackEffectCnt = attackEffectShowFrame * 2;
        enm->be_damaged(this->damage);
        attackTarget = enm->get_loc();
        return true;
    }
    return false;
}

void FrdSphere::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(3, \
                loc.first * cellSize + 50, loc.second * cellSize + 20, \
                loc.first * cellSize + 20, loc.second * cellSize + 80, \
                loc.first * cellSize + 80, loc.second * cellSize + 80);
    painter.drawPolygon(p);

    Friendly::paint_dir(painter);
    Friendly::paint(painter);
}

void FrdSphere::update_range()
{
    this->range.push_back(this->loc);
    this->range.push_back(this->loc + dir);
    this->range.push_back(this->loc + (CellLoc)(dir * 2));
}

void FrdSphere::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        painter.setPen(Qt::white);

        ObjLoc tempLoc = loc + dir + dir;
        painter.drawLine((loc.first + ((ObjLoc)dir).second / 2) * cellSize + cellSize / 2, \
                         (loc.second + ((ObjLoc)dir).first / 2) * cellSize + cellSize / 2, \
                         tempLoc.first * cellSize + cellSize / 2, tempLoc.second * cellSize + cellSize / 2);
        painter.drawLine((loc.first - ((ObjLoc)dir).second / 2) * cellSize + cellSize / 2, \
                         (loc.second - ((ObjLoc)dir).first / 2) * cellSize + cellSize / 2, \
                         tempLoc.first * cellSize + cellSize / 2, tempLoc.second * cellSize + cellSize / 2);

        painter.setPen(Qt::black);
    }
}
