#pragma once
#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class CherryPowerUp : public PowerUp {

    private: 
        EntityManager* em;
        Player* p;

    public: 
        CherryPowerUp(EntityManager*, Player*);
        void activate();
};