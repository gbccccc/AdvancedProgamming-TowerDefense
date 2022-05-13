#ifndef PLAYER_H
#define PLAYER_H

#include <QPainter>

class Player
{
private:
    int hp;
public:
    Player(int hp);

    void be_damage(int damage) {this->hp -= damage;}
    bool is_alive() {return hp > 0;}
    void paint(QPainter &painter);
};

#endif // PLAYER_H
