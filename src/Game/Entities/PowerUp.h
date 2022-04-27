#pragma once



class PowerUp{
    public:
        virtual void activate() = 0;
        void stepsCheck();
        int getRank();
        int compareMethod(PowerUp*);
        int rank = 0;
};