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

    private:
      EntityManager *entityManager;
      Player *player;
      GhostSpawner* gs;
      bool ultimate = false;
      ofImage pacmanSpriteSheet;
};