#include "Eyes.h"

Eyes::Eyes(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    //eyesAnim = new Animation(10, {sprite.cropFrom(586,83,16,16)});
    //eyesAnim= new Animation(10, {sprite.cropFrom(617,83,16,16)});
    //eyesAnim = new Animation(10, {sprite.cropFrom(600,83,16,16)});
    vector<ofImage> eyesFrames;

    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    eyesFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    eyesFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    eyesFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    eyesFrames.push_back(temp);
    eyesAnim = new Animation(10, eyesFrames);
}