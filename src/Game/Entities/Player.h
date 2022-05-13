#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "PowerUp.h"

enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        ofImage EyesSprite;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        bool fast = false;
        bool inmortal = false;
        int stepsSpeed = 0;
        int stepsMortal = 0;
        PowerUp* powerup = 0;
        vector<PowerUp*> powerups;
       
        

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        int getScore();
        FACING getFacing();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        int getSpeed();
        bool getFast();
        bool getInmortal();
        void setFast(bool checkFast);
        void setInmortal(bool checkInmortal);
        void setSpeed(int);
        void setCoords(int x1, int y1);
        bool acceptStrawberry();
        bool stepsCheck();
        int gx;
        int gy;
        
        vector<PowerUp*>& getPowerUps();
        
};