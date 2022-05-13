#include "friendly_bomber.h"
#include "enemy.h"

FrdBomber::FrdBomber(CellLoc loc, Dir dir, GameMap &gmp):
    Friendly(800, 50, "Bomber", 4000, loc, dir, gmp)
{
    update_range();
}

void FrdBomber::update()
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

bool FrdBomber::attack(Enemy *enm)
{
    if (!enm->is_flying())
    {
        attackEffectCnt = attackEffectShowFrame * 2;
        enm->be_damaged(this->damage);
        attackTarget = enm->get_loc();

        CellLoc center = enm->get_cell_loc();
        vector<CellLoc> spreadRange;
        spreadRange.push_back(center);
        spreadRange.push_back(center + CellLoc(1, 0));
        spreadRange.push_back(center + CellLoc(0, 1));
        spreadRange.push_back(center + CellLoc(-1, 0));
        spreadRange.push_back(center + CellLoc(0, -1));

        for (CellLoc rangeLoc : spreadRange)
            for (Enemy *spreadEnm : gmp.get_cell(rangeLoc)->get_enemy())
                if (!spreadEnm->is_flying())
                    spreadEnm->be_damaged(damage / 5);

        return true;
    }
    return false;
}

void FrdBomber::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    painter.drawRect(loc.first * cellSize + 20, loc.second * cellSize + 20, 60, 60);
    painter.drawEllipse(QPointF(loc.first * cellSize + 50, loc.second * cellSize + 50), 30, 30);
    Friendly::paint_dir(painter);
    Friendly::paint(painter);
}

void FrdBomber::update_range()
{
    this->range.push_back(this->loc);
    this->range.push_back(this->loc + get_vertical_dir(dir));
    this->range.push_back(this->loc - get_vertical_dir(dir));
    this->range.push_back(this->loc + dir);
    this->range.push_back(this->loc + dir + get_vertical_dir(dir));
    this->range.push_back(this->loc + dir - get_vertical_dir(dir));
    this->range.push_back(this->loc + (CellLoc)(dir * 2));
    this->range.push_back(this->loc + (CellLoc)(dir * 2) + get_vertical_dir(dir));
    this->range.push_back(this->loc + (CellLoc)(dir * 2) - get_vertical_dir(dir));
}

void FrdBomber::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        if (attackEffectCnt > attackEffectShowFrame)
            draw_attack_effect_laser(painter);

        QColor color(Qt::white);
        color.setAlpha(100);
        painter.setPen(color);
        painter.setBrush(color);

        painter.drawEllipse(QPoint(attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2), 30, 30);
        painter.drawEllipse(QPoint(attackTarget.first * cellSize + cellSize / 2 + cellSize, attackTarget.second * cellSize + cellSize / 2), 30, 30);
        painter.drawEllipse(QPoint(attackTarget.first * cellSize  + cellSize / 2 - cellSize, attackTarget.second * cellSize + cellSize / 2), 30, 30);
        painter.drawEllipse(QPoint(attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2 + cellSize), 30, 30);
        painter.drawEllipse(QPoint(attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2 - cellSize), 30, 30);

        painter.setPen(Qt::black);
    }
}
