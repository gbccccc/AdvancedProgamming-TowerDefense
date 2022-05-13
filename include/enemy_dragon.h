#ifndef ENMDRAGON_H
#define ENMDRAGON_H

#include "enemy.h"

class EnmDragon : public Enemy
{
private:
    bool attack(Friendly *frd);
public:
    EnmDragon(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMDRAGON_H
