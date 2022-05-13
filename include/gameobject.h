#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <windows.h>
#include <string>
#include <QPainter>
using namespace std;

class GameObject
{
protected:
    double hp;
    const double fullhp;
    double damage;
    const string name;
    int attackEffectCnt;
    bool twinkle;
    int twinkleLastCnt;
    int twinkleChangeCnt;

    static int attackEffectShowFrame;
    static int twinkleLastFrame;
    static int twinkleChangeFrame;

public:
    GameObject(double hp, double damage, string name);
    virtual ~GameObject() = 0;

    void be_damaged(double damage);
    bool check_twinkle();
    bool is_alive() {return this->hp > 0;}

    virtual void update() = 0;
    virtual bool is_friendly() = 0;
    virtual void paint(QPainter &painter) = 0;
    virtual void draw_attack_effect(QPainter &painter) = 0;


    virtual void resume_time_set() = 0;
};

#endif // GAMEOBJECT_H
