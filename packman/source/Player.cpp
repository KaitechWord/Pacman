#include "../header/Player.h"
#include "../header/Map.h"
#include <QKeyEvent>

Player::Player()
    : MovingObject(PLAYER_START_X, PLAYER_START_Y, QImage("./image/yellow.JPG"), QImage("./image/yellow.JPG")), m_direction(Up)
{}

void Player::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Left:
            m_direction = Left;
            break;
        case Qt::Key_Right:
            m_direction = Right;
            break;
        case Qt::Key_Down:
            m_direction = Down;
            break;
        case Qt::Key_Up:
            m_direction = Up;
            break;
        default:
            break;
    }
}

int Player::getDirection() const{
    return m_direction;
}

void Player::setDirection(int direction){
    m_direction = direction;
}