#include "friendly_guardmother.h"
#include "game.h"

FrdGuardMother::FrdGuardMother(CellLoc loc, Dir dir, GameMap &gmp, Game *game) :
    Friendly(50, 0, "Guard Mother", 10000, loc, dir, gmp),
    game(game)
{
    update_range();
}

void FrdGuardMother::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();
    if (now - this->lastAtkTime >= this->atkGap)
        for (CellLoc rangeLoc : this->range)
            if (attack(rangeLoc))
                this->lastAtkTime = now;

    this->Friendly::update();
}

bool FrdGuardMother::attack(Enemy *enm)
{
    enm = NULL;
    return false;
}

bool FrdGuardMother::attack(CellLoc loc)
{
    return game->generate_friend(loc, dir, -1);
}

void FrdGuardMother::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::white;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    painter.drawEllipse(QPointF(loc.first * cellSize + cellSize / 2, loc.second * cellSize + cellSize / 2), 30, 30);
    QPolygon p;
    p.setPoints(5, \
                loc.first * cellSize + 30, loc.second * cellSize + 30, \
                loc.first * cellSize + 30, loc.second * cellSize + 50, \
                loc.first * cellSize + 50, loc.second * cellSize + 70, \
                loc.first * cellSize + 70, loc.second * cellSize + 50, \
                loc.first * cellSize + 70, loc.second * cellSize + 30);
    painter.drawPolygon(p);
    Friendly::paint_dir(painter);
    Friendly::paint(painter);
}

void FrdGuardMother::update_range()
{
    this->range.push_back(this->loc + dir);
    this->range.push_back(this->loc + dir + get_vertical_dir(dir));
    this->range.push_back(this->loc + dir - get_vertical_dir(dir));
}

void FrdGuardMother::draw_attack_effect(QPainter &painter)
{
    return;
}
