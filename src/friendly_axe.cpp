#include "friendly_axe.h"
#include "enemy.h"

FrdAxe::FrdAxe(CellLoc loc, Dir dir, GameMap &gmp) :
    Friendly(400, 6, "Axe", 250, loc, dir, gmp)
{
    update_range();
}

void FrdAxe::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();
    bool attackSuccess = false;
    if (now - this->lastAtkTime >= this->atkGap)
        for (CellLoc rangeLoc : this->range)
        {
            for (Enemy *enm : gmp.get_cell(rangeLoc)->get_enemy())
                if (attack(enm))
                {
                    this->lastAtkTime = now;
                    attackSuccess = true;
                    break;
                }

            if (attackSuccess)
                break;
        }

    this->Friendly::update();
}

bool FrdAxe::attack(Enemy *enm)
{
    attackEffectCnt = attackEffectShowFrame;
    if (!enm->is_flying())
        enm->be_damaged(this->damage);
    else
        enm->be_damaged(this->damage / 2);
    attackTarget = enm->get_loc();
    return true;
}

void FrdAxe::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(6, \
                loc.first * cellSize + 30, loc.second * cellSize + 30, \
                loc.first * cellSize + 70, loc.second * cellSize + 30, \
                loc.first * cellSize + 80, loc.second * cellSize + 50, \
                loc.first * cellSize + 70, loc.second * cellSize + 70, \
                loc.first * cellSize + 30, loc.second * cellSize + 70, \
                loc.first * cellSize + 20, loc.second * cellSize + 50);
    painter.drawPolygon(p);

    Friendly::paint_dir(painter);
    Friendly::paint(painter);
}

void FrdAxe::update_range()
{
    this->range.push_back(this->loc);
    this->range.push_back(this->loc + dir);
    this->range.push_back(this->loc - dir);
}

void FrdAxe::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_laser(painter);
    }
}
