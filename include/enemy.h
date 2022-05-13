#ifndef ENEMY_H
#define ENEMY_H

#include<QPainter>
#include "gameobject.h"
#include "route.h"
#include "gamemap.h"
#include "player.h"

#include "friendly.h"

class Buff;

enum Fly {flying, ground};

class Enemy : public GameObject
{
protected:
    double atkGap;
    double speed;
    Fly fly;
    int damageToPlayer;
    ObjLoc loc;
    GameMap &gmp;
    unsigned lastUpdateTime;
    unsigned lastAtkTime;
    Route &route;
    CellLoc moveTarget;
    Dir dir;
    Player &player;
    list<Buff *> buffs;
    CellLoc attackTarget;

    void move();
    virtual bool attack(Friendly *frd) = 0;

    void draw_attack_effect_laser(QPainter &painter);
    void draw_attack_effect_fight(QPainter &painter);

public:
    Enemy(double hp, double damage, string name, double atkGap, double speed, Fly fly, int damageToPlayer, Route &route, GameMap &gmp, Player &player);
    ~Enemy();

    void add_buff(Buff *buff);

    bool is_friendly() {return false;}
    bool is_flying() {return fly == Fly::flying;}

    CellLoc get_cell_loc();
    ObjLoc get_loc();

    void resume_time_set();

    virtual void update();
    virtual void paint(QPainter &painter);
    virtual void draw_attack_effect(QPainter &painter) = 0;

    friend class Buff;
};

#endif // ENEMY_H
