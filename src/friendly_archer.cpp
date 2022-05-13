#include "friendly_archer.h"
#include "enemy.h"

FrdArcher::FrdArcher(CellLoc loc, Dir dir, GameMap &gmp) :
    Friendly(100, 10, "Archer", 500, loc, dir, gmp)
{
    update_range();
}

void FrdArcher::update()
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

bool FrdArcher::attack(Enemy *enm)
{
    attackEffectCnt = attackEffectShowFrame;
    enm->be_damaged(this->damage);
    attackTarget = enm->get_loc();
    return true;
}

void FrdArcher::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    QPolygon p;
    p.setPoints(4, \
                loc.first * cellSize + 50, loc.second * cellSize + 20, \
                loc.first * cellSize + 90, loc.second * cellSize + 90, \
                loc.first * cellSize + 50, loc.second * cellSize + 70, \
                loc.first * cellSize + 10, loc.second * cellSize + 90);
    painter.drawPolygon(p);

    Friendly::paint(painter);
}

void FrdArcher::update_range()
{
    for (int i = -2; i <= 2; ++i)
        for (int j = -2; j <= 2; ++j)
            range.push_back(this->loc + CellLoc(i, j));
}

void FrdArcher::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        draw_attack_effect_laser(painter);
    }
}
