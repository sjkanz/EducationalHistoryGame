#include "Disaster.h"

#ifndef fishing
#define fishing

class Fish {
    private:
        float cost;
    public:
        Fish(float cost) {
            this->cost = cost;
        }
        float get_cost() {
            return this->cost;
        }
        void set_cost(float cost) {
            this->cost = cost;
        }
};

#endif