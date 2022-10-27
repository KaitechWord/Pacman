#pragma once
#include <QObject>
#include <QBasicTimer>
#include "MovingObject.h"
#include "Score.h"

#define PLAYER_START_X 13
#define PLAYER_START_Y 23

class Player: public MovingObject{
    private:
        int m_direction;
        void keyPressEvent(QKeyEvent *event);
    public:
        Player();
        int getDirection() const;
        void setDirection(int direction);
};