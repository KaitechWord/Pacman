#pragma once

#include <QGraphicsPixmapItem>
#include <string>

class Tile: public QGraphicsPixmapItem{
    public:
        Tile(int x, int y, const QImage &image);
    private:

};