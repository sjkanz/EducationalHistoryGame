#ifndef disaster
#define disaster
// #include "Person.h"
// #include "Prot_items.h"
#include <string>
#include <vector>

enum disaster_type
{
    TYPHOON,
    FLOOD,
    // Volcanic_eruption,
    EARTHQUAKE
};

class Item
{
private:
    float cost;
    int health;
    bool destroyed;
    int weakness;
    std::string info;

public:
    Item(float cost, int health, int weakness, std::string info)
    {
        this->cost = cost;
        this->health = health;
        this->destroyed = false;
        this->weakness = weakness;
        this->info = info;
    }
    float get_cost()
    {
        return this->cost;
    }
    void set_cost(float cost)
    {
        this->cost = cost;
    }
    int get_health()
    {
        return this->health;
    }
    void set_health(int health)
    {
        this->health = health;
    }
    bool get_destroyed()
    {
        return this->destroyed;
    }
    void set_destroyed(bool destroyed)
    {
        this->destroyed = destroyed;
    }
    int get_weakness()
    {
        return this->weakness;
    }
    void set_weakness(int weakness)
    {
        this->weakness = weakness;
    }
    std::string get_info()
    {
        return this->info;
    }
    void set_info(std::string info)
    {
        this->info = info;
    }
    bool operator==(const Item &other) const
    {
        // Compare relevant fields of Item to determine equality
        return this->cost == other.cost && this->health == other.health && this->weakness == other.weakness;
    }
};

class Person
{
private:
    float money;    // how much money do you have?
    float health;   // how much health do you have?
    int wind_prot;  // how much wind protection do you have?
    int water_prot; // how well can you protect against floods?
    // int level;      // what level are you on?
    std::vector<Item> items;

public:
    Person(float health, float money, int wind_prot, int water_prot)
    {
        this->health = health;
        this->money = money;
        this->wind_prot = wind_prot;
        this->water_prot = water_prot;
    }
    Person()
    {
        this->health = 100;
        this->money = 0;
        this->wind_prot = 0;
        this->water_prot = 0;
    }
    float get_money()
    {
        return this->money;
    }
    void set_money(float money)
    {
        this->money = money;
    }
    void add_money(float money)
    {
        this->money += money;
    }
    void remove_money(float money)
    {
        this->money -= money;
    }
    float get_health()
    {
        return this->health;
    }
    void set_health(float health)
    {
        this->health = health;
    }
    int get_wind_prot()
    {
        return this->wind_prot;
    }
    void set_wind_prot(int wind_prot)
    {
        this->wind_prot = wind_prot;
    }
    int get_water_prot()
    {
        return this->water_prot;
    }
    void set_water_prot(int water_prot)
    {
        this->water_prot = water_prot;
    }
    std::vector<Item> get_items()
    {
        return this->items;
    }
    void set_items(std::vector<Item> items)
    {
        this->items = items;
    }
    // int get_level()
    // {
    //     return this->level;
    // }
    // void set_level(int level)
    // {
    //     this->level = level;
    // }
    void add_item(Item item)
    {
        this->money -= item.get_cost();
        this->items.push_back(item);
    }
    void remove_item(Item item)
    {
        for (int i = 0; i < this->items.size(); i++)
        {
            if (this->items[i] == item)
            {
                this->items.erase(this->items.begin() + i);
                break;
            }
        }
    }
};

class Disaster
{
public:
    Disaster();
    Disaster(float gen_damage, disaster_type type)
    {
        // this->water_damage = water_damage;
        // this->wind_strength = wind_strength;
        // this->earthquake_mag = earthquake_mag;
        this->gen_damage = gen_damage;
        this->type = type;
    }
    // float do_damage(float); // each float is for each of the damages. Returns amt of damage inflicted
    // float get_water_dmg() {
    //     return this->water_damage;
    // }
    // void set_water_dmg(float water_damage) {
    //     this->water_damage = water_damage;
    // }
    // float get_wind_str() {
    //     return this->wind_strength;
    // }
    // void set_wind_str(float wind_strength) {
    //     this->wind_strength = wind_strength;
    // }
    // float get_quake_mag() {
    //     return this->earthquake_mag;
    // }
    // void set_quake_mag(float earthquake_mag) {
    //     this->earthquake_mag = earthquake_mag;
    // }
    float get_gen_dmg()
    {
        return this->gen_damage;
    }
    void set_gen_dmg(float gen_damage)
    {
        this->gen_damage = gen_damage;
    }
    disaster_type get_type()
    {
        return this->type;
    }

private:
    // float water_damage; // if there's a flood happening, how much is it flooding?
    // float wind_strength; // if there's wind, how much damage is inflicted if defenses fail
    // float earthquake_mag; // if the ground is shaking, how much?
    float gen_damage;   // everything does some damage, so this impacts the life of Prot_items
    disaster_type type; // type of disaster
};

