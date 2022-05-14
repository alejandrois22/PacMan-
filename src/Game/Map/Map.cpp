#include "Map.h"
#include "ShowUltimate.h"
#include "SpeedPowerUp.h"
#include "CherryPowerUp.h"
#include "StrawberryPowerUp.h"
#include "ShowCherry.h"
#include "ShowStrawberry.h"
#include "ShowUltimate.h"





Map::Map(EntityManager* em){
	pacmanSpriteSheet.load("images/Background.png");

    entityManager = em;
}

vector<vector<int>> findPowerUp(int x, int y, vector<vector<int>> maze){
	vector<vector<int>> result;

	if (maze[x][y] == 0 || maze[x][y] == 3) return result;

	if (maze[x][y] == 2){
		result.push_back({x,y});
		return result;
	}

	maze[x][y] = 3;

	vector<vector<int>> up = findPowerUp(x,y-1,maze);
	if (!up.empty()){
		result.insert(result.end(), up.begin(), up.end());
		result.push_back({x, y});
		return result;
	}
	vector<vector<int>> down = findPowerUp(x,y+1,maze);
	if (!down.empty()){
		result.insert(result.end(), down.begin(), down.end());
		result.push_back({x, y});
		return result;
	}
	vector<vector<int>> left = findPowerUp(x-1,y,maze);
	if (!left.empty()){
		result.insert(result.end(), left.begin(), left.end());
		result.push_back({x, y});
		return result;
	}
	vector<vector<int>> right = findPowerUp(x+1,y,maze);
	if (!right.empty()){
		result.insert(result.end(), right.begin(), right.end());
		result.push_back({x, y});
		return result;
	}
	return result;
}

void Map::tick(){
	for (size_t i=0; i<entityManager->entities.size(); i++){
		Entity *entity = entityManager->entities[i];
		if (dynamic_cast<ShowCherry*>(entity) || dynamic_cast<ShowStrawberry*>(entity) || dynamic_cast<ShowUltimatePowerUp*>(entity)){
			maze[(entity->getX()-xOff)/multiplier][(entity->getY()-yOff)/multiplier] = entity->remove? 1:2;
		}
	}
	entityManager->tick();
	player->tick();
	gs->tick();

	if (gps && gpsCounter++ > 22){
		path = findPowerUp((player->getX()-xOff)/multiplier, (player->getY()-yOff)/multiplier, maze);
		gpsCounter = 0;
	}

	if(player->getScore() >=1000 && ultimate == false){
		ultimate = true;
		Entity* randomE = entityManager->entities[ofRandom(entityManager->entities.size())];
		int xPos = randomE->getX();
		int yPos = randomE->getY();


        ShowUltimatePowerUp* ult = new ShowUltimatePowerUp(xPos,yPos,16,16, pacmanSpriteSheet);
        this->addEntity(ult);
		


	}

}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	if (gps){
		ofDrawBitmapString("Path lenght; " + to_string(path.size()), 10, 20);
		ofSetColor(255,161,0);
		for (auto it=path.rbegin(); it != path.rend(); it++){
			ofDrawCircle((*it)[0]*multiplier + xOff + 8, (*it)[1]*multiplier + yOff + 8, 8);
		}
	}
	entityManager->render();
	player->render();

}

void Map::keyPressed(int key){
	player->keyPressed(key);
	gs->keyPressed(key);
	if (key == 'l') gps = !gps;

}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBoundBlock(BoundBlock* e){
    entityManager->boundBlocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::setPlayer(Player* p){
    player = p;
	player->gx = gx;
	player->gy = gy;
}

Player* Map::getPlayer(){
	return player;
}
void Map::setGhostSpawner(GhostSpawner* p){
    gs = p;
}

Map::~Map(){
	delete player;
	delete entityManager;
	delete gs;
}

EntityManager* Map::getEntityManager() {
	return entityManager;
}