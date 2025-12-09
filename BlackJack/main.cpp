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

// RANDOM MACHINE
std::random_device rd;
std::mt19937 rng(rd());

// ACTOR BOOL ACTIONS
bool playerActions = (player.getHandScore() < 21); // true when phs < 21
bool dealerActions = (dealer.getHandScore() < 21 || dealer.getHandScore() >= 17); // true when dhs < 21 or >= 17
bool gameLoop = (bet > 0 || player.getHandScore() <= 21 || dealer.getHandScore() <= 21);


while (keepGoing) {
system("cls");
// Main Menu
std::cout << R"(
*+===+===+===+===+===+===+*
|        BLACKJACK        |
*+===+===+===+===+===+===+*

)";

std::cout << "MONEY: " << money << "\n";

std::cout << R"(
*+===+===+===+===+===+===+*
|   1. START              |
|                         |
|   2. RESET CHIPS (200)  |
|                         |
|   3. EXIT               |
*+===+===+===+===+===+===+*

SELECT:
)";
std::cin >> select;

// Deck Debug
/*
std::cout << "----- DEBUG -----" << "\n";
std::cout << "| Card 0: " << playingCards[0].second << "\n"; // prints card
std::cout << "| Deck Size: " << playingCards.size() << "\n"; // Should print 52
std::cout << "-----------------" << "\n\n";
*/

// If User enters Char instead of Num
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
    std::cout << R"(
*+===+===+===+===+===+===+*
|      PLACE YOUR BET     |
*+===+===+===+===+===+===+*

)";
    std::cout << "MONEY: " << money << "\n\n";
    std::cout << "SET BET SIZE: \n";
    std::cin >> bet;

// if user inputs char
    if (std::cin.fail()) { 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid Input, Please Enter a Number\n";
        std::cout << "Press 'Enter' to Try Again\n";
        std::cin.get();
        continue;
        }

// If bet size > player money
    if (bet > money) {
        system("cls");
        std::cout << "Error: Insufficient Funds!" << "\n\n";
        }

    else {
        std::cout << "Confirm Bet? (y/n)" << "\n";
        std::cin >> confirmBetChoice;
        }

// EXIT BETTING SCREEN

} 
while (bet <= 0 || bet > money || confirmBetChoice == 'n');

// Bet Confirmed
// maybe have bet deduction happen only after player bust
money = money - bet;

system ("cls");
dealer.clearHand();
player.clearHand();

