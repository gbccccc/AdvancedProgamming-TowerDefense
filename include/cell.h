#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <list>
#include <QPainter>
using namespace std;

#include "loc.h"

class Enemy;
class Friendly;

class Cell
{
public:
    enum RouteState { common, onRoute, summon, home, NA_route };
private:
    RouteState routeState;
    bool block;
    bool passable;

    CellLoc loc;
    list<Enemy *> enemyIn;
    list<Friendly *> friendIn;

public:
    Cell();
    Cell(RouteState routeState, CellLoc loc);

    void update_state();
    bool is_frd_empty() {return friendIn.empty();}
    bool is_block() {return block;}
    bool is_passable() {return passable;}
    RouteState get_route_state() {return this->routeState;}


    list<Enemy *> &get_enemy() {return this->enemyIn;}
    Friendly *get_friend() {return this->friendIn.front();}

    void add_friend(Friendly *frd);
    void rm_friend(Friendly *frd);
    void add_enemy(Enemy *enm);
    void rm_enemy(Enemy *enm);

    void paint(QPainter &painter);

    friend class GameMap;
};

#endif // CELL_H
