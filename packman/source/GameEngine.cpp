#include "../header/GameEngine.h"

GameEngine::GameEngine()
    : m_scene(new QGraphicsScene()),
      m_map(new Map(LEVEL_MAP, MAP_ROWS, MAP_COLS)), m_score(new Score(0, 0, "Score: ", START_SCORE)),
      m_health(new Score(MAP_COLS / 2.0 * TILE_SIZE, 0, "Health: ", START_HEALTH)),
      m_pacman(new Player()), m_ghost(new Enemy()), m_damaged(false)/*, win(false), m_ghosts(new Enemy[4])*/
{
    m_scene->addItem(m_map);
    m_map->addTiles();
    m_scene->addItem(m_score);
    m_scene->addItem(m_health);
    m_scene->addItem(m_pacman);
    m_scene->addItem(m_ghost);
    m_pacman->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pacman->setFocus();
    setScene(m_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE, WINDOW_SIZE);
    
    m_pacmanTimer = new QTimer(this);
    connect(m_pacmanTimer, SIGNAL(timeout()), this, SLOT(pacmanMoving()));
    m_pacmanTimer->start(INTERVAL);
    
    m_ghostTimer = new QTimer(this);
    connect(m_ghostTimer, SIGNAL(timeout()), this, SLOT(ghostMoving()));
    m_ghostTimer->start(INTERVAL);

    /*for (int i = 0; i < GHOST_NUM; i++) {
        ghostTimer[i] = new QTimer(this);
        connect(ghostTimer[i], SIGNAL(timeout()), this, SLOT(ghostsMoving(i)));
        ghostTimer[i]->start(INTERVAL);
    }*/
}

GameEngine::~GameEngine(){
    delete m_scene;
    delete m_map;
    delete m_score;
    delete m_health;
    delete m_pacman;
    delete m_ghost;
    delete m_pacmanTimer;
    delete m_ghostTimer;

}

void GameEngine::bonusHandler(){
    int bonus = m_map->isThereBonus(m_pacman->getNowX(), m_pacman->getNowY() * MAP_COLS);
    if(bonus != 0){
        m_score->addScore(bonus);
        if(bonus == GIGA_BONUS){
            m_ghost->setStatus(Panic);
            m_ghost->setPanicTime(PANIC_COUNTER);
            m_ghost->setSpecialImage();
            m_ghost->reverseDirection();
            m_ghostTimer->setInterval(PANIC_INTERVAL);
        }
        m_map->decreasePointTilesNum();
    }
}

void GameEngine::pacmanMovingLeft(){
    if(!m_map->isThereObstacle(m_pacman->getNowX() - 1, m_pacman->getNowY() * MAP_COLS)){
        m_pacman->moveLeft();
        bonusHandler();
    }
    collisionHandler();    
}

void GameEngine::pacmanMovingRight(){
    if(!m_map->isThereObstacle(m_pacman->getNowX() + 1, m_pacman->getNowY() * MAP_COLS)){
        m_pacman->moveRight();
        bonusHandler();
    }
    collisionHandler();    
}

void GameEngine::pacmanMovingUp(){
    if(!m_map->isThereObstacle(m_pacman->getNowX(), (m_pacman->getNowY() - 1) * MAP_COLS)){
        m_pacman->moveUp();
        bonusHandler();
    }
    collisionHandler();
}

void GameEngine::pacmanMovingDown(){
    if(!m_map->isThereObstacle(m_pacman->getNowX(), (m_pacman->getNowY() + 1) * MAP_COLS)){
        m_pacman->moveDown();
        bonusHandler();
    }
    collisionHandler();
}


void GameEngine::pacmanMoving(){
    if(m_health->getScore() == 0){
        m_pacmanTimer->stop();
        m_ghostTimer->stop();
        std::chrono::milliseconds timespan(TWO_SECONDS);
        std::this_thread::sleep_for(timespan);
        QCoreApplication::quit();
    }
    if(m_map->getPointTilesNum() == 0){
        m_pacmanTimer->stop();
        m_ghostTimer->stop();
        std::chrono::milliseconds timespan(TWO_SECONDS);
        std::this_thread::sleep_for(timespan);
        QCoreApplication::quit();
    }
    if(m_pacman->getNowCoords().m_x == LEFT_PORTAL_X){
        m_pacman->moveLeftPortal();
    }
    else if(m_pacman->getNowCoords().m_x == RIGHT_PORTAL_X){
        m_pacman->moveRightPortal();
    }
    switch(m_pacman->getDirection()){
        case Left:
            pacmanMovingLeft();
            break;
        case Right:
            pacmanMovingRight();
            break;
        case Up:
            pacmanMovingUp();
            break;
        case Down:
            pacmanMovingDown();
            break;
        default:
            break;        
    }
}

void GameEngine::ghostMoveLeft(){
    m_ghost->setDirection(Left);
    m_ghost->moveLeft();
}

void GameEngine::ghostMoveRight(){
    m_ghost->setDirection(Right);
    m_ghost->moveRight();
}

