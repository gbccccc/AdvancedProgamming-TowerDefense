#include "gameobject.h"
#include "loc.h"

GameObject::GameObject(double hp, double damage, string name):
    hp(hp),
    fullhp(hp),
    damage(damage),
    name(name),
    attackEffectCnt(0),
    twinkle(false),
    twinkleLastCnt(0),
    twinkleChangeCnt(0)
{}

GameObject::~GameObject() {}

int GameObject::attackEffectShowFrame = 4;
int GameObject::twinkleChangeFrame = 5;
int GameObject::twinkleLastFrame = 15;

void GameObject::be_damaged(double damage)
{
    this->hp -= damage;
    twinkleLastCnt = twinkleLastFrame;
}

bool GameObject::check_twinkle()
{
    if (twinkle || twinkleLastCnt > 0)
    {
        if (twinkleChangeCnt == 0)
            twinkle = !twinkle;
        twinkleChangeCnt = (twinkleChangeCnt + 1) % twinkleChangeFrame;
        --twinkleLastCnt;
    }

    return twinkle;
}
