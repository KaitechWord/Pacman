#include "../header/Map.h"
#include <QDebug>
#include <iostream>

const int MAP_START_X = 0;
const int MAP_START_Y = 100;
const int MAP_ROWS = 31;
const int MAP_COLS = 28;
const int TILE_SIZE = 25;
const int POINT_TILES = 245;
int LEVEL_MAP[] = 
{   // 1 - obstacle || 2 - sciezka || 3 - sciezka z punktem || 4 - sciezka z giga punktem || 5 - skrzyzowanie || 6 - skrzyzowanie z punktem || 7 - portal
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 4, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 6, 3, 3, 3, 3, 6, 3, 3, 6, 3, 3, 6, 3, 3, 6, 3, 3, 6, 3, 3, 6, 3, 3, 3, 3, 6, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 3, 3, 3, 3, 3, 6, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 6, 3, 3, 3, 3, 3, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 2, 2, 5, 2, 2, 5, 2, 2, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    7, 2, 2, 2, 2, 2, 6, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 2, 6, 2, 2, 2, 2, 2, 7,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 5, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
    1, 3, 3, 3, 3, 3, 6, 3, 3, 6, 3, 3, 3, 1, 1, 3, 3, 3, 6, 3, 3, 6, 3, 3, 3, 3, 3, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1,
    1, 4, 3, 3, 1, 1, 6, 3, 3, 6, 3, 3, 6, 2, 3, 6, 3, 3, 6, 3, 3, 6, 1, 1, 3, 3, 4, 1,
    1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1,
    1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1,
    1, 3, 3, 6, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 6, 3, 3, 1,
    1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1,
    1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1,
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};


Map::Map(int *levelMap, const int rows, const int cols)
	: QGraphicsRectItem(MAP_START_X, MAP_START_Y, TILE_SIZE*cols + cols, TILE_SIZE*rows + rows), m_rows(rows), m_cols(cols), m_numberOfPointTiles(POINT_TILES)
{
    m_map = new int[rows*cols];
    m_tiles = new Tile * [rows*cols];
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            m_map[i * m_cols + j] = levelMap[i * m_cols + j];
            setTiles(j, i * m_cols);
        }
    }
}

void Map::updateTile(int x, int y, int newPathNum){
    switch(newPathNum){
        case 2:{//(to be uploaded) path 
            QImage imgScaled = QImage("./image/white.png").scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            m_tiles[x + y]->setPixmap(QPixmap::fromImage(imgScaled));
            m_map[x + y] = newPathNum;
            }
            break;
        case 3:{//(to be uploaded) path + bonus
            QImage imgScaled = QImage("./image/green.png").scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            m_tiles[x + y]->setPixmap(QPixmap::fromImage(imgScaled));
            m_map[x + y] = newPathNum;
            }
            break;
        case 5:{//(to be uploaded) decision tile (same color as normal path)
            QImage imgScaled = QImage("./image/white.png").scaled(TILE_SIZE, TILE_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            m_tiles[x + y]->setPixmap(QPixmap::fromImage(imgScaled));
            m_map[x + y] = newPathNum;
            }
            break;
        default:
            break; 
    }
}

void Map::setTiles(int x, int y){
    switch(m_map[y + x]){
        case 1:{//obstacle
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/grey.PNG"));
            }
            break;
        case 2:{//path
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/white.png"));
            }
            break;
        case 3:{//path + bonus   
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/green.png"));
            }
            break;
        case 4:{//path + giga bonus
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/yellow.JPG"));
            }
            break;
        case 5:{//decision tile (same color as normal path)
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/white.png"));
            }
            break;
        case 6:{//decision tile + bonus (same color as normal path + bonus)
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/green.png"));
            }
            break;
        case 7:{//portal (same color as normal path) 
            m_tiles[y + x] = new Tile(x, y/m_cols, QImage("./image/white.png"));
            }
            break;
        default:
            break; 
    }
}

void Map::addTiles(){
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            scene()->addItem(m_tiles[j + i * m_cols]);
        }
    }
}

bool Map::isThereObstacle(int x, int y) const{
    if(m_map[x + y] == 1){
        return true;
    }
    else{
        return false;
    }
}

bool Map::isThereDecision(int x, int y) const{
    if(m_map[x + y] == 5 || m_map[x + y] == 6){
        return true;
    }
    else{
        return false;
    }
}

int Map::isThereBonus(int x, int y){
    switch(m_map[x + y]){
        case 3:
            updateTile(x, y, 2);
            return 30;
            break;
        case 4:
            updateTile(x, y, 2);
            return 100;
            break;
        case 6:
            updateTile(x, y, 5);
            return 30;
            break;
        default:
            return 0;
            break;
    }
}