void GameEngine::ghostMoveUp(){
    m_ghost->setDirection(Up);
    m_ghost->moveUp();
}

void GameEngine::ghostMoveDown(){
    m_ghost->setDirection(Down);
    m_ghost->moveDown();
}

void GameEngine::collisionHandler(){
    if((m_ghost->getNowCoords().areCoordsTheSame(m_pacman->getNowCoords()) || (m_ghost->getNowCoords().areCoordsTheSame(m_pacman->getOldCoords()) && m_ghost->getOldCoords().areCoordsTheSame(m_pacman->getNowCoords()))) && !m_damaged){
        if(m_ghost->getStatus() == Normal){
            m_health->addScore(DAMAGE_UNIT);
        }
        else{
            m_ghost->setNowX(m_ghost->getStartCoords().m_x);
            m_ghost->setNowY(m_ghost->getStartCoords().m_y);
            m_ghost->setPos(m_ghost->getStartCoords().m_x * TILE_SIZE + m_ghost->getStartCoords().m_x, m_ghost->getStartCoords().m_y * TILE_SIZE + m_ghost->getStartCoords().m_y + MAP_START_Y);
            m_score->addScore(GHOST_BONUS);
        }
    }
    else{
        m_damaged = false;
    }
}

void GameEngine::decisionTileWhereToMoveNormal(){
    std::map<int, double> distances;
	calcDistancesNormal(distances);
	if(distances[0] <= distances[1] && distances[0] <= distances[2] && distances[0] <= distances[3]){
        ghostMoveLeft();
	}
	else if(distances[1] <= distances[0] && distances[1] <= distances[2] && distances[1] <= distances[3]){
		ghostMoveRight();
	}
	else if(distances[2] <= distances[0] && distances[2] <= distances[1] && distances[2] <= distances[3]){
		ghostMoveUp();
    }
    else if(distances[3] <= distances[0] && distances[3] <= distances[1] && distances[3] <= distances[2]){
        ghostMoveDown();
    }
}

void GameEngine::decisionTileWhereToMovePanic(){
    std::map<int, double> distances;
	calcDistancesPanic(distances);
	if(distances[0] >= distances[1] && distances[0] >= distances[2] && distances[0] >= distances[3]){
        ghostMoveLeft();
	}
	else if(distances[1] >= distances[0] && distances[1] >= distances[2] && distances[1] >= distances[3]){
		ghostMoveRight();
	}
	else if(distances[2] >= distances[0] && distances[2] >= distances[1] && distances[2] >= distances[3]){
		ghostMoveUp();
    }
    else if(distances[3] >= distances[0] && distances[3] >= distances[1] && distances[3] >= distances[2]){
        ghostMoveDown();
    }
}

void GameEngine::ghostLastDirLeft(){
    if(!m_map->isThereObstacle(m_ghost->getNowX() - 1, m_ghost->getNowY() * MAP_COLS)){ 
       ghostMoveLeft();
    }
    
    else if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() - 1) * MAP_COLS)){ 
        ghostMoveUp();
    }
    else{ 
        ghostMoveDown();
    }
}

void GameEngine::ghostLastDirRight(){
    if(!m_map->isThereObstacle(m_ghost->getNowX() + 1, m_ghost->getNowY() * MAP_COLS)){
        ghostMoveRight();
    }
    else if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() - 1) * MAP_COLS)){ 
        ghostMoveUp();
    }
    else{ 
        ghostMoveDown();
    }
}

void GameEngine::ghostLastDirUp(){
    if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() - 1) * MAP_COLS)){ 
        ghostMoveUp();
    }
    else if(!m_map->isThereObstacle(m_ghost->getNowX() - 1, m_ghost->getNowY() * MAP_COLS)){ 
        ghostMoveLeft();
    }
    else{
        ghostMoveRight();
    }
}

void GameEngine::ghostLastDirDown(){
    if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() + 1) * MAP_COLS)){ 
        ghostMoveDown();
    }
    else if(!m_map->isThereObstacle(m_ghost->getNowX() - 1, m_ghost->getNowY() * MAP_COLS)){ 
        ghostMoveLeft();
    }
    else{
        ghostMoveRight();
    }
}

void GameEngine::normalTileWhereToMove(){
    switch(m_ghost->getDirection()){
        case Left:
            ghostLastDirLeft();
            break;
        case Right:
            ghostLastDirRight();
            break;
        case Up:
            ghostLastDirUp();
            break;
        case Down:
            ghostLastDirDown();
            break;
        default:
            break;        
    }
}


