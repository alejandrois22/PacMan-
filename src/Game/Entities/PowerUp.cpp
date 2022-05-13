#include <PowerUp.h>

int PowerUp::getRank(){
    return rank;
}

int PowerUp::compareMethod(PowerUp* pw){
    if(this->getRank() > pw->getRank()){
        return 1;
        }
        
    else if(this->getRank() < pw->getRank()){
        return -1;
        }
    
    return 0;
}
