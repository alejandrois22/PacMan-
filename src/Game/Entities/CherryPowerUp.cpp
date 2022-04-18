#include "CherryPowerUp.h"

CherryPowerUp::CherryPowerUp(EntityManager* em, Player* p){
    this->em = em;
    this->p = p;
}

void CherryPowerUp::activate(){

    int i= ofRandom(em->entities.size());
    ofRectangle coordinates = em->entities[i]->getBounds();
    em->entities[i]->remove = true;
    p->setCoords(coordinates.getX(), coordinates.getY());
}