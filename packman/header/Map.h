#pragma once

#include "Tile.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

extern const int MAP_START_X;
extern const int MAP_START_Y;
extern const int MAP_ROWS;
extern const int MAP_COLS;
extern const int TILE_SIZE;
extern int LEVEL_MAP[];

class Map: public QGraphicsRectItem{
	private:
		int *m_map;
        const int m_rows;
        const int m_cols;
        int m_numberOfPointTiles;
        Tile **m_tiles;
        void setTiles(int x, int y);
	public:
		Map(int *levelMap, const int rows, const int cols);
        ~Map(){
            delete[] m_map;
            for(int i = 0; i < m_rows*m_cols; i++){
                delete m_tiles[i];
            }
            delete[] m_tiles;
        }
        bool isThereObstacle(int x, int y) const;
        bool isThereDecision(int x, int y) const;
        int isThereBonus(int x, int y);
        void addTiles();
        void updateTile(int x, int y, int newPathNum);
        int getPointTilesNum(){ return m_numberOfPointTiles;};
        void decreasePointTilesNum(){ m_numberOfPointTiles--;};
};
