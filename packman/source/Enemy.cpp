#include "../header/Enemy.h"

Enemy::Enemy()
    : MovingObject(GHOST_START_X, GHOST_START_Y, QImage("./image/red.jpeg"), QImage("./image/blue.jpg")), m_status(Normal), m_lastDir(Left), m_panicTime(0)
{}

void Enemy::reverseDirection(){
    switch(m_lastDir){
        case Left:
            moveRight();
            m_lastDir = Right;
            break;
        case Right:
            moveLeft();
            m_lastDir = Left;
            break;
        case Up:
            moveDown();
            m_lastDir = Down;
            break;
        case Down:
            moveUp();
            m_lastDir = Right;
            break;
    }
}
