#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>
#include <thread>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "Score.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "MovingObject.h"

#define INTERVAL 200 //move interval (in msec // 1000msec = 1sec)
#define PANIC_INTERVAL 400 
#define GHOST_NUM 4
#define DAMAGE_UNIT -1
#define GHOST_BONUS 200
#define LEFT_PORTAL_X 0
#define RIGHT_PORTAL_X 27
#define TWO_SECONDS 2000
#define GIGA_BONUS 100
#define START_SCORE 0
#define START_HEALTH 3
#define PANIC_COUNTER 10
#define WINDOW_SIZE 1000

class GameEngine: public QGraphicsView{
    Q_OBJECT
    private:
        QGraphicsScene *m_scene;
        Map *m_map;
        Score *m_score;
        Score *m_health;
        Player *m_pacman;
        QTimer *m_pacmanTimer;
        QTimer *m_ghostTimer;
        Enemy *m_ghost;
        //Enemy *m_ghosts;
        bool m_damaged;
        void calcDistancesNormal(std::map<int, double>& distances);
        void calcDistancesPanic(std::map<int, double>& distances);
        void decisionTileWhereToMoveNormal();
        void decisionTileWhereToMovePanic();
        void ghostMoveLeft();
        void ghostMoveDown();
        void ghostMoveRight();
        void ghostMoveUp();
        void normalTileWhereToMove();
        void ghostLastDirDown();
        void ghostLastDirUp();
        void ghostLastDirRight();
        void ghostLastDirLeft();
        void pacmanMovingLeft();
        void pacmanMovingRight();
        void pacmanMovingUp();
        void pacmanMovingDown();
        void bonusHandler();
        void collisionHandler();
    private slots:
        void pacmanMoving();
        void ghostMoving();
        //void ghostsMoving();
    public:
        GameEngine();
        ~GameEngine();
};
