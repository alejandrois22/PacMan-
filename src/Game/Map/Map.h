#pragma once

#include "Player.h"
#include "GhostSpawner.h"
#include "EntityManager.h"

class Map{
    public:
      Map(EntityManager*);
      ~Map();
      void addBoundBlock(BoundBlock*);
      void addEntity(Entity*);
      Player* getPlayer();
      void setPlayer(Player*);
      void setGhostSpawner(GhostSpawner*);
      void tick();
      void render();
      void keyPressed(int key);
		  void mousePressed(int x, int y, int button);
		  void keyReleased(int key);
      EntityManager *getEntityManager();
      int gx;
      int gy;
      void setMaze(vector<vector<int>> maze){ this->maze = maze; }
      void setOffsets(int mult, int xOff, int yOff){ multiplier = mult; this->xOff = xOff; this->yOff = yOff; }
      
    private:
      EntityManager *entityManager;
      Player *player;
      GhostSpawner* gs;
      bool ultimate = false;
      ofImage pacmanSpriteSheet;
      vector<vector<int>> maze;
      int multiplier, xOff, yOff;
      bool gps = false;
      int gpsCounter = 0; 
      vector<vector<int>> path;
};