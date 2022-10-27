#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "../header/GameEngine.h"

int main(int argc, char *argv[]){
   QApplication a(argc, argv);
   GameEngine *game = new GameEngine();
   game->show();
   return a.exec();
}