// Check remaining cards in deck - reset if <= 20 cards
if (playingCards.size() <= 20) {
    std::cout << "SHUFFLING DECK..." << "\n";
                for (int t = 1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
    playingCards = generateDeck;
}

// GAME START
std::cout << "<<<| DEALER MUST DRAW TO 17 |>>>" << "\n\n";

// Dealer takes 1 random card, removes card from deck, displays card and value
std::cout << "DEALER'S HAND:" << "\n";
dealer.addCard(drawRandomCard(playingCards, rng));
dealer.printHand();
std::cout << " " << "\n\n";
std::cout << "Dealer Showing: ";
std::cout << dealer.getHandScore();
std::cout << "\n\n";

// Player takes 2 random cards, removing them from deck, display cards and value
std::cout << "YOUR HAND:" << "\n";
player.addCard(drawRandomCard(playingCards, rng));
player.addCard(drawRandomCard(playingCards, rng));
player.printHand();
std::cout << " " << "\n\n";
std::cout << "Player Showing: ";
std::cout << player.getHandScore();
std::cout << "\n\n";

bool playerTurn = true;
while (playerTurn) {
system ("cls");
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

// Player opens with BlackJack
    if (player.getHandScore() == 21) {
        playerTurn = false;
        money = money + (bet * 3);
        std::cout << "*** <<< Player BlackJack! >>> ***" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
                /*for (int t = 1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }*/
        break; // overwrites dealer actions
    }
  
// DEBUG - SHOWS STATUS OF CARD DECK
/*
std::cout << "----- DEBUG -----"<< "\n";
std::cout << "cards in hand: "; 
player.printHandSize();
std::cout << "deck size: " << playingCards.size() << "\n";
std::cout << "-----------------" << "\n\n";
*/

// Show Bet Size
std::cout << "Bet Size: " << bet << "\n\n";

// Player Actions
std::cout << "MONEY: " << money << "\n";
std::cout << R"(
+------------+
| 1. HIT     |
|            |
| 2. STAND   |
|            |
| 3. DOUBLE  |
+------------+
)"
<< "\n";

// Hit, Stand, Double
std::cout << "SELECT: ";
std::cin >> playerHSD;

// if user inputs char
    if (std::cin.fail()) { 
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid Input, Please Enter a Number\n";
            std::cout << "Press 'Enter' to Try Again\n";
            std::cin.get();
            continue;
        }

// HIT
// Give option to hit until stand/blackjack/bust
    if (playerHSD == 1) {
        player.addCard(drawRandomCard(playingCards, rng));
        player.getHandScore();
        
    }

// STAND
// Player does not draw a new card. Moves onto Dealers actions
    else if (playerHSD == 2) {
        playerTurn = false;
    }


// DOUBLE
// Add only 1 card, doubles bet. moves straight to dealer actions
    else if (playerHSD == 3) {
        system ("cls");
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

        player.addCard(drawRandomCard(playingCards, rng));
        player.getHandScore();
        money = money - bet; // deduct money by bet size again
                for (float t = 0.25; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        playerTurn = false;
        
// DOUBLE WIN CONDITIONS
        /*
        // Player BlackJack
        if (player.getHandScore() == 21) {
        system ("cls");
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

        money = money + (bet * 6);
        std::cout << "Black Jack!" << "\n\n";
                for (int t = 1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

        playerTurn = false;
    }

    // Player > Dealer
    if (dealer.getHandScore() >=17 && player.getHandScore() > dealer.getHandScore()
        && player.getHandScore() <= 21) {
        money = money + (bet * 6);
        std::cout << "Player Wins!" << "\n\n";
                for (int t = 1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
             playerTurn = false;
    }
*/
    } // DOUBLE BLOCK

    
// Player Bust
    if (player.getHandScore() > 21) {
        system ("cls");
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

        std::cout << "<< BUST! >>" << "\n";
        std::cout << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/

        playerTurn = false;
    }

// Player BlackJack
    if (player.getHandScore() == 21) {
        system ("cls");
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

        money = money + (bet * 3);
        std::cout << "*** <<< Black Jack! >>> ***" << "\n\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/

        playerTurn = false;
    }

} // playerTurn loop 

// Dealer Actions
bool dealerTurn = true;

// If Player Busts or Black Jack, skip Dealers Turn
if (player.getHandScore() == 21 || player.getHandScore() > 21) {
    dealerTurn = false;
}

while (dealerTurn) {
    system ("cls");
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

// Dealer soft stands on 17
    if (dealer.getHandScore() >= 17) {
        dealerTurn = false;
        break;
    }
    
    else {
        dealer.addCard(drawRandomCard(playingCards, rng));
                for (float t = 0.25; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
        dealer.getHandScore();
        }

} // Dealer Actions

// Dealer Bust 
    if (dealer.getHandScore() > 21) {
        money = money + (bet * 2);
        std::cout << "<< Dealer Bust! >>" << "\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
    }

 // Dealer BlackJack
    if (dealer.getHandScore() == 21) {
        //money = money - (bet * 1.5);
        std::cout << "<< Dealer Black Jack! >>" << "\n";
        std::cout << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
    }

// Player > Dealer
    if (dealer.getHandScore() >=17 && player.getHandScore() > dealer.getHandScore()
        && player.getHandScore() <= 21) {
        money = money + (bet * 2);
        std::cout << "<< Player Wins! >>" << "\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
    }

// Dealer > Player
    if (dealer.getHandScore() >=17 && player.getHandScore() < dealer.getHandScore()
        && dealer.getHandScore() < 21) {
        std::cout << "<< Dealer Wins! >>" << "\n";
        std::cout << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue...";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
    }

// Player == Dealer (PUSH)
    if (dealer.getHandScore() >=17 && player.getHandScore() == dealer.getHandScore()) {
        money = money + bet; // refunds bet
        std::cout << "<< PUSH >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n\n";
        std::cin >> playerHSD;
        /* 
            for (int t = 1; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
    }

} // Game Block


// RESET CHIPS 
if (select == 2) {
    system("cls");

        if (money <= 0) {
            money = 200;
            std::cout << "FUNDS RESET TO " << money << "\n\n";
            std::cout << R"(
              =%%#*#%%%##*##%%%%%%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%#          
             .%%%#%%%##**##%%%%%%%%%%%%@@@@%%%%%%@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%-          
             ##%%%%##***##%%%%%%%%%%@@@@@@%###%%%%@@@@@@@%%%%%%%%@@@%%%%%%%%%%%           
            +*#@%%#*+**###%%%%%%%%%@@@@@@@%##%%@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%+           
            ##%%%#*++**###%%%%%%%@@@@@@@@@%#%@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%            
           *##%%#*++**###%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%=            
           #=::-*+++**###%%%%%@@@@@@@@@@@@@@@@%%%@@@@@@@@@@@@@@@@@%%%%%%%%%%%             
           *.  :*++**###%%%%%@@@@@@@@@@@@@@@%%%%%%@@@@@@@@%%%%@@@@@@%%%%%%%%.             
           *=--+*++***##%%%%%@@@@@@@@@@@@@@@@@@@@%%@@@@%@@@@%%%@@@@@@%%%%%%#              
           *##***+***###%%%%@@@@@@@@@@@@@@@@@@@%%%%%@@@%%@@@%%%%%@@@@@%%%%#               
           *##*******##%%%%%@@@@@@@@@@@@@@@@@@@@@%%@@@@@%%@%%%%%%%%@@@@%%%-               
          :********####%%%%%@@@@@@@@@@@@@@@%#@@@@@@@@@@#+=----=#@@%%@@@%%%                
          -********###%%%%%%@@@@@@@@@@@@@@@%%@#==-++:.            .*@@@%%-                
          =***##**####%%%%%%%@@@@@@@@@@+.      .........             .%%%                 
          +**###**###%%%%%%%@@@@@@@@@:         :::......                -                 
          +**########%%%%@@@@@@@@@@=           :--:..::....                               
          +**#######%%%@@@@@@@@@@=             :---::::....        ....                   
          +**######%%%@@@@@@@@@@:              :---:......         .:=-::.                
      .       ...:+%%%@@@@@@@@=               .:---:......        .*++=+=---=:.           
      -:.             .:-#@%:     .          ..:----:::.           =#@#**+**--...         
         =#+-::.            ..              ...:=-::::.        .-=%@%#++#*#=-:::::        
         =###%*+=-:.   .                 ....:.......           .-*%#.     *+=+=--:       
         =*#%@%%%#**+=----+**=:.. .       ..:::.....          .:-+#%#       ##***+=-.     
          .          -@@%%%**+::...       ....::.  ..        :=@%##%%#         =##*+:     
         :-:                        .::.::....:::::::.      :@@%###%%%-                   
         %+=--#+-:..                +=+---:...:-++=:.      .-@%#%##%%%%                   
         @%%@@@@%#*+-:.:..    ...:=%@*.      :*%@=::.      -@%%%%#%%%%#                   
         @%%@@@@@@@@@:::       . .@--:.     .-#@*===-.    .@%%@@%%%%%%%                   
        .@@@@@@@@@@@@@=+-:::              ....  ..        @%@@@@@%%%%%                    
        :@@@@@@@@@@@@@@@%++*#+:::.......-=:              +%%@@@@@%%%+                     
        *@@@@@@@@@@@@@@@@@@##*++===-----+*=:. .         .@@@@@@@@@*                       
        @@@@@@@@@@@@@@@@@@@@@@@####*****#@@*+=#*=------:@@@@@@@@@-                        
       +@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@@@@@@@@@@@@#@@@@@@@@@@@@#           
                     
                 +-----+ << ARE YOU WINNING YET? >> +-----+
)"; 
                for (int t = 3; t >= 0; t--){
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
        }

        else {
            std::cout << R"(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%+*#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:%@%@%@@@@@@@@-@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-..%@@@@@@@@@@@@@-@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=::.*+:.@@@@@@@@@@@@:.::-+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@-:..........@@@@...@@@@@.:....::--+@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@+:::.............-@@%...@@%@::::....::::---=*@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@+.............:....:@@@...@@@@.:::-..:::::::::.-@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@%.......::..........#@@...:@@@::-:..::::::::-:::@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@.......::..........:@@...:@@.:::::.::::::-::.-.+@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@=..-:....:..........:@@...:@@.::-::::::::::::.:.:@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@:.................:..:@...:@::::::::::::::-:.--::@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@................::....@...:@.::*:#-::::::::.::-::-@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@++..............+..:...::..:#@:***#:-:::::::.:::-+:@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@....................:*@@@@@@@@@@::::::--::-::--:-::@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@*.....................#@@%@@@@@@@@-:::-:::-:.:.--:::%@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@=..............-.....*-#%#-*@@@@*@@::-::::::..::::--*@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@-...................#*#@@@@@%#@@@@@@:::::::..:-::-:.+@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@*................%#%####@@@@@@@@@@@@@@@:::....:---:::@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@*...............%@##%%%@@@@@@@#@@@@@@@@@.....:.::-:::@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@...=............@@@@@@%........:@@@@@@@@=::....-....:@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@.--.............@@@@@@.....:.....@::*@@+--::::.-:.**#@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@*..............-.@@@*%...........:#%@@%-:-+--.-:.***#@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@-.................@-@.....:.....+.@.##.---------:-:-:@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@:...................................-.:-::::----:-:--@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@+......................................:-:::.::-----@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@:........................:..................:::---*@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@:.......................:.....::............:-::=@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@:....................::::::::::..........:::--@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@-.............-...:::=::::::.:.-..:*@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@-................::::::::-*::..:...:@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@.................:@@::::#*:*:.::...:@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@:.................:::.:::::::.:.....::@@@@@@@@@@@@@@@@@@@@@@@@@@
                        
                        +-----+ << YOU'RE NOT BANKRUPT... YET >> +-----+
)"; 
                for (int t = 3; t >= 0; t--){
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
        }

} // Reset Chips Block


// EXIT
if (select == 3) {
    system("cls");
    keepGoing = false;
// face art
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAA  A AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAA        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAA           AAAAAAAAAAAAAAA         AAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAA              AAAAAAAAAAAA          AAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAA                 AAAAAAAAA           AAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAA               AAAAAAAAAA            NAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAA              AAAAAAAAAA             AAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAA            AAAAAAAAAAt              IAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAA         AAAAAAAAAAAAAA             AAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA           AAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA      AAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAA  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAA A AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAA A   AAAAAAAAAAAAAAAAAAAAAAAAAAAAA   AAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAw   u     AAAAAAAAAAAAAAAAAb     AAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAA  A   E                 A      AAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAA X A     A A     A      V AAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAi A      A  A          AAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAA    AA   A A    AA   AAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA A    A       AAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        std::cout << "\n";
        for (float t = 0.1; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        std::cout << "           +-----+ << YOU'LL BE BACK >> +-----+\n";

        for (int t = 3; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    break; // breaks loop exits exe

    } // Exit Block

} // keep going block

return 0;
} // main() block