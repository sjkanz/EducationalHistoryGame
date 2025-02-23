#include "Disaster.h"
#include "Fishing.h"
// #include "Person.h"
#include "Prot_items.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

// variables
// bool timer_expired = false;
// const int numThreads = 10;
// std::thread threads[numThreads];
std::random_device rd;
std::mt19937 gen(rd());

// function prototypes
LPCWSTR ConvertToLPCWSTR(const char *);
int go_fish(int);
bool valid_purchase(int, Person &);
void crisis(Person &);
int print_menu(Person &);
int shop();
bool hazard(Person &);

// void timer()
// {
//     timer_expired = false;
//     std::uniform_int_distribution<> distrib(60, 90);
//     std::this_thread::sleep_for(std::chrono::seconds(distrib(gen)));
//     timer_expired = true;
// }

int Stilts::total_stilts = 0;

int main()
{
    // walkthrough
    // 1. catch fish
    Person p(100, 0, 0, 0, 0);
    std::cout << "Welcome to the game! You have 100 health and 0 money." << std::endl;
    std::cout << "To get money, you can fish! Let's try that now." << std::endl;
    std::cout << "Do you wish to go fishing? (y/n)" << std::endl;
    char fish;
    std::cin >> fish;
    if (fish == 'n')
    {
        std::cout << "You decided not to fish. You still have 0 money." << std::endl;
        std::cout << "To play this game, you have to fish, so for now, you're fishing anyway." << std::endl;
    }
    else if (fish == 'y')
    {
        std::cout << "Yay, let's fish!" << std::endl;
    }
    else
    {
        std::cout << "That's not one of the options." << std::endl;
        std::cout << "To play this game, you have to fish, so for now, you're fishing anyway." << std::endl;
    }
    Fish f(3); // fish costs 3 shells
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    p.add_money(f.get_cost());
    std::cout << "You caught a fish! You now have " << p.get_money() << " shells." << std::endl;
    // p.set_level(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // std::cout << "You have reached level 1!" << std::endl;
    std::cout << "Look! You unlocked something." << std::endl;
    MessageBoxW(NULL, ConvertToLPCWSTR("New Item in Shop: Stilts!"), ConvertToLPCWSTR("New Item Unlocked"), MB_OK | MB_ICONINFORMATION);
    std::cout << "You can now buy stilts! You can now buy stilts to raise your house up by one." << std::endl;
    std::cout << "Stilts help protect against floods. They cost 3 shells." << std::endl;
    std::cout << "Would you like to buy some? (y/n)" << std::endl;
    char input = ' ';
    std::cin >> input;
    if (input == 'n')
    {
        std::cout << "Too bad, this is the tutorial. You have to buy stilts." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    p.add_item(Stilts(p));
    std::cout << "You now have stilts! You raised your house up by one." << std::endl;
    std::cout << "Stilts help protect against floods. They cost 3 shells." << std::endl;
    std::cout << "Go ahead and experiment a little!" << std::endl;
    int choice = print_menu(p);
    while (choice != 3)
    {
        while (choice != 1 && choice != 2 && choice != 3)
        {
            std::cout << "That's not one of the options. Please try again." << std::endl;
            choice = print_menu(p);
        }
        if (choice == 1)
        {
            p.add_money(go_fish(3));
        }
        else if (choice == 2)
        {
            int decision = shop();
            while (decision != 1 && decision != 2)
            {
                std::cout << "That's not one of the options. Please try again." << std::endl;
                decision = shop();
            }
            if (decision == 1 && valid_purchase(3, p))
            {
                Stilts temp(p);
                p.add_item(temp);
                std::cout << "You bought stilts! You raised your house up by one." << std::endl;
            }
            else if (decision == 1 && !valid_purchase(3, p))
            {
                std::cout << "You don't have enough money to buy stilts. You still have " << p.get_money() << " shells." << std::endl;
            }
            else if (decision == 2)
            {
                Stilts temp(p);
                std::cout << temp.get_info() << std::endl;
            }
            else
            {
                std::cout << "You decided not to buy stilts. You still have " << p.get_money() << " shells." << std::endl;
            }
        }
        else
        {
            std::cout << "ERR" << std::endl;
        }

        std::cout << "Are you ready for the flood? y/n" << std::endl;
        char ready;
        std::cin >> ready;
        if (ready == 'n')
        {
            std::cout << "No worries! You have more time!" << std::endl;
            choice = print_menu(p);
        }
        else if (ready == 'y')
        {
            choice = 3;
        }
    }
    std::cout << "You have decided to face the flood. Let's see what happens." << std::endl;
    std::cout << "Here comes the flood!" << std::endl;
    Flood flood(5, p.get_water_prot() - 1);
    std::cout << "You survived the flood! You still have " << p.get_health() << " health." << std::endl;
    std::cout << "That's the basis of the game! As you progress, you will unlock more items and face disasters." << std::endl;
    std::cout << "Different disasters will require different items to protect against." << std::endl;
    std::cout << "Good luck!" << std::endl;
    // end of Walkthrough

    // starting the timer in a separate thread
    // int index = 0;
    // threads[index] = std::thread(timer);
    // index++;
    // main game loop
    choice = print_menu(p);
    int turns = 0;
    std::uniform_int_distribution<> distrib(3, 10);
    int next_hazard = distrib(gen);
    while (choice != 3 && p.get_health() > 0)
    {
        // std::cout<<"timer: "<<timer_expired<<std::endl;
        while (!(choice >= 1 && choice <= 6))
        {
            std::cout << "That's not one of the options. Please try again." << std::endl;
            choice = print_menu(p);
        }
        if (choice == 1)
        {
            std::uniform_int_distribution<> fish1(1, 2);
            std::uniform_int_distribution<> fish2(1, 5);
            if (fish1(gen) == fish2(gen))
            {
                std::cout << "You caught a fish!" << std::endl;
                p.add_money(go_fish(15));
                std::cout << "Wow! You got lucky!" << std::endl;
                std::cout << "You now have " << p.get_money() << " shells." << std::endl;
            }
            else if (fish2(gen) > 2)
            {
                std::cout << "You caught a fish!" << std::endl;
                p.add_money(go_fish(fish2(gen)));
                std::cout << "You now have " << p.get_money() << " shells." << std::endl;
            }
            else
            {
                std::cout << "Oh no! Your fishing line broke!" << std::endl;
                std::cout << "Spending money to repair it..." << std::endl;
                p.remove_money(2);
                std::cout << "You didn't catch a fish." << std::endl;
                std::cout << "You now have " << p.get_money() << " shells." << std::endl;
            }
        }
        else if (choice == 2)
        {
            choice = shop();
            while (!(choice >= 1 && choice <= 4))
            {
                std::cout << "That's not one of the options. Please try again." << std::endl;
                choice = shop();
            }
            if (choice == 1 && valid_purchase(3, p))
            {
                Stilts temp(p);
                p.add_item(temp);
                std::cout << "You bought stilts! You raised your house up by one." << std::endl;
            }
            else if (choice == 1 && !valid_purchase(3, p))
            {
                std::cout << "You don't have enough money to buy stilts. You still have " << p.get_money() << " shells." << std::endl;
            }
            else if (choice == 2 && valid_purchase(5, p))
            {
                StormShutters temp(p);
                p.add_item(temp);
                p.set_wind_prot(p.get_wind_prot() + 1);
                std::cout << "You bought storm shutters! You now have " << p.get_wind_prot() << " wind protection." << std::endl;
            }
            else if (choice == 2 && !valid_purchase(5, p))
            {
                std::cout << "You don't have enough money to buy storm shutters. You still have " << p.get_money() << " shells." << std::endl;
            }
            else if (choice == 3 && valid_purchase(6, p))
            {
                Foundation temp(p);
                p.add_item(temp);
                p.set_quake_prot(p.get_quake_prot() + 1);
                std::cout << "You bought foundation bolting! You now have " << p.get_quake_prot() << " earthquake protection." << std::endl;
            }
            else if (choice == 3 && !valid_purchase(6, p))
            {
                std::cout << "You don't have enough money to buy foundation bolting. You still have " << p.get_money() << " shells." << std::endl;
            }
            else if (choice == 4)
            {
                std::cout << "Here's some more information about the items." << std::endl;
                Stilts temp(p);
                std::cout << temp.get_info() << std::endl;
                StormShutters temp2(p);
                std::cout << temp2.get_info() << std::endl;
                Foundation temp3(p);
                std::cout << temp3.get_info() << std::endl;
            }
            else
            {
                std::cout << "Come back later! You have " << p.get_money() << " shells." << std::endl;
            }
        }
        if (turns == next_hazard)
        {
            crisis(p);
            next_hazard += distrib(gen);
        }
        turns++;
        choice = print_menu(p);
    }
    if (p.get_health() <= 0)
    {
        std::cout << "You have died." << std::endl;
    }
    else if (p.get_money() < 0) {
        std::cout << "You have gone bankrupt." << std::endl;
    }
    else
    {
        std::cout << "You have decided to exit the game." << std::endl;
    }
    std::cout << "Thank you for playing!" << std::endl;
    return 0;
}

void crisis(Person &p)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> hazard_picker(1, 3);
    int hazard = hazard_picker(gen);
    std::uniform_int_distribution<> tf(1, 2);
    std::uniform_int_distribution<> distrib2(1, 10);
    if (hazard == 1)
    {
        std::cout << "A flood is coming!" << std::endl;
        Flood flood(distrib2(gen), distrib2(gen));
        flood.do_damage(p);
    }
    else if (hazard == 2)
    {
        std::cout << "Oh no! It's a typhoon!" << std::endl;
        bool flood = false;
        if (tf(gen) == 1)
        {
            std::cout << "The typhoon is causing a flood!" << std::endl;
            flood = true;
        }
        std::uniform_real_distribution<> windspeed(55, 190);
        Typhoon typhoon(distrib2(gen), flood, distrib2(gen), windspeed(gen));
        typhoon.do_damage(p);
    }
    else if (hazard == 3)
    {
        std::cout << "Hold on! There's an earthquake!" << std::endl;
        bool flood = false;
        if (tf(gen) == 1)
        {
            std::cout << "The earthquake is causing a flood!" << std::endl;
            flood = true;
        }
        std::uniform_real_distribution<> mag(1.0, 10.0);
        Earthquake earthquake(distrib2(gen), flood, mag(gen));
        earthquake.do_damage(p);
    }
}

int print_menu(Person &p)
{
    std::cout << "Current Stats:" << std::endl;
    std::cout << "Health: " << (p).get_health() << std::endl;
    std::cout << "Money: " << (p).get_money() << "\n"
              << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Go fishing" << std::endl;
    std::cout << "2. Open Shop" << std::endl;
    std::cout << "3. Exit" << std::endl;
    int input = -1;
    std::cin >> input;
    return input;
}

bool valid_purchase(int cost, Person &p)
{
    if ((p).get_money() >= cost)
    {
        return true;
    }
    return false;
}

int shop(bool first) {
    std::cout << "Welcome to the shop!" << std::endl;
    std::cout << "What would you like to buy?" << std::endl;
    std::cout << "1. Stilts - 3 shells" << std::endl;
    std::cout << "2. More info" << std::endl;
    std::cout << "3. Exit" << std::endl;
    int input = -1;
    std::cin >> input;
    return input;
}

int shop()
{
    std::cout << "Welcome to the shop!" << std::endl;
    std::cout << "What would you like to buy?" << std::endl;
    std::cout << "1. Stilts - 3 shells" << std::endl;
    std::cout << "2. Storm Shutters - 5 shells" << std::endl;
    std::cout << "3. Foundation Bolting - 6 shells" << std::endl;
    std::cout << "4. More info" << std::endl;
    // std::cout << "5. Med Kits - 15 shells" << std::endl;
    std::cout << "5. Exit" << std::endl;
    int input = -1;
    std::cin >> input;
    return input;
}

int go_fish(int cost)
{
    Fish f(cost);
    return f.get_cost();
}

LPCWSTR ConvertToLPCWSTR(const char *charString)
{
    size_t length = strlen(charString) + 1;
    wchar_t *wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, charString, -1, wideString, length);
    return wideString;
}