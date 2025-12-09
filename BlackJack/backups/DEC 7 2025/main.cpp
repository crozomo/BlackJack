#include "header.hpp"


int main() {
system("cls");

// ACTOR CLASSES
HandManager dealer;
HandManager player;

// MENU INPUTS
int select {}; // menu select
int bet {}; // set bet size
char confirmBetChoice{}; // confirm bet size
char loopChoice {}; // used for exiting program

bool keepGoing = true; // loops through entire program

// USER
int money {200}; // player starting funds

// GAME INPUTS
int playerHSD {}; // hit/stand/double

// GUI ELEMENTS 
/*
int colOne = 60; // set spaces for column one
int colTwo = 50; // set spaces for column two
int colThree = 40; // set spaces for column three
*/

// RANDOM MACHINE
std::random_device rd;
std::mt19937 rng(rd());

// ACTOR BOOL ACTIONS
bool playerActions = (player.getHandScore() < 21); // true when phs < 21
bool dealerActions = (dealer.getHandScore() < 21 || dealer.getHandScore() >= 17); // true when dhs < 21 or >= 17
bool gameLoop = (bet > 0 || player.getHandScore() <= 21 || dealer.getHandScore() <= 21);


while (keepGoing) {

// Main Menu
std::cout << "+-----+ BLACKJACK +-----+  \n\n";

// Deck Debug
/*
std::cout << "----- DEBUG -----" << "\n";
std::cout << "| Card 0: " << playingCards[0].second << "\n"; // prints card
std::cout << "| Deck Size: " << playingCards.size() << "\n"; // Should print 52
std::cout << "-----------------" << "\n\n";
*/

std::cout << "MONEY: " << money << "\n\n";

std::cout << "1. START" << "\n\n";
std::cout << "2. RESET CHIPS (200)" << "\n\n";
std::cout << "3. EXIT" << "\n\n";
std::cout << "SELECT: ";
std::cin >> select;

    // if user inputs char
    if (std::cin.fail()) { 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid Input, Please Enter a Number\n";
        std::cout << "Press 'Enter' to Try Again\n";
        std::cin.get();
        continue;
        }

// START / GAME BLOCK
if (select == 1) {
    system("cls");

// Betting Screen
do {
    system("cls");
    std::cout << "+-----+ PLACE YOUR BET +-----+\n\n";
    std::cout << "MONEY: " << money << "\n\n";
    std::cout << "SET BET SIZE: \n";
    std::cin >> bet;

        if (bet > money) {
        system("cls");
        std::cout << "Error: Insufficient Funds!" << "\n\n";
        }

        else {
        std::cout << "Confirm Bet? (y/n)" << "\n";
        std::cin >> confirmBetChoice;
        }
} 
while (bet <= 0 || bet > money || confirmBetChoice == 'n');

// Bet Confirmed
// maybe have bet deduction happen only after player bust
money = money - bet;

system ("cls");
dealer.clearHand();
player.clearHand();

// GAME START
/**/
bool playerTurn = true;
Cards newCard = drawRandomCard(playingCards, rng);

while (playerTurn) {
    
}
do {
system ("cls");
std::cout << "Dealer Must Draw to 17" << "\n\n";
std::cout << "DEALER'S HAND:" << "\n";
// DH (Shows 1 Card First) 

// Dealer takes 1 random card, removes card from deck, displays card and value
dealer.addCard(newCard);
dealer.printHand();
std::cout << " " << "\n\n";
std::cout << "Dealer Showing: ";
std::cout << dealer.getHandScore();
std::cout << "\n\n";


std::cout << "YOUR HAND:" << "\n";
// Takes 2 cards from the deck
// CURRENTLY KEEPS ADDING CARDS TO PLAYER WHEN LOOPING (EVEN WHEN DECK = 0)
// Bug: because of the while loop, it unintentionally adds another card to the hand
// use if while loop?
Cards newCard = drawRandomCard(playingCards, rng);
//Cards newCard2 = drawRandomCard(playingCards, rng);
player.addCard(newCard);
//player.addCard(newCard2);
player.printHand();
std::cout << " " << "\n\n";
std::cout << "Player Showing: ";
std::cout << player.getHandScore();
std::cout << "\n\n";


// debug current deck and player hand size - shows cards have been removed from deck
/**/
std::cout << "----- DEBUG -----"<< "\n";
std::cout << "cards in hand: "; 
player.printHandSize();
std::cout << "deck size: " << playingCards.size() << "\n";
std::cout << "-----------------" << "\n\n";


// Show Bet Size
std::cout << "Bet Size: " << bet << "\n\n";

// Player Actions
std::cout << "MONEY: " << money << "\n";
std::cout << R"(
1. HIT

2. STAND

3. DOUBLE
)"
<< "\n";

// Hit, Stand, Double
std::cout << "SELECT: ";
std::cin >> playerHSD;

// HIT
// Give option to hit until stand/blackjack/bust
if (playerHSD == 1) {
    while (playerActions = true) {
    Cards newCard3 = drawRandomCard(playingCards, rng);
    player.addCard(newCard3);
    break;
    std::cin >> playerHSD;
    playerActions = true;

        if (playerActions = false) {
        std::cout << "BUST" << "\n\n";
        break;
        }
    }
     
} // Hit Block
    
// STAND
// Player does not draw a new card. Moves onto Dealers actions
if (playerHSD == 2) {
    playerActions = false;
    //Cards dh2 = drawRandomCard(playingCards, rng);
    //dealerHand.push_back(dh2);
    //dealerHandSize = dh1.first + dh2.first;
    //std::cout << dh2.second << "\n";
    //std::cout << dealerHandSize << "\n";
} // Stand Block

// DOUBLE 
// doubles bet, player takes one card then stands
if (playerHSD == 3) {
    money = money - bet;

    Cards c = drawRandomCard(playingCards, rng);
   // playerHand.push_back(c);
    std::cout << c.second << "\n";
    playerActions = false;
    /*
    if (player.getHandScore() > dealerHandSize) {
        money = money + (bet * 4);
    }
        */
} // Double Block


// Dealer "reveals" (takes another) card
// Dealer adds cards until >= 17, == 21 or < 21
Cards dh2 = drawRandomCard(playingCards, rng);
//dealerHand.push_back(dh2);

} // Game Block
while (gameLoop);


// Player BUST
if (player.getHandScore() > 21) {
    bet = 0;
    std::cout << "BUST" << "\n\n";
}

// Dealer Bust 
/*
if (dealerHandSize > 21) {
    money = money + (bet * 2);
    std::cout << "Dealer Bust!" << "\n\n";
}
*/

// Player BlackJack
if (player.getHandScore() == 21) {
    money = money + (bet * 3);
    std::cout << "Black Jack!" << "\n\n";
}

// Dealer BlackJack
if (dealer.getHandScore() == 21) {
    bet = 0;
    std::cout << "Dealer Black Jack!" << "\n\n";
}

// Player > Dealer
if (dealer.getHandScore() >=17 && player.getHandScore() > dealer.getHandScore()) {
    money = money + (bet * 3);
    std::cout << "Player Wins!" << "\n\n";
}


} // Game Block


// RESET CHIPS 
if (select == 2) {
    system("cls");

        if (money <= 0) {
            money = 200;
            std::cout << "FUNDS RESET TO " << money << "\n\n";
        }

        else {
            std::cout << "YOU ARE NOT BANKRUPT... YET" << "\n\n";
        }

} // Reset Chips Block


// EXIT
if (select == 3) {
    system("cls");
    keepGoing = false;

    std::cout << "SEE YOU AGAIN SOON" << std::endl;

        for (int t = 3; t >= 0; t--){
            std::cout << t << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    break; // breaks loop exits exe
} // Exit Block

} // keep going block

    return 0;
} // main block