#include "../header/Tile.h"
#include "../header/Map.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <iostream>

Tile::Tile(int x, int y, const QImage &image)
    : QGraphicsPixmapItem()
{
    setPos(x * TILE_SIZE + x, y * TILE_SIZE + y + MAP_START_Y);
    QImage imgScaled = image.scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(imgScaled));
}