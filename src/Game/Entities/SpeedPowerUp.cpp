#include "SpeedPowerUp.h"

SpeedPowerUp::SpeedPowerUp(Player* p){
    this->p = p;
}
void SpeedPowerUp::activate(){
    if (p->getSpeed() == 4){
    p->setSpeed(8);
    }
    else p->setSpeed(4);
    
    }
