#include "ShowStrawberry.h"

ShowStrawberry::ShowStrawberry(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 506,50,11,12);
}