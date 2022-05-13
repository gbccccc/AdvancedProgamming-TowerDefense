#include "friendly.h"
#include "enemy.h"
#include "cell.h"

Cell::Cell() : routeState(NA_route), block(false), passable(true), loc(CellLoc(0, 0)) {}
Cell::Cell(RouteState routeState, CellLoc loc) : routeState(routeState), block(false), passable(true), loc(loc) {}

void Cell::update_state()
{
    passable = true;
    for (Friendly *frd : friendIn)
        if (!frd->is_passable())
        {
            passable = false;
            break;
        }
}

void Cell::add_friend(Friendly *frd)
{
    friendIn.push_front(frd);
    update_state();
}

void Cell::rm_friend(Friendly *frd)
{
    friendIn.remove(frd);
    update_state();
}

void Cell::add_enemy(Enemy *enm)
{
    enemyIn.push_back(enm);
}

void Cell::rm_enemy(Enemy *enm)
{
    enemyIn.remove(enm);
}

void Cell::paint(QPainter &painter)
{
    switch (routeState)
    {
    case Cell::common:
        painter.setBrush(QBrush(Qt::gray));
        break;
    case Cell::onRoute:
        painter.setBrush(QBrush(Qt::green));
        break;
    case Cell::home:
        painter.setBrush(QBrush(Qt::blue));
        break;
    case Cell::summon:
        painter.setBrush(QBrush(Qt::red));
        break;
    case Cell::NA_route:
        painter.setBrush(QBrush(Qt::transparent));
        break;
    }

    painter.drawRect(loc.first * cellSize, loc.second * cellSize, cellSize, cellSize);

    if (block)
    {
        painter.setBrush(QBrush(Qt::black));
        painter.drawLine(loc.first * cellSize, loc.second * cellSize, (loc.first + 1) * cellSize, (loc.second + 1) * cellSize);
        painter.drawLine(loc.first * cellSize + cellSize / 2, loc.second * cellSize, (loc.first + 1) * cellSize, loc.second * cellSize + cellSize / 2);
        painter.drawLine(loc.first * cellSize, loc.second * cellSize + cellSize / 2, loc.first * cellSize + cellSize / 2, (loc.second + 1) * cellSize);
    }
}
