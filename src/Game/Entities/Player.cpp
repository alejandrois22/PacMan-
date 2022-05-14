#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Eyes.h"
#include "GameState.h"
#include "SpeedPowerUp.h"
#include "ShowCherry.h"
#include "CherryPowerUp.h"
#include "ShowStrawberry.h"
#include "StrawberryPowerUp.h"
#include "ShowUltimate.h"
#include "UltimatePowerUp.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    moving = MLEFT;
    
}
void Player::tick(){

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }
    if (inmortal){
        stepsMortal++;
        if (stepsMortal >= 60){
            inmortal = false;
            stepsMortal = 0;
        }
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if (!inmortal){
    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);

    ofDrawBitmapString("Current PowerUp:", ofGetWidth()/2-500, 50);

    for (unsigned int i=0; i<powerups.size(); i++){
        ofDrawBitmapString(powerups[i]->getName() + "\t" + "Rank: " + to_string(powerups[i]->getRank()) , ofGetWidth()/2-500, 80+i*10);
        cout << powerups[0]->getName();
    }
    if (!acceptStrawberry()){
    ofDrawBitmapString("Too close to Ghost", ofGetWidth()/2+345,80);
    }
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            if (!inmortal)
            die();
            break;
        case 'm':
		if(health < 3){
		  health++;
		    break;
         }
        case ' ':
        if (powerups.size() >= 1){
        powerup = powerups[0];
            if (powerup != nullptr){
                powerup->activate();
                powerups.erase(powerups.begin());
        }
    }
        break;
        case '-': //Sets the first powerup to SpeedPowerUp.
        powerups.push_back(new SpeedPowerUp(this));
        break;

        case ']':
        score += 500;
        break;
}
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
int Player::getSpeed(){ return speed; }
bool Player::getFast(){ return fast; }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
void Player::setSpeed(int s){ speed = s; }
vector<PowerUp*>& Player::getPowerUps(){return powerups;}


void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity) || dynamic_cast<ShowCherry*>(entity) || dynamic_cast<ShowStrawberry*>(entity) || dynamic_cast<ShowUltimatePowerUp*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            if(dynamic_cast<ShowCherry*>(entity)){
                powerups.push_back(new CherryPowerUp(em,this));
            }
            if(dynamic_cast<ShowStrawberry*>(entity)){
                powerups.push_back(new StrawberryPowerUp(em,this));
            }
            if(dynamic_cast<ShowUltimatePowerUp*>(entity)){
                PowerUp* ult = new UltimatePowerUp(this);
                ult->activate();
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
                EyesSprite.load("images/Background.png");
                Eyes* ey= new Eyes(ghost->getX(), ghost->getY(),16, 16,EyesSprite);
                ey->gx = gx;
                ey->gy = gy;
                em->entities.push_back(ey);
            }
            else {
                if (!inmortal){
                die();
                }
            }
                
        }
    }
}
    

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

void Player::setFast(bool checkFast){
    this->fast = checkFast;
}

void Player::setInmortal(bool checkInmortal)
{
    this->inmortal = checkInmortal;
}

bool Player::acceptStrawberry(){
    for (Entity* entity:em->ghosts){
        Ghost* ghost = dynamic_cast<Ghost*>(entity);
        ofRectangle coords = ghost->getBounds();
        if (ofDist(coords.getX(),coords.getY(),this->x,this->y) <= 45)
            return false;
        }
    return true;
}


void Player::setCoords(int x1, int y1){
    x = x1;
    y = y1;
}


Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}