void GameEngine::ghostMoving(){
    if(m_ghost->getNowCoords().m_x == LEFT_PORTAL_X){
        m_ghost->moveLeftPortal();
    }
    else if(m_ghost->getNowCoords().m_x == RIGHT_PORTAL_X){
        m_ghost->moveRightPortal();
    }
    if(m_ghost->getStatus() == Normal){
        if(m_map->isThereDecision(m_ghost->getNowX(), m_ghost->getNowY() * MAP_COLS)){
            decisionTileWhereToMoveNormal();
        }    
        else{
            normalTileWhereToMove();
        }
    }
    else{
        if(m_map->isThereDecision(m_ghost->getNowX(), m_ghost->getNowY() * MAP_COLS)){
            decisionTileWhereToMovePanic();
        }    
        else{
            normalTileWhereToMove();
        }
        m_ghost->decreasePanicTime();
    }
    if(m_ghost->getNowCoords().areCoordsTheSame(m_pacman->getNowCoords())){
        if(m_ghost->getStatus() == Normal){
            m_health->addScore(DAMAGE_UNIT);
        }
        else{
            m_ghost->setNowX(m_ghost->getStartCoords().m_x);
            m_ghost->setNowY(m_ghost->getStartCoords().m_y);
            m_ghost->setPos(m_ghost->getStartCoords().m_x * TILE_SIZE + m_ghost->getStartCoords().m_x, m_ghost->getStartCoords().m_y * TILE_SIZE + m_ghost->getStartCoords().m_y + MAP_START_Y);
            m_score->addScore(GHOST_BONUS);
        }
        m_damaged = true;
    }
    if(m_ghost->getPanicTime() == 0){
        m_ghost->setNormalImage();
        m_ghost->setStatus(Normal);
        m_ghostTimer->setInterval(INTERVAL);
    }
}

void GameEngine::calcDistancesNormal(std::map<int, double>& distances){
	if(!m_map->isThereObstacle((m_ghost->getNowX() - 1), m_ghost->getNowY() * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - (m_ghost->getNowX() - 1)) * (m_pacman->getNowX() - (m_ghost->getNowX() - 1));
		int yDistanceDoubled = (m_pacman->getNowY() - m_ghost->getNowY()) * (m_pacman->getNowY() - m_ghost->getNowY());
		distances[0] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX() + 1, m_ghost->getNowY() * MAP_COLS)){
		int xDistanceDoubled = (m_pacman->getNowX() - (m_ghost->getNowX() + 1)) * (m_pacman->getNowX() - (m_ghost->getNowX() + 1));
		int yDistanceDoubled = (m_pacman->getNowY() - m_ghost->getNowY()) * (m_pacman->getNowY() - m_ghost->getNowY());
		distances[1] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() - 1) * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - m_ghost->getNowX()) * (m_pacman->getNowX() - m_ghost->getNowX());
		int yDistanceDoubled = (m_pacman->getNowY() - (m_ghost->getNowY() - 1)) * (m_pacman->getNowY() - (m_ghost->getNowY() - 1));
		distances[2] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() + 1) * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - m_ghost->getNowX()) * (m_pacman->getNowX() - m_ghost->getNowX());
		int yDistanceDoubled = (m_pacman->getNowY() - (m_ghost->getNowY() + 1)) * (m_pacman->getNowY() - (m_ghost->getNowY() + 1));
		distances[3] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	for(int i = 0; i < 4; i++){
		if(!(distances.count(i) > 0)){
			distances[i] = std::numeric_limits<double>::max();	
		}
	}
}

void GameEngine::calcDistancesPanic(std::map<int, double>& distances){
	if(!m_map->isThereObstacle((m_ghost->getNowX() - 1), m_ghost->getNowY() * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - (m_ghost->getNowX() - 1)) * (m_pacman->getNowX() - (m_ghost->getNowX() - 1));
		int yDistanceDoubled = (m_pacman->getNowY() - m_ghost->getNowY()) * (m_pacman->getNowY() - m_ghost->getNowY());
		distances[0] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX() + 1, m_ghost->getNowY() * MAP_COLS)){
		int xDistanceDoubled = (m_pacman->getNowX() - (m_ghost->getNowX() + 1)) * (m_pacman->getNowX() - (m_ghost->getNowX() + 1));
		int yDistanceDoubled = (m_pacman->getNowY() - m_ghost->getNowY()) * (m_pacman->getNowY() - m_ghost->getNowY());
		distances[1] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() - 1) * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - m_ghost->getNowX()) * (m_pacman->getNowX() - m_ghost->getNowX());
		int yDistanceDoubled = (m_pacman->getNowY() - (m_ghost->getNowY() - 1)) * (m_pacman->getNowY() - (m_ghost->getNowY() - 1));
		distances[2] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	if(!m_map->isThereObstacle(m_ghost->getNowX(), (m_ghost->getNowY() + 1) * MAP_COLS)){ 
		int xDistanceDoubled = (m_pacman->getNowX() - m_ghost->getNowX()) * (m_pacman->getNowX() - m_ghost->getNowX());
		int yDistanceDoubled = (m_pacman->getNowY() - (m_ghost->getNowY() + 1)) * (m_pacman->getNowY() - (m_ghost->getNowY() + 1));
		distances[3] = sqrt(xDistanceDoubled + yDistanceDoubled);
	}
	for(int i = 0; i < 4; i++){
		if(!(distances.count(i) > 0)){
			distances[i] = std::numeric_limits<double>::min();	
		}
	}
}
