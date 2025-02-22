#include "Prot_items.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef person
#define person

class Person {
    private:
        float money;
        float health; // how much health do you have?
        int wind_prot; // how much wind protection do you have?
        int water_prot; // how well can you protect against floods?
        std::string filename;
        std::type_info items;
    public:
        Person(float health, float money, int wind_prot, int water_prot, std::string filename) {
            this->health = health;
            this->money = money;
            this->wind_prot = wind_prot;
            this->water_prot = water_prot;
            this->filename = filename;
        }
        float get_money() {
            return this->money;
        }
        void set_money(float money) {
            this->money = money;
        }
        float get_health() {
            return this->health;
        }
        void set_health(float health) {
            this->health = health;
        }
        int get_wind_prot() {
            return this->wind_prot;
        }
        void set_wind_prot(int wind_prot) {
            this->wind_prot = wind_prot;
        }
        int get_water_prot() {
            return this->water_prot;
        }
        void set_water_prot(int water_prot) {
            this->water_prot = water_prot;
        }
        bool add_item(item_type item, Item item_obj) {
            std::fstream output(this->filename, std::ios::binary | std::ios::app);
            if (output.is_open()) {
                if (item == item_type::STILTS) {
                    
                    output.write(reinterpret_cast<char*>(&item_obj), sizeof(Item));
                }
                output.close();
            }
            else {
                return false;
            }
            return true;
        }
};

#endif