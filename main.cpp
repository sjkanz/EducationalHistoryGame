
#include "Disaster.h"
#include "Prot_items.h"
#include "Fishing.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

LPCWSTR ConvertToLPCWSTR(const char*);

int main() {
    // to make these pass by reference, just make sure to add & in front
    int wind_prot = 0; // how much wind protection do you have
    int water_prot = 0; // how well can you protect against floods?
    int health = 100; // how much health do you have?
    int money = 0;
    std::vector<Item> items; // what items do you have?

    // walkthrough
    // 1. catch fish
    std::cout<<"Welcome to the game! You have 100 health and 0 money."<<std::endl;
    std::cout<<"To get money, you can fish! Let's try that now."<<std::endl;
    std::cout<<"Do you wish to go fishing? (y/n)"<<std::endl;
    char fish;
    std::cin >> fish;
    if (fish == 'n') {
        std::cout<<"You decided not to fish. You still have 0 money."<<std::endl;
        std::cout<<"To play this game, you have to fish, so for now, you're fishing anyway."<<std::endl;
    } else {
        std::cout<<"That's not one of the options."<<std::endl;
        std::cout<<"To play this game, you have to fish, so for now, you're fishing anyway."<<std::endl;
    }
    Fish f(3); // fish costs 3 shells
    money += f.get_cost();
    std::cout<<"You caught a fish! You now have "<<money<<" shells."<<std::endl;
    std::cout<<"Look! You unlocked something."<<std::endl;
    MessageBoxW(NULL, ConvertToLPCWSTR("New Item: Stilts!"), ConvertToLPCWSTR("New Item Unlocked"), MB_OK | MB_ICONINFORMATION);
    items[0] = Stilts::Stilts();
    Stilts::total_stilts++;
    std::cout<<"You now have stilts! You raised your house up by one."<<std::endl;
    

    return 0;
}

LPCWSTR ConvertToLPCWSTR(const char* charString) {
    size_t length = strlen(charString) + 1;
    wchar_t* wideString = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, charString, -1, wideString, length);
    return wideString;
}