#include "header.hpp"

// Draw Random Card
Cards drawRandomCard(std::vector<Cards>& playingCards, std::mt19937& gen) {
    if (playingCards.empty()) {
        return {0, "none"};
    }

    // pick random card from playingcards, starting from index 0 to index n-1  
    std::uniform_int_distribution<int> dist(0, playingCards.size() -1);
    int randomIndex = dist(gen);

    // save card to return to later. grab card located at position randomindex 
    Cards selected = playingCards [randomIndex];

    // swap with last element
    std::swap(playingCards[randomIndex], playingCards.back());

    // remove last element
    playingCards.pop_back();

    return selected;
}