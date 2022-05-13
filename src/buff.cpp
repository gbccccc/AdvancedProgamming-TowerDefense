#include "buff.h"
#include <windows.h>

Buff::Buff(Enemy *enm, unsigned length):
    enm(enm),
    length(length),
    beginTime(GetTickCount()),
    lastUpdateTime(beginTime)
{
}

Buff::~Buff() {}

bool Buff::update()
{
    lastUpdateTime = GetTickCount();
    if (lastUpdateTime - beginTime > length)
    {
        rm_buff(enm);
        return false;
    }

    return true;
}

void Buff::resume_time_set()
{
    unsigned now = GetTickCount();
    beginTime += now - lastUpdateTime;
    lastUpdateTime = now;
}
