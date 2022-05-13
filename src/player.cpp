#include "player.h"

Player::Player(int hp) : hp(hp) {}

void Player::paint(QPainter &painter)
{
    QRectF rect(10, 0, 100, 40);
    painter.drawText(rect, (QString)"HP:" + QString::number(hp));
}
