#ifndef GAME_H
#define GAME_H

#include <QPainter>
#include <iostream>
#include <list>
using namespace std;

#include "gamemap.h"
#include <fstream>
using namespace std;

#include "route.h"
#include "gameobject.h"
#include "player.h"

class Game
{
private:
    static const int refreshGap = 20;
    static int frdTypeNum;

    ifstream initer;
    list<Route *> routes;
    GameMap *gmp;
    unsigned summonGap;
    unsigned lastSummonTime;
    int frdIndex;
    list<GameObject *> objects;
    CellLoc chosen;
    Player &player;
    QPixmap pix;

    void generate_enemy(Route &route, int index);
    bool generate_friend(CellLoc loc, Dir dir);
    bool add_friend_2_list(Friendly *frd);

    void draw_chosen(QPainter &painter);
    void draw_cur_friend_name(QPainter &painter);

public:
    Game(string fileName);
    ~Game();
    void start();
    bool update();
    void resume_time_set();

    void paint(QPainter &painter);

    void unchoose();
    void choose(CellLoc loc);
    void turn_chosen(Dir dir);
    void change_friend_index(int offset);

    bool generate_friend(CellLoc loc, Dir dir, int index);
    bool rm_friend(CellLoc loc);

    void sudo_generate_enemy(int index);
};

#endif // GAME_H
