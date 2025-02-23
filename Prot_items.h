#ifndef prot_items
#define prot_items

#include "Disaster.h"
// #include "Person.h"

class Stilts : public Item {
    private:
        float height;
        bool support;
    public:
        static int total_stilts;
        const int max_stilts = 5; // if >= 5 stilts, there's less resistance to wind
        Stilts(Person &p): Item (3.0, 10, FLOOD) {
                this->height = 1;
                this->support = false;
                total_stilts++;
                    if (total_stilts >= max_stilts) {
                        (p).set_wind_prot((p).get_wind_prot() - 1);
                    }
                    (p).set_water_prot((p).get_water_prot() + 1);
            }
        float get_height() {
            return this->height;
        }
        void set_height(float height) {
            this->height = height;
        }
        bool get_support() {
            return this->support;
        }
        void set_support(bool support) {
            this->support = support;
        }
        void minus_health(float health) {
            this->set_health(this->get_health() - health);
        }
        void add_support() {
            this->set_health(this->get_health() + 10);
            this->set_support(true);
        }
        void repair() {
            if(this->get_support()) {
                this->set_health(20);
            }
            else {
                this->set_health(10);
            }
        }
};

#endif