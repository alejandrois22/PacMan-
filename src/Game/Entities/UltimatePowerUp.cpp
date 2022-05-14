#include "UltimatePowerUp.h"


UltimatePowerUp::UltimatePowerUp(Player* p) : PowerUp("Ultimate"){
    this-> p = p;
}

void UltimatePowerUp::activate(){
    selectionSort(p->getPowerUps());
    
}
void UltimatePowerUp::selectionSort(vector<PowerUp*> &powers){
    for (unsigned int i=0; i<powers.size()-1; i++) {
        int minPos = i;
        for (unsigned int j=i; j<powers.size(); j++) {
            if (powers[j]->compareMethod(powers[minPos]) == 1)  {
                minPos = j;
            }
        }
        PowerUp* temp = powers[i];
        powers[i] = powers[minPos];
        powers[minPos] = temp;
    }
}