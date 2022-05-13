#pragma once

#include "PowerUp.h"
#include "Player.h"
#include "Map.h"

class UltimatePowerUp : public PowerUp{
    public:
    UltimatePowerUp(Player*);
    void activate();
    void selectionSort(vector<PowerUp*>&);
    private:
    Player* p;

};