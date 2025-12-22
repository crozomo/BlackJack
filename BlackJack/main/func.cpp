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

// Print Game Board
void printGameBoard(HandManager& dealer, HandManager& player, int money, int bet) {
    std::cout << "<<<| DEALER MUST DRAW TO 17 |>>>" << "\n\n";
    std::cout << "DEALER'S HAND:" << "\n";
    dealer.printHand();
    std::cout << " " << "\n\n";
    std::cout << "Dealer Showing: ";
    std::cout << dealer.getHandScore();
    std::cout << "\n\n";

    std::cout << "YOUR HAND:" << "\n";
    player.printHand();
    std::cout << " " << "\n\n";
    std::cout << "Player Showing: ";
    std::cout << player.getHandScore();
    std::cout << "\n\n";

    std::cout << "Bet Size: " << bet << "\n\n";
    std::cout << "MONEY: " << money << "\n";

}