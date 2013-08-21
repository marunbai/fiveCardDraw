#include "hand.h"

typedef struct player{
  char* name;
  Hand* hand;
}Player;

void player_init(Player* player, char* s);
int get_winner(Player** p);
void print_montecarlo_result(int* ret_value);
void change_card_by_montecarlo(int* ret_value, Hand* h, Deck* deck);
