#ifndef ENMCIRCLE_H
#define ENMCIRCLE_H

#include<QPainter>
#include "enemy.h"

class EnmThief : public Enemy
{
private:
    bool attack(Friendly *frd);

public:
    EnmThief(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMCIRCLE_H
