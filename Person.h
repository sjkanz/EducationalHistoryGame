#include "Prot_items.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef person
#define person

class Person {
    private:
        float money; // how much money do you have?
        float health; // how much health do you have?
        int wind_prot; // how much wind protection do you have?
        int water_prot; // how well can you protect against floods?
        int level; // what level are you on?
        std::vector<Item*> items;
    public:
        Person(float health, float money, int wind_prot, int water_prot, std::vector<Item*> items) {
            this->health = health;
            this->money = money;
            this->wind_prot = wind_prot;
            this->water_prot = water_prot;
        }
        float get_money() {
            return this->money;
        }
        void set_money(float money) {
            this->money = money;
        }
        void add_money(float money) {
            this->money += money;
        }
        void remove_money(float money) {
            this->money -= money;
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
        std::vector<Item*> get_items() {
            return this->items;
        }
        void set_items(std::vector<Item*> items) {
            this->items = items;
        }
        int get_level() {
            return this->level;
        }
        void set_level(int level) {
            this->level = level;
        }
        void add_item(Item* item) {
            this->money += item->get_cost();
            this->items.push_back(item);
        }
        void remove_item(Item* item) {
            this->money -= item->get_cost();
            for (int i = 0; i < this->items.size(); i++) {
                if (this->items[i] == item) {
                    this->items.erase(this->items.begin() + i);
                    break;
                }
            }
        }

};

#endif