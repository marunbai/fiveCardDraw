#include "deck.h"

typedef struct hand{
  int class;
  Card* hand_arr;
  int def_card;
  int value;
  int size;
}Hand;

void hand_init(Hand* h);
void hand_insert(Hand* h, Card* card);
void hand_print(Hand* h);
void hand_print_simple(Hand* h);
int card_cmp(const void *c, const void *d);
void card_init(Card* card, int value, int suit);

void deal_card(Hand* h, Deck* deck, int card_num);
void set_hand_class(Hand* h);
int compute_hand(Hand* h);
void change_card(Hand* h , Deck* deck, int index);
void compute_hand_afterchange(Hand* h);

int is_royalflush(Hand* h);
int is_straightflush(Hand* h);
int is_fourofakind(Hand* h);
int is_fullhouse(Hand* h);
int is_flush(Hand* h);
int is_straight(Hand* h);
int is_threeofakind(Hand* h);
int is_twopair(Hand* h);
int is_onepair(Hand* h);
int is_highcard(Hand* h);

int* monte_carlo_advisor(Hand* h);
int check_card(Card* card, Hand* hand);
void copy_card(Card* card, Hand* hand, int index);
