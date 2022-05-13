#include "Eyes.h"
#include "GhostSpawner.h"
Eyes::Eyes(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    vector<ofImage> eyesFrames;

    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 82, 16, 16);
    eyesFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 82, 16, 16);
    eyesFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 82, 16, 16);
    eyesFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 82, 16, 16);
    eyesFrames.push_back(temp);
    eyesAnim = new Animation(10, eyesFrames);
}

void Eyes::render(){
    
    eyesAnim->getCurrentFrame().draw(x,y,width,height);
}
void Eyes::tick(){
 if(this->x >ofGetWidth()/2){
     x= x - 1;
 }
 else{
    x = x + 1;
 }
 if(this->y > ofGetHeight()/2){
     y = y-1;
 }
 else{
    y= y + 1;
 }
 if(this->x == ofGetWidth()/2 && this->y == ofGetHeight()/2){
    this-> remove = true;

 }
}
//with the find