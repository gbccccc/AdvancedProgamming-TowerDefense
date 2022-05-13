#include "friendly.h"
#include <QPainter>
#include <QString>

Friendly::Friendly(double hp, double damage, string name, double atkGap, CellLoc loc, Dir dir, GameMap &gmp, bool passable) :
    GameObject(hp, damage, name),
    atkGap(atkGap),
    lastAtkTime(0),
    loc(loc),
    dir(dir),
    gmp(gmp),
    attackTarget(ObjLoc(0, 0)),
    passable(passable)
{
    gmp.get_cell(loc)->add_friend(this);
}

Friendly::~Friendly()
{
    gmp.get_cell(loc)->rm_friend(this);
}

void Friendly::update()
{
    lastUpdateTime = GetTickCount();
}

void Friendly::paint(QPainter &painter)
{
    QRectF rect(loc.first * cellSize + 35, loc.second * cellSize + 40, 30, 20);
    painter.drawText(rect, Qt::AlignHCenter, QString::number((int)hp));
}

void Friendly::paint_dir(QPainter &painter)
{
    painter.setPen(Qt::DashLine);
    painter.drawLine(loc.first * cellSize + 50 + dir.first * 50, loc.second * cellSize + 50 + dir.second * 50, \
                     loc.first * cellSize + 50 - dir.first * 50 + (!dir.first) * 50, loc.second * cellSize + 50 - dir.second * 50 + (!dir.second) * 50);
    painter.drawLine(loc.first * cellSize + 50 + dir.first * 50, loc.second * cellSize + 50 + dir.second * 50, \
                     loc.first * cellSize + 50 - dir.first * 50 - (!dir.first) * 50, loc.second * cellSize + 50 - dir.second * 50 - (!dir.second) * 50);
}

void Friendly::draw_detail(QPainter &painter)
{
    painter.setPen(QPen(Qt::darkMagenta, 4));
    for (CellLoc loc : range)
    {
        painter.drawLine(loc.first * cellSize, loc.second * cellSize, \
                         loc.first * cellSize + cellSize / 3, loc.second * cellSize);

        painter.drawLine(loc.first * cellSize, loc.second * cellSize, \
                         loc.first * cellSize, loc.second * cellSize + cellSize / 3);

        painter.drawLine(loc.first * cellSize + cellSize, loc.second * cellSize, \
                         loc.first * cellSize + cellSize - cellSize / 3, loc.second * cellSize);

        painter.drawLine(loc.first * cellSize + cellSize, loc.second * cellSize, \
                         loc.first * cellSize + cellSize, loc.second * cellSize + cellSize / 3);

        painter.drawLine(loc.first * cellSize, loc.second * cellSize + cellSize, \
                         loc.first * cellSize + cellSize / 3, loc.second * cellSize + cellSize);

        painter.drawLine(loc.first * cellSize, loc.second * cellSize + cellSize, \
                         loc.first * cellSize, loc.second * cellSize + cellSize - cellSize / 3);

        painter.drawLine(loc.first * cellSize + cellSize, loc.second * cellSize + cellSize, \
                         loc.first * cellSize + cellSize - cellSize / 3, loc.second * cellSize + cellSize);

        painter.drawLine(loc.first * cellSize + cellSize, loc.second * cellSize + cellSize, \
                         loc.first * cellSize + cellSize, loc.second * cellSize + cellSize - cellSize / 3);
    }
    painter.setPen(QPen(Qt::black, 0));

    QRectF rect(loc.first * cellSize, loc.second * cellSize, 100, 20);
    painter.drawText(rect, Qt::AlignCenter, QString::fromStdString(name));
}

void Friendly::resume_time_set()
{
    unsigned now = GetTickCount();
    lastAtkTime += now - lastUpdateTime;
    lastUpdateTime = now;
}

void Friendly::turn(Dir dir)
{
    this->dir = dir;
    range.clear();
    update_range();
}

void Friendly::draw_attack_effect_laser(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.drawLine(loc.first * cellSize + cellSize / 2, loc.second * cellSize + cellSize / 2, \
                     attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2);
    painter.setPen(Qt::black);
}

CellLoc Friendly::get_loc()
{
    return loc;
}
