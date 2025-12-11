#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <limits>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>

#ifndef HEADER_HPP
#define HEADER_HPP

// std::pair allows the vector to contain both int and string data types
using Cards = std::pair<int, std::string>;

extern std::vector<Cards> playingCards;
extern std::vector<Cards> generateDeck;

Cards drawRandomCard(std::vector<Cards>& playingCards, std::mt19937& gen);

// card manager for player and dealer
class HandManager {
    private:
    std::vector<Cards> handDisplay {}; 

    public:
    void addCard (Cards newCard) {
        handDisplay.push_back(newCard);
    }

    // displays card string in hand
    void printHand () { 
        for (int i = 0; i < handDisplay.size(); i++) {
            std::cout << handDisplay[i].second << "  ";
        }
    }

    // clears cards from hand
    void clearHand () {
        handDisplay.clear();
    }

    // used in debug to show how many cards in hand
    void printHandSize() {
        std::cout << handDisplay.size() << "\n";
    }

    // displays total value of cards in hand
    int getHandScore () {
        int vTotal {0};
        for (int i = 0; i < handDisplay.size(); i++) {
            vTotal = vTotal + handDisplay[i].first;
        }
        return vTotal;
    }

};


#endif