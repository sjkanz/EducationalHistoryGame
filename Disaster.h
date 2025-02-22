#ifndef disaster
#define disaster

enum class disaster_type {
    TYPHOON,
    FLOOD
    // Volcanic_eruption,
    // Earthquake
};

class Disaster {
    public:
        Disaster();
        Disaster(float water_damage, float wind_strength, float earthquake_mag, float gen_damage, disaster_type type) {
            this->water_damage = water_damage;
            this->wind_strength = wind_strength;
            this->earthquake_mag = earthquake_mag;
            this->gen_damage = gen_damage;
            this->type = type;
        }
        float do_damage(float, float, float, float); // each float is for each of the damages. Returns amt of damage inflicted
        float get_water_dmg() {
            return this->water_damage;
        }
        void set_water_dmg(float water_damage) {
            this->water_damage = water_damage;
        }
        float get_wind_str() {
            return this->wind_strength;
        }
        void set_wind_str(float wind_strength) {
            this->wind_strength = wind_strength;
        }
        float get_quake_mag() {
            return this->earthquake_mag;
        }
        void set_quake_mag(float earthquake_mag) {
            this->earthquake_mag = earthquake_mag;
        }
        float get_gen_dmg() {
            return this->gen_damage;
        }
        void set_gen_dmg(float gen_damage) {
            this->gen_damage = gen_damage;
        }
        disaster_type get_type() {
            return this->type;
        }
    private:
        float water_damage; // if there's a flood happening, how much is it flooding?
        float wind_strength; // if there's wind, how much damage is inflicted if defenses fail
        float earthquake_mag; // if the ground is shaking, how much?
        float gen_damage; // everything does some damage, so this impacts the life of Prot_items
        disaster_type type; // type of disaster
};

class Flood : public Disaster {
    public:
        Flood(float water_damage, float wind_strength, float earthquake_mag, float gen_damage, float flood_height)
            : Disaster(water_damage, wind_strength, earthquake_mag, gen_damage, disaster_type::FLOOD) {
                this->flood_height = flood_height;
            }
        bool do_damage(float); // float for flood_height, returns whether damage successfully inflicted
    private:
        float flood_height;
        //bool disease; // if this water has disease, then health drops rapidly
        // ADD MEDKIT AND DISEASE LATER

};

class Typhoon : public Disaster {
    public:
        Typhoon(float water_damage, float wind_strength, float earthquake_mag, float gen_damage, bool flood, float min)
        : Disaster(water_damage, wind_strength, earthquake_mag, gen_damage, disaster_type::TYPHOON) {
            this->flood = flood;
            this->min_wind_height = min;
            f = nullptr;
        }
        bool cause_flood() { // if there is an associated flood, then start a flood disaster. returns whether flood successfully started
            if (this->flood) {
                // start flood
                f = new Flood(this->get_water_dmg(), this->get_wind_str(), this->get_quake_mag(), this->get_gen_dmg(), this->get_min_wind_height());
                return true;
            }
            return false;
        } 
        bool do_damage(float); // only float for min_wind_height, returns whether damage was successfully inflicted
        bool hasFlood();
        float get_min_wind_height();
        void set_min_wind_height(float);
    private:
        bool flood;
        Flood* f;
        float min_wind_height; // what is the minimum height that will cause the hut to fly away?
};

class VolcanicEruption : public Disaster {
    public:
        VolcanicEruption(float wind_strength, float earthquake_mag, float gen_damage, float lava_height)
            : Disaster(0, wind_strength, earthquake_mag, gen_damage, disaster_type::FLOOD) {
                this->lava_height = lava_height;
        }
        // bool cause_quake(); // causes earthquake if there is one, returns if earthquake was caused
        bool do_damage(float); // float for lava_height, returns whether damage successfully inflicted
    private:
        float lava_height;
        // bool earthquake;
};

// class Earthquake : public Disaster {
//     public:
//         bool do_damage(float);
// };

#endif