#ifndef ENMSPHERE_H
#define ENMSPHERE_H

#include "enemy.h"

class EnmSphere : public Enemy
{
private:
    bool attack(Friendly *frd);
public:
    EnmSphere(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMSPHERE_H
