#ifndef ENMDAMAGEUPPER_H
#define ENMDAMAGEUPPER_H

#include "enemy.h"

class EnmDamageUpper : public Enemy
{
private:
    bool attack(Friendly *frd);
    bool attack(Friendly *frd, vector<Cell *> buffCells);

public:
    EnmDamageUpper(Route &route, GameMap &gmp, Player &player);

    void update();

    void paint(QPainter &painter);
    void draw_attack_effect(QPainter &painter);
};

#endif // ENMDAMAGEUPPER_H
