#pragma once



class PowerUp{
    public:
        virtual void activate() = 0;
        void stepsCheck();
        int getRank();

    private:
        int rank = 0;
};