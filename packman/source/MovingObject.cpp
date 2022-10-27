#include "../header/MovingObject.h"

MovingObject::MovingObject(int startX, int startY, const QImage &imgNormal, const QImage &imgSpecial)
    : QGraphicsPixmapItem(), m_startingPos(startX, startY), m_nowCoords(m_startingPos.m_x, m_startingPos.m_y), m_oldCoords(m_startingPos.m_x, m_startingPos.m_y), m_imgNormal(imgNormal.scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)), m_imgSpecial(imgSpecial.scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation))
{
    setPos(m_startingPos.m_x * TILE_SIZE + m_startingPos.m_x, m_startingPos.m_y * TILE_SIZE + m_startingPos.m_y + MAP_START_Y);
    setPixmap(QPixmap::fromImage(m_imgNormal));
}

void MovingObject::moveLeft(){
    m_oldCoords.m_x = m_nowCoords.m_x;
    m_nowCoords.m_x -= 1;
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

void MovingObject::moveRight(){
    m_oldCoords.m_x = m_nowCoords.m_x;
    m_nowCoords.m_x += 1;
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

void MovingObject::moveUp(){
    m_oldCoords.m_y = m_nowCoords.m_y;
    m_nowCoords.m_y -= 1;
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

void MovingObject::moveDown(){
    m_oldCoords.m_y = m_nowCoords.m_y;
    m_nowCoords.m_y += 1;
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

void MovingObject::moveRightPortal(){
    m_oldCoords.m_x = m_nowCoords.m_x;
    m_nowCoords.m_x = 0; 
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

void MovingObject::moveLeftPortal(){
    m_oldCoords.m_x = m_nowCoords.m_x;
    m_nowCoords.m_x = 27; 
    setPos(m_nowCoords.m_x * TILE_SIZE + m_nowCoords.m_x, m_nowCoords.m_y * TILE_SIZE + m_nowCoords.m_y + MAP_START_Y);
}

Coordinates MovingObject::getNowCoords() const{
    return m_nowCoords;
}

Coordinates MovingObject::getOldCoords() const{
    return m_oldCoords;
}

int MovingObject::getNowX() const{
    return m_nowCoords.m_x;
}

int MovingObject::getNowY() const{
    return m_nowCoords.m_y;
}

int MovingObject::getOldX() const{
    return m_oldCoords.m_x;
}

int MovingObject::getOldY() const{
    return m_oldCoords.m_y;
}
