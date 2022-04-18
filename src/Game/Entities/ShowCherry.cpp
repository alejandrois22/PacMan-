#include "ShowCherry.h"

ShowCherry::ShowCherry(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 489,50,13,12);
}