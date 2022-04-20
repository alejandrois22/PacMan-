#include "StrawberryPowerUp.h"

StrawberryPowerUp::StrawberryPowerUp(EntityManager* em, Player* p){
    this->em = em;
    this->p = p;
}

void StrawberryPowerUp::activate(){
    if (p->acceptStrawberry() == true){
    p->setInmortal(true);
    }
}