class Flood : public Disaster
{
public:
    Flood(float gen_damage, float flood_height)
        : Disaster(gen_damage, disaster_type::FLOOD)
    {
        this->flood_height = flood_height;
    }
    void do_damage(Person &p)
    {
        if (this->flood_height > p.get_water_prot())
        {
            p.set_health(p.get_health() - get_gen_dmg());
        }
        std::vector<Item> items = p.get_items();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].get_weakness() == disaster_type::FLOOD)
            {
                items[i].set_health(items[i].get_health() - get_gen_dmg());
                if (items[i].get_health() <= 0)
                {
                    items[i].set_health(0);
                    items[i].set_destroyed(true);
                    p.remove_item(items[i]);
                    i--;
                }
            }
        }
    }

private:
    float flood_height;
    // bool disease; // if this water has disease, then health drops rapidly
    //  ADD MEDKIT AND DISEASE LATER
};

class Typhoon : public Disaster
{
public:
    Typhoon(int gen_damage, bool flood, float min, float wind_speed)
        : Disaster(gen_damage, disaster_type::TYPHOON)
    {
        this->flood = flood;
        this->min_wind_height = min;
        this->wind_speed = wind_speed;
        f = nullptr;
    }
    bool cause_flood()
    { // if there is an associated flood, then start a flood disaster. returns whether flood successfully started
        if (this->flood)
        {
            // start flood
            f = new Flood(this->get_gen_dmg(), this->get_min_wind_height());
            return true;
        }
        return false;
    }
    void do_damage(Person &p)
    {
        if (flood)
        {
            f->do_damage(p);
        }
        if (this->wind_speed > p.get_wind_prot())
        {
            p.set_health(p.get_health() - get_gen_dmg());
        }
        std::vector<Item> items = p.get_items();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].get_weakness() == disaster_type::TYPHOON)
            {
                items[i].set_health(items[i].get_health() - get_gen_dmg());
                if (items[i].get_health() <= 0)
                {
                    items[i].set_health(0);
                    items[i].set_destroyed(true);
                    p.remove_item(items[i]);
                    i--;
                }
            }
        }
    }
    bool hasFlood() { return flood; };
    void setFlood(bool f) { flood = f; };
    float get_min_wind_height() { return min_wind_height; };
    void set_min_wind_height(float m) { min_wind_height = m; };
    float get_wind_speed() { return wind_speed; };
    void set_wind_speed(float w) { wind_speed = w; };

private:
    bool flood;
    Flood *f;
    float wind_speed;
    float min_wind_height; // what is the minimum height that will cause the hut to fly away?
};

// class VolcanicEruption : public Disaster
// {
// public:
//     VolcanicEruption(float gen_damage, float lava_height)
//         : Disaster(gen_damage, disaster_type::FLOOD)
//     {
//         this->lava_height = lava_height;
//     }
//     // bool cause_quake(); // causes earthquake if there is one, returns if earthquake was caused
//     bool do_damage(float); // float for lava_height, returns whether damage successfully inflicted
// private:
//     float lava_height;
//     // bool earthquake;
// };

class Earthquake : public Disaster {
    private:
        float mag;
        int gen_damage;
        bool flood;
        Flood *f;
    public:
        void do_damage(Person& p);
        Earthquake(int gen_damage, bool flood, float mag) : Disaster(gen_damage, disaster_type::EARTHQUAKE) {
            this->mag = mag;
            this->gen_damage = gen_damage;
            this->flood = flood;
            f = nullptr;
        }
        bool cause_flood() {
            if (this->flood) {
                f = new Flood(this->gen_damage, this->mag);
                return true;
            }
            return false;
        }
        float get_mag() {
            return this->mag;
        }
        void set_mag(float mag) {
            this->mag = mag;
        }
        int get_gen_damage() {
            return this->gen_damage;
        }
        void set_gen_damage(int gen_damage) {
            this->gen_damage = gen_damage;
        }
        bool hasFlood() {
            return flood;
        }
        void setFlood(bool f) {
            flood = f;
        }
};

#endif