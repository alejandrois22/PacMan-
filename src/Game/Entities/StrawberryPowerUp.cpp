#include "StrawberryPowerUp.h"

StrawberryPowerUp::StrawberryPowerUp(EntityManager* em, Player* p){
    this->em = em;
    this->p = p;
    this->rank = 3;
}

void StrawberryPowerUp::activate(){
    if (p->acceptStrawberry() == true){
    p->setInmortal(true);
    }
}