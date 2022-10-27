#pragma once
#include "Coordinates.h"
#include "Map.h"
#include <string>
#include <QGraphicsPixmapItem>

enum Direction{
    Left,
    Up,
    Right,
    Down
};

class MovingObject:public QGraphicsPixmapItem{
    protected:
        Coordinates m_startingPos;
        Coordinates m_nowCoords;
        Coordinates m_oldCoords;
        const QImage m_imgNormal;
        const QImage m_imgSpecial;
    public:
        MovingObject(int startX, int startY, const QImage &imgNormal, const QImage &imgSpecial);
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void moveRightPortal();
        void moveLeftPortal();
        int getNowX() const;
        int getNowY() const;
        void setNowX(int x) {m_nowCoords.m_x = x;};
        void setNowY(int y) {m_nowCoords.m_y = y;};
        void setSpecialImage() { setPixmap(QPixmap::fromImage(m_imgSpecial));};
        void setNormalImage() { setPixmap(QPixmap::fromImage(m_imgNormal));};
        int getOldX() const;
        int getOldY() const;
        Coordinates getNowCoords() const;
        Coordinates getOldCoords() const;
        Coordinates getStartCoords() const{ return m_startingPos; };
};
