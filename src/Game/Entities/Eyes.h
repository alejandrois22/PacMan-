#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "Animation.h"

class Eyes: public Entity{
    public:
        Eyes(int, int, int, int, ofImage);

private:
 Animation* eyesAnim;

};