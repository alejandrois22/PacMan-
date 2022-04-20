#pragma once
#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class StrawberryPowerUp : public PowerUp {

    private: 
        EntityManager* em;
        Player* p;

    public: 
        StrawberryPowerUp(EntityManager*, Player*);
        void activate();
};