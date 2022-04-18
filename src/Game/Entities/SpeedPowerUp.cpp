#include "SpeedPowerUp.h"

SpeedPowerUp::SpeedPowerUp(Player* p){
    this->p = p;
}
void SpeedPowerUp::activate(){
    p->setSpeed(8);
    p->setFast(true);
    }