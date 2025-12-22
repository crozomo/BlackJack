#include "header.hpp"
#ifdef _WIN32
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
SetConsoleOutputCP(CP_UTF8);
#endif
system("cls");

// ACTOR CLASSES
HandManager dealer;
HandManager player;

// USER
int money {200}; // player starting funds

// MENU INPUTS
int select {}; // menu select
int bet {}; // set bet size
char loopChoice {}; // used for exiting program

// Menu Booleans
bool keepGoing {true}; // loops through entire program
bool betMenu = (bet <= 0 || bet > money);
bool initGame = true; // initial card deal
bool moneyBetLoop {true}; // update player money and bet size during dealer actions and win/loss

// GAME INPUTS
int playerHSD {}; // hit/stand/double

// RANDOM MACHINE
std::random_device rd;
std::mt19937 rng(rd());

// ACTOR BOOL ACTIONS
bool playerTurn {true};
bool dealerTurn {true};


while (keepGoing) {
system("cls");
// Main Menu 
std::cout << R"(
♠+===+===+===+===+===+===+♠
|  ♠ ♥   BLACKJACK  ♣ ♦  |
♠+===+===+===+===+===+===+♠

)";

std::cout << "MONEY: " << money << "\n\n";

if (money == 0 && money < 1) {
    std::cout << "99% of Gamblers..." << "\n";
}

if (money >= 1000 && money < 5000) {
    std::cout << "Hey! Check Out the High-Roller!" << "\n";
}

if (money >= 5000 && money < 10000) {
    std::cout << "Whoa Buddy! Leave Some Chips for the Rest of Us!" << "\n";
}

if (money >= 10000 && money < 1000000) {
    std::cout << "You've Had Enough Fun, We're Going To Have to Ask You to Leave" << "\n";
}

if (money >= 1000000) {
    std::cout << "<<< I Know What You Are >>>" << "\n";
}

std::cout << R"(
.+===+===+===+===+===+===+.
|   1. START              |
|                         |
|   2. RESET CHIPS (200)  |
|                         |
|   3. EXIT               |
'+===+===+===+===+===+===+'

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
    betMenu = true;
    playerTurn = true;
    dealerTurn = true;
    initGame = true;
    system("cls");

// Betting Screen
while (betMenu) {
system("cls");
std::cout << R"(
*+===+===+===+===+===+===+*
|      PLACE YOUR BET     |
*+===+===+===+===+===+===+*

)";

    if (money <= 0) {
        betMenu = false;
        bet = 0;
        money = 0;
        std::cout << "<< YOU HAVE NO MONEY >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD; 
            if (std::cin.fail()) { 
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid Input, Please Enter a Number\n";
                std::cout << "Press 'Enter' to Try Again\n";
                std::cin.get();
                continue;
            }
            initGame = false;
            playerTurn = false;
            dealerTurn = false;
        
        system("cls");
    }
    
    else if (money > 0) {
    std::cout << "Enter 'X' to Exit" << "\n\n";
    std::cout << "MONEY: " << money << "\n\n";
    std::cout << "SET BET SIZE: \n";
    std::cin >> bet;
    
        if (bet > money) {
            system("cls");
            std::cout << "Error: Insufficient Funds!" << "\n\n";
        }

        if (bet <= 0) {
            system("cls");
            std::cout << "Error: Please Enter a Valid Bet!" << "\n\n";
        }

    if (std::cin.fail()) {
            betMenu = false;
            initGame = false;
            playerTurn = false;
            dealerTurn = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
        }

    }

if (bet > 0 && bet <= money && money > 0) {
       betMenu = false;
}

} // EXIT BETTING SCREEN

// GAME INIT PREP
system ("cls");
dealer.clearHand();
player.clearHand();

// Check remaining cards in deck - reset if <= 20 cards
if (playingCards.size() <= 20) {
    std::cout << "SHUFFLING DECK..." << "\n";
            for (int t {1}; t >= 0; t--) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
    playingCards = generateDeck;
}

// GAME START
while (initGame) {
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
        initGame = false;
}

//bool playerTurn = true;
while (playerTurn) {
    system ("cls");
    printGameBoard(dealer, player, money, bet);

// Player opens with BlackJack
    if (player.getHandScore() == 21) {
        money = money + (bet * 3);
        std::cout << "\n" << "♠ ♠ ♠ <<< Player BlackJack! >>> ♠ ♠ ♠" << "\n";
        std::cout << "YOU WON " << bet << "\n";
        std::cout << "Enter '1' to Continue...";
        playerTurn = false;
        std::cin >> playerHSD;
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
/*
// Show Bet Size
std::cout << "Bet Size: " << bet << "\n\n";

// Player Actions
std::cout << "MONEY: " << money << "\n";
*/

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
// fix being able to double with no money/not enough money
    else if (playerHSD == 3) {
        system ("cls");
        printGameBoard(dealer, player, money, bet);

// cout error message if doubling bet will lead to money > 0. 
        if (money - bet * 2 <= 0) {
            std::cout << "Error: Insufficient Funds!" << "\n" ;
                for (int t {1}; t >= 0; t--){
                std::this_thread::sleep_for(std::chrono::seconds(1));
                }
        }

        else {
            player.addCard(drawRandomCard(playingCards, rng));
            player.getHandScore();
            bet = bet * 2; // doubles bet size
                    for (int t {1}; t >= 0; t--){
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
            playerTurn = false;
        }
    } // DOUBLE BLOCK

    
// Player Bust
    if (player.getHandScore() > 21) {
        system ("cls");
        printGameBoard(dealer, player, money, bet);

        std::cout << "<< BUST! >>" << "\n";
        money = money - bet;
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;

        playerTurn = false;
    }

// Player BlackJack
    if (player.getHandScore() == 21) {
        system ("cls");
        printGameBoard(dealer, player, money, bet);

        money = money + (bet * 2); 
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "♠ ♠ ♠ <<< Player BlackJack! >>> ♠ ♠ ♠" << "\n\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;

        playerTurn = false;
    }

} // playerTurn loop 

// Dealer Actions
// If Player Busts or Black Jack, skip Dealers Turn
if (player.getHandScore() == 21 || player.getHandScore() > 21) {
    dealerTurn = false;
}

while (dealerTurn) {
    system ("cls");
    printGameBoard(dealer, player, money, bet);

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
        money = money + bet;
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "<< Dealer Bust! >>" << "\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;
    }

 // Dealer BlackJack
    if (dealer.getHandScore() == 21) {
        money = money - (bet * 1.5);
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "<< Dealer Black Jack! >>" << "\n";
        std::cout << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;
    }

// Player > Dealer
    if (dealer.getHandScore() >=17 && player.getHandScore() > dealer.getHandScore()
        && player.getHandScore() <= 21) {
        money = money + bet;
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "<< Player Wins! >>" << "\n";
        std::cout << "<< YOU WON " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;
    }

// Dealer > Player
    if (dealer.getHandScore() >=17 && player.getHandScore() < dealer.getHandScore()
        && dealer.getHandScore() < 21) {
        money = money - bet;
        system ("cls");
        printGameBoard(dealer, player, money, bet);
        std::cout << "\n" << "<< Dealer Wins! >>" << "\n";
        std::cout << "<< YOU LOST " << bet << " >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n";
        std::cin >> playerHSD;
    }

// Player == Dealer (PUSH)
    if (dealer.getHandScore() >=17 && player.getHandScore() == dealer.getHandScore()) {
        std::cout << "\n" << "<< PUSH >>" << "\n\n";
        std::cout << "Enter '1' to Continue..." << "\n\n";
        std::cin >> playerHSD;
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

        for (int t {3}; t >= 0; t--){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    break; // breaks loop exits exe

    } // Exit Block

} // keep going block

return 0;
} // main() block