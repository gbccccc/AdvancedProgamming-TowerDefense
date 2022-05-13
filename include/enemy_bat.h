#ifndef ENMBAT_H
#define ENMBAT_H

#include "enemy.h"

class EnmBat : public Enemy
{
private:
    bool attack(Friendly *frd);

public:
    EnmBat(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMBAT_H
