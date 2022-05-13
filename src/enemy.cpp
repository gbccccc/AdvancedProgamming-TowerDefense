#include <windows.h>
#include <cmath>
#include "enemy.h"
#include "buff_types.h"

Enemy::Enemy(double hp, double damage, string name, double atkGap, double speed, Fly fly, int damageToPlayer, Route &route, GameMap &gmp, Player &player):
    GameObject(hp, damage, name),
    atkGap(atkGap),
    speed(speed),
    fly(fly),
    damageToPlayer(damageToPlayer),
    loc(route.get_summon()),
    gmp(gmp),
    lastUpdateTime(GetTickCount()),
    lastAtkTime(0),
    route(route),
    moveTarget(route.get_next_turn_loc(route.get_summon())),
    dir(get_dir(loc, moveTarget)),
    player(player),
    attackTarget(CellLoc(0, 0))
{
    gmp.get_cell(this->get_cell_loc())->add_enemy(this);
}

Enemy::~Enemy()
{
    gmp.get_cell(get_cell_loc())->rm_enemy(this);
}

void Enemy::paint(QPainter &painter)
{
    QRectF rect(loc.first * cellSize + 35, loc.second * cellSize + 40, 30, 20);
    painter.drawText(rect, Qt::AlignHCenter, QString::number((int)hp));
}

CellLoc Enemy::get_cell_loc()
{
    return CellLoc(round(loc.first), round(loc.second));
}

void Enemy::update()
{
    // update buffs
    for (list<Buff *>::iterator itr = buffs.begin(); itr != buffs.end(); itr++)
        if (!(*itr)->update())
        {
            delete *itr;
            itr = buffs.erase(itr);
        }

    lastUpdateTime = GetTickCount();
}

void Enemy::add_buff(Buff *buff)
{
    buffs.push_back(buff);
}

void Enemy::move()
{
    CellLoc tempLoc = this->get_cell_loc();
    unsigned timeGap = GetTickCount() - lastUpdateTime;

    // common move
    if (get_distance((pair<double, double>)moveTarget - loc) > get_distance(dir * (speed * timeGap / 1000)))
        loc += dir * (speed * timeGap / 1000);
    // reach turning location
    else if (!route.is_home(moveTarget))
    {
        loc = moveTarget;
        moveTarget = route.get_next_turn_loc(moveTarget);
        dir = get_dir(loc, moveTarget);
    }
    // reach home
    else
    {
        hp = 0;
        player.be_damage(damageToPlayer);
    }

    // move to a new cell
    if (tempLoc != this->get_cell_loc())
    {
        gmp.get_cell(this->get_cell_loc())->add_enemy(this);
        gmp.get_cell(tempLoc)->rm_enemy(this);
    }
}

void Enemy::resume_time_set()
{
    unsigned now = GetTickCount();
    lastAtkTime += now - lastUpdateTime;
    lastUpdateTime = now;
}

void Enemy::draw_attack_effect_laser(QPainter &painter)
{
    painter.setPen(Qt::red);
    painter.drawLine(loc.first * cellSize + cellSize / 2, loc.second * cellSize + cellSize / 2, \
                     attackTarget.first * cellSize + cellSize / 2, attackTarget.second * cellSize + cellSize / 2);
    painter.setPen(Qt::black);
}

void Enemy::draw_attack_effect_fight(QPainter &painter)
{
    painter.setPen(Qt::red);
    painter.drawLine(attackTarget.first * cellSize, attackTarget.second * cellSize, \
                     attackTarget.first * cellSize + cellSize, attackTarget.second * cellSize + cellSize);
    painter.setPen(Qt::black);
}

ObjLoc Enemy::get_loc()
{
    return loc;
}
