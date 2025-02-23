#ifndef fishing
#define fishing

#include "Disaster.h"

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