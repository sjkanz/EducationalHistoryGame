#ifndef DISASTER.H
#define DISASTER.H

enum class disaster_type {
    Typhoon,
    Flood,
    Volcanic_eruption,
    Earthquake
};

class Disaster {
    public:
        float water_damage; // if there's a flood happening, how much is it flooding?
        float wind_strength; // if there's wind, how much damage is inflicted if defenses fail
        float earthquake_mag; // if the ground is shaking, how much?
        float general_damage; // everything does some damage, so this impacts the life of Prot_items
        disaster_type type; // type of disaster
        float do_damage(float, float, float, float); // each float is for each of the damages. Returns amt of damage inflicted
};

class Typhoon : public Disaster {
    public:
        bool flood;
        float min_wind_height; // what is the minimum height that will cause the hut to fly away?
        bool cause_flood(); // if there is an associated flood, then start a flood disaster. returns whether flood successfully started
        bool do_damage(float); // only float for min_wind_height, returns whether damage was successfully inflicted
};

class Flood : public Disaster {
    public:
        float flood_height;
        //bool disease; // if this water has disease, then health drops rapidly
        // ADD MEDKIT AND DISEASE LATER
        bool do_damage(float); // float for flood_height, returns whether damage successfully inflicted

};

class VolcanicEruption : public Disaster {
    public:
        float lava_height;
        bool earthquake;
        bool cause_quake(); // causes earthquake if there is one, returns if earthquake was caused
        bool do_damage(float); // float for lava_height, returns whether damage successfully inflicted
};

#endif