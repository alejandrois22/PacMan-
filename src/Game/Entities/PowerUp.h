#pragma once
#include <string>

using namespace std;


class PowerUp{
    public:
    PowerUp(string name){
        this->name = name;
    }
        virtual void activate() = 0;
        void stepsCheck();
        int getRank();
        int compareMethod(PowerUp*);
        int rank = 0;
        string getName(){ return name; };
        //virtual void tick() = 0;
	    // virtual void render() = 0;
    private:
        string name;
};