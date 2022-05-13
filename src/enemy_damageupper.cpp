#include "enemy_damageupper.h"
#include "buff_damageup.h"

EnmDamageUpper::EnmDamageUpper(Route &route, GameMap &gmp, Player &player):
    Enemy(400, 20, "Damage Upper", 3000, 0.5, Fly::ground, 1, route, gmp, player)
{
}

void EnmDamageUpper::update()
{
    if (!is_alive())
        return;

    unsigned now = GetTickCount();

    // set attack range
    vector<Cell *> rangeCells;
    rangeCells.push_back(gmp.get_cell(this->get_cell_loc()));
    // set buff range
    vector<Cell *> buffCells;
    buffCells.push_back(gmp.get_cell(this->get_cell_loc()));
    buffCells.push_back(gmp.get_cell(this->get_cell_loc() + Dir(1, 0)));
    buffCells.push_back(gmp.get_cell(this->get_cell_loc() + Dir(0, 1)));
    buffCells.push_back(gmp.get_cell(this->get_cell_loc() + Dir(-1, 0)));
    buffCells.push_back(gmp.get_cell(this->get_cell_loc() + Dir(0, -1)));

    // check if there are friends in attack range
    bool frd_in_range = false;
    for (Cell *rangeCell : rangeCells)
        if (!rangeCell->is_passable())
        {
            frd_in_range = true;
            break;
        }

    // if no, move
    if (!frd_in_range)
        move();
    // if yes, and has experienced a whole attack gap time, attack
    else if (now - lastAtkTime >= atkGap)
        for (Cell *rangeCell : rangeCells)
            if (!rangeCell->is_passable())
                if (attack(rangeCell->get_friend(), buffCells))
                {
                    lastAtkTime = now;
                    break;
                }

    this->Enemy::update();
}

bool EnmDamageUpper::attack(Friendly *frd)
{
    return false;
}

bool EnmDamageUpper::attack(Friendly *frd, vector<Cell *> buffCells)
{
    attackEffectCnt = attackEffectShowFrame * 5;
    frd->be_damaged(damage);
    attackTarget = frd->get_loc();

    for (Cell *cell : buffCells)
        for (Enemy *enm : cell->get_enemy())
            enm->add_buff(new buffDamageUp(enm, 3000));

    return true;
}

void EnmDamageUpper::paint(QPainter &painter)
{
    if (check_twinkle())
        return;

    QColor color = Qt::red;
    color.setAlpha(hp * 255 / fullhp);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);

    QPolygon p;
    p.setPoints(7, \
                (int)(loc.first * cellSize + 30), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 40), (int)(loc.second * cellSize + 50), \
                (int)(loc.first * cellSize + 50), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 60), (int)(loc.second * cellSize + 50), \
                (int)(loc.first * cellSize + 70), (int)(loc.second * cellSize + 30), \
                (int)(loc.first * cellSize + 70), (int)(loc.second * cellSize + 70), \
                (int)(loc.first * cellSize + 30), (int)(loc.second * cellSize + 70));
    painter.drawPolygon(p);

    Enemy::paint(painter);
}

void EnmDamageUpper::draw_attack_effect(QPainter &painter)
{
    if (attackEffectCnt > 0)
    {
        --attackEffectCnt;
        if (attackEffectCnt > attackEffectShowFrame * 4)
            draw_attack_effect_fight(painter);

        painter.setPen(Qt::red);
        painter.setBrush(Qt::transparent);

        painter.drawEllipse(QPoint(loc.first * cellSize + cellSize / 2, loc.second * cellSize + cellSize / 2), 100, 100);

        painter.setPen(Qt::black);
    }
}
