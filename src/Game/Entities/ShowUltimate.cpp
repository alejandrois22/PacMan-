#include "ShowUltimate.h"

ShowUltimatePowerUp::ShowUltimatePowerUp(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 569,51,13,11);
}