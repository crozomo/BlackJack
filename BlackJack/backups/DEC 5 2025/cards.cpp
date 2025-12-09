#include "header.hpp"
/*
// <Cards> is an object type. Elements in the playingCards vector will be converted 
into a Cards object.
*/
std::vector<Cards> playingCards {
/* if player hand has ace and < 21, ace = 11. proto suites: (H)<3 (D)<> (C)-% (S)->
   If next card makes player > 21, ace = 1 until stand or 21 */

    //Black Spades
    {2, "S 2"},
    {3, "S 3"},
    {4, "S 4"},
    {5, "S 5"},
    {6, "S 6"},
    {7, "S 7"},
    {8, "S 8"},
    {9, "S 9"},
    {10, "S 10"},
    {10, "S Jack"},
    {10, "S Queen"},
    {10, "S King"},
    {11, "S Ace"}, 

    //Black Clubs 
    {2, "C 2"},
    {3, "C 3"},
    {4, "C 4"},
    {5, "C 5"},
    {6, "C 6"},
    {7, "C 7"},
    {8, "C 8"},
    {9, "C 9"},
    {10, "C 10"},
    {10, "C Jack"},
    {10, "C Queen"},
    {10, "C King"},
    {11, "C Ace"}, 

    //White Hearts
    {2, "H 2"},
    {3, "H 3"},
    {4, "H 4"},
    {5, "H 5"},
    {6, "H 6"},
    {7, "H 7"},
    {8, "H 8"},
    {9, "H 9"},
    {10, "H 10"},
    {10, "H Jack"},
    {10, "H Queen"},
    {10, "H King"},
    {11, "H Ace"}, 

    //White Diamonds 
    {2, "D 2"},
    {3, "D 3"},
    {4, "D 4"},
    {5, "D 5"},
    {6, "D 6"},
    {7, "D 7"},
    {8, "D 8"},
    {9, "D 9"},
    {10, "D 10"},
    {10, "D Jack"},
    {10, "D Queen"},
    {10, "D King"},
    {11, "D Ace"},
    };