#ifndef ENMARCHER_H
#define ENMARCHER_H

#include "enemy.h"

class EnmArcher : public Enemy
{
private:
    bool attack(Friendly *frd);
public:
    EnmArcher(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMARCHER_H
