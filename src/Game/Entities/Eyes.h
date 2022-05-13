#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "Animation.h"

class Eyes: public Entity{
    public:
    Eyes(int, int, int, int, ofImage);
    void render();
    void tick();
    int gx;
    int gy;  
private:
 Animation* eyesAnim;

};