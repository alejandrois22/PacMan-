#pragma once
#include "PowerUp.h"
#include "Player.h"

class SpeedPowerUp : public PowerUp{
    
    private:
        Player* p;

    public: 
        SpeedPowerUp(Player*);
        void activate();
};

