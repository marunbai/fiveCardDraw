#include <time.h>
#include "list.h"
#include "card.h"


typedef List Deck;
int deck_enqueue(Deck *deck, const void *data);
int deck_dequeue(Deck *deck, const void **data);
void deck_destory(void *data);
void deck_print(Deck *deck);
void deck_init(Deck* deck, Card* card_arr);
Card* shuffle_card();

#define deck_peek(deck) ((deck)->head == NULL ? NULL : (deck)->head->data)
#define deck_size list_size
