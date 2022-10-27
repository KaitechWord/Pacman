#include "../header/Coordinates.h"

Coordinates::Coordinates(int x, int y)
    : m_x(x), m_y(y)
{}

bool Coordinates::areCoordsTheSame(const Coordinates& coords) const{
    if(m_x != coords.m_x || m_y != coords.m_y){
        return false;
    }
    return true;
}