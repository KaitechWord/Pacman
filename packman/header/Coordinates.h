#pragma once

struct Coordinates{
    int m_x, m_y;
    Coordinates(int x, int y);
    bool areCoordsTheSame(const Coordinates& coords) const;
};