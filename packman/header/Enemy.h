#pragma once
#include "MovingObject.h"

#define GHOST_START_X 13
#define GHOST_START_Y 10

enum Status {
    Normal,
    Panic,
    Running
};

class Enemy: public MovingObject{
    protected:
        Status m_status;
        Direction m_lastDir;
        int m_panicTime;
    public:
		Enemy();
        Status getStatus(){ return m_status;};
        void setStatus(Status status){m_status = status;}
        Direction getDirection(){ return m_lastDir;}
        void setDirection(Direction dir){ m_lastDir = dir;}
        void reverseDirection();
        int getPanicTime() const { return m_panicTime;};
        void setPanicTime(int time){ m_panicTime = time;};
        void decreasePanicTime(){ m_panicTime--; };
        //virtual Coordinates& chasingStrategy(Coordinates& nowPac, Coordinates& oldPac, Coordinates& nowBlinky) const = 0;
};
/*
class Red: public Enemy{
    public:
        Red();
        Coordinates& chasingStrategy(Coordinates& nowPac, Coordinates& oldPac) const override;
}

class Pink: public Enemy{
    public:
        Pink();
        Coordinates& chasingStrategy(Coordinates& nowPac, Coordinates& oldPac) const override;
}

class Blue: public Enemy{
    public:
        Blue();
        Coordinates& chasingStrategy(Coordinates& nowPac, Coordinates& oldPac) const override;
}

class Orange: public Enemy{
    public:
        Orange();
        Coordinates& chasingStrategy(Coordinates& nowPac, Coordinates& oldPac) const override;
}*/
