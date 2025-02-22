
#include "Disaster.h"
#include "Fishing.h"
#include "Person.h"
#include "Prot_items.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

LPCWSTR ConvertToLPCWSTR(const char*);
int go_fish();
int print_menu();
int shop();
int go_flood();


void timer(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::cout << "Timer expired!" << std::endl;
}

int Stilts::total_stilts = 0;

int main() {
    // walkthrough
    // 1. catch fish
    Person p(100, 0, 0, 0, std::vector<Item*>());
    std::cout<<"Welcome to the game! You have 100 health and 0 money."<<std::endl;
    std::cout<<"To get money, you can fish! Let's try that now."<<std::endl;
    std::cout<<"Do you wish to go fishing? (y/n)"<<std::endl;
    char fish;
    std::cin >> fish;
    if (fish == 'n') {
        std::cout<<"You decided not to fish. You still have 0 money."<<std::endl;
        std::cout<<"To play this game, you have to fish, so for now, you're fishing anyway."<<std::endl;
    } else if (fish == 'y') {
        std::cout<<"Yay, let's fish!"<<std::endl;
    }
    else {
        std::cout<<"That's not one of the options."<<std::endl;
        std::cout<<"To play this game, you have to fish, so for now, you're fishing anyway."<<std::endl;
    }
    Fish f(3); // fish costs 3 shells
    p.add_money(f.get_cost());
    std::cout<<"You caught a fish! You now have "<<p.get_money()<<" shells."<<std::endl;
    std::cout<<"Look! You unlocked something."<<std::endl;
    MessageBoxW(NULL, ConvertToLPCWSTR("New Item in Shop: Stilts!"), ConvertToLPCWSTR("New Item Unlocked"), MB_OK | MB_ICONINFORMATION);
    p.add_item(Stilts());
    p.remove_money(3);
    std::cout<<"You now have stilts! You raised your house up by one."<<std::endl;
    std::cout<<"Stilts help protect against floods. They cost 3 shells."<<std::endl;
    std::cout<<"Go ahead and buy another!"<<std::endl;
    int choice = print_menu(p);
    while (choice != 3) {
        while (!(choice == 1 || choice == 2)) {
            std::cout<<"That's not one of the options. Please try again."<<std::endl;
            choice = print_menu();
        }
        if (choice == 1) {
            go_fish(3);
        }
        else if (choice == 2) {
            int choice = shop();
            while (!(choice == 1 || choice == 2)) {
                std::cout<<"That's not one of the options. Please try again."<<std::endl;
                choice = shop();
            }
            if(choice == 1 && valid_purchase(3, p)) {
                p.add_item(Stilts());
                p.remove_money(3);
                std::cout<<"You bought stilts! You raised your house up by one."<<std::endl;
            }
            else if (choice == 1 && !valid_purchase(3, p)) {
                std::cout<<"You don't have enough money to buy stilts. You still have "<<p.get_money()<<" shells."<<std::endl;
            }
            else if (choice == 2) {
                std::cout<<"You decided not to buy stilts. You still have "<<p.get_money()<<" shells."<<std::endl;
            }
        }
        std::cout<<"Are you ready for the flood? y/n"<<std::endl;
        char ready;
        std::cin >> ready;
        if (ready == 'n') {
            std::cout<<"No worries! You have more time!"<<std::endl;
            choice = print_menu(p);
        }
        else if (ready == 'y') {
            choice = 3;
        }
    }
    std::cout<<"You have decided to face the flood. Let's see what happens."<<std::endl;
    std::cout<<"Here comes the flood!"<<std::endl;

    return 0;
}


int print_menu(Person p) {
    std::cout<<"Current Stats:"<<std::endl;
    std::cout<<"Health: "<<p.get_health()<<std::endl;
    std::cout<<"Money: "<<p.get_money()<<"\n"<<std::endl;
    std::cout<<"What would you like to do?"<<std::endl;
    std::cout<<"1. Go fishing"<<std::endl;
    std::cout<<"2. Open Shop"<<std::endl;
    return std::cin.get();
}

bool valid_purchase(int cost, Person p) {
    if (p.get_money() >= cost) {
        return true;
    }
    return false;
}

int shop() {
    std::cout<<"Welcome to the shop!"<<std::endl;
    std::cout<<"What would you like to buy?"<<std::endl;
    std::cout<<"1. Stilts"<<std::endl;
    std::cout<<"2. Exit"<<std::endl;
    return std::cin.get();
}

int go_fish(int cost) {
    std::cout<<"Do you wish to go fishing? (y/n)"<<std::endl;
    char fish;
    std::cin >> fish;
    if (fish == 'n') {
        std::cout<<"You decided not to fish. You still have 0 money."<<std::endl;
        return 0;
    } else if (fish == 'y') {
        std::cout<<"Yay, let's fish!"<<std::endl;
    }
    else {
        std::cout<<"That's not one of the options. Sending you back to home"<<std::endl;
        return 0;
    }
    Fish f(cost); // fish costs 3 shells
    return f.get_cost();
}

LPCWSTR ConvertToLPCWSTR(const char* charString) {
    size_t length = strlen(charString) + 1;
    wchar_t* wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, charString, -1, wideString, length);
    return wideString;
}