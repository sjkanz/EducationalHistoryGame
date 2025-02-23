#ifndef prot_items
#define prot_items

#include "Disaster.h"
// #include "Person.h"

class Stilts : public Item
{
private:
    float height;
    bool support;

public:
    static int total_stilts;
    const int max_stilts = 5; // if >= 5 stilts, there's less resistance to wind
    Stilts(Person &p) : Item(3.0, 10, FLOOD, "Stilts are a great way to protect against floods."
         " They raise the structure above potential flood levels, protecting the structure from water" 
         " damage and debris in the water. This also improves ventilation under the building, reducing"
         " potential moisture buildup later. Some places in modern day that utilize stilts: Vietnam, Bangladesh,"
         " the Maldives, the United States and the United Kingdom.")
    {
        this->height = 1;
        this->support = false;
        total_stilts++;
        if (total_stilts >= max_stilts)
        {
            p.set_wind_prot(p.get_wind_prot() - 1);
        }
        (p).set_water_prot((p).get_water_prot() + 1);
    }
    float get_height()
    {
        return this->height;
    }
    void set_height(float height)
    {
        this->height = height;
    }
    bool get_support()
    {
        return this->support;
    }
    void set_support(bool support)
    {
        this->support = support;
    }
    void minus_health(float health)
    {
        this->set_health(this->get_health() - health);
    }
    void add_support()
    {
        this->set_health(this->get_health() + 10);
        this->set_support(true);
    }
    void repair()
    {
        if (this->get_support())
        {
            this->set_health(20);
        }
        else
        {
            this->set_health(10);
        }
    }
};

class StormShutters : public Item
{
private:
    bool support;

public:
    StormShutters(Person &p) : Item(5, 10, TYPHOON, "Storm shutters are used to protect against typhoons."
         " They protect windows from flying debris and high winds, reducing the risk of damage to the structure"
         " and the people inside. Some places in modern day that utilize storm shutters: Japan, the Philippines,"
         " the United States, and the Caribbean.")
    {
        this->support = false;
        p.set_wind_prot(p.get_wind_prot() + 1);
    }
    bool get_support()
    {
        return this->support;
    }
    void set_support(bool support)
    {
        this->support = support;
    }
    void minus_health(float health)
    {
        this->set_health(this->get_health() - health);
    }
    void add_support()
    {
        this->set_health(this->get_health() + 10);
        this->set_support(true);
    }
    void repair()
    {
        if (this->get_support())
        {
            this->set_health(20);
        }
        else
        {
            this->set_health(10);
        }
    }
};

class Foundation : public Item {
    private:
        float depth;
        bool support;
    public:
        Foundation(Person &p): Item (5.0, 20, EARTHQUAKE, "Foundation bolting, or seismic retrofitting, "
            "is a technique used to enhance the earthquake resistance of a building by securely anchoring "
            "the structure to its foundation. This involves installing anchor bolts that attach the building's"
            " wooden frame to a concrete foundation, thus preventing the building from sliding or shifting off "
            "the foundation during seismic activity. Some places in modern day that utilize foundation bolting: "
            "California, Japan, New Zealand, and Turkey.") {
                this->depth = 1;
                this->support = false;
                (p).set_water_prot((p).get_water_prot() + 2);
            }
        float get_depth() {
            return this->depth;
        }
        void set_depth(float depth) {
            this->depth = depth;
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
            this->set_health(this->get_health() + 20);
            this->set_support(true);
        }
        void repair() {
            if(this->get_support()) {
                this->set_health(40);
            }
            else {
                this->set_health(20);
            }
        }
};

#endif