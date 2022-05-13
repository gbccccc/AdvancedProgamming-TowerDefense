#ifndef FRIENDLY_H
#define FRIENDLY_H

#include<QPainter>
#include <vector>
#include <list>

#include "gameobject.h"
#include "loc.h"
#include "gamemap.h"

class Enemy;

class Friendly : public GameObject
{
protected:
    double atkGap;
    unsigned lastUpdateTime;
    unsigned lastAtkTime;
    CellLoc loc;
    vector<CellLoc> range;
    Dir dir;
    GameMap &gmp;
    ObjLoc attackTarget;
    bool passable;

    virtual bool attack(Enemy *enm) = 0;

    void paint_dir(QPainter &painter);
    void draw_attack_effect_laser(QPainter &painter);

    virtual void update_range() = 0;

public:
    ~Friendly();
    Friendly(double hp, double damage, string name, double atkGap, CellLoc loc, Dir dir, GameMap &gmp, bool passable = false);

    bool is_friendly() {return true;}
    bool is_passable() {return passable;}
    CellLoc get_loc();

    void resume_time_set();

    virtual void update();
    virtual void paint(QPainter &painter);
    virtual void draw_attack_effect(QPainter &painter) = 0;

    void draw_detail(QPainter &painter);

    void turn(Dir dir);
};

#endif // FRIENDLY_H
