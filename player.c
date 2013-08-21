#include "player.h"

void player_init(Player* player, char* s){
  player->name = s;
  Hand* hand = malloc(sizeof(Hand));
  hand_init(hand);
  player->hand = hand;
}

int get_winner(Player** p){
  int i,winner;
  int max = 0;
  for(i = 0; i<4; i++){
    if( ((p[i]->hand)->value) > max){
      max = (p[i]->hand)->value;
      winner = i;
    }
  }
  return winner;
}

void print_montecarlo_result(int* ret_value){
  int i;
  if(ret_value[0] == 0){
    printf("the best move for this hand is not to change hand\n");
    printf("the change card is: ");
  }

  else if(ret_value[0] == 1){
    printf("the best move for this hand is to change 1 card\n");
    printf("the change card is: ");
  }
  else if(ret_value[0] == 2){
    printf("the best move for this hand is to change 2 cards\n");
    printf("the change card is: ");
  }
  else if(ret_value[0] == 3){
    printf("the best move for this hand is to change 3 cards\n");
    printf("the change card is: ");
  }
  
  for(i = 0; i<ret_value[0]; i++){
    printf("%d ", ret_value[i+1]+1);
  }
  putchar('\n');
}

void change_card_by_montecarlo(int* ret_value, Hand* h, Deck* deck){
  int i,index;
  if(ret_value[0] != 0){
    for(i = 0; i< ret_value[0]; i++){
      index = ret_value[i+1];
      Card** a = malloc(sizeof(Card));
      deck_dequeue(deck, (const void **) a);
      Card* b = malloc(sizeof(Card));
      b->value = h->hand_arr[index].value;
      b->suit = h->hand_arr[index].suit;
      deck_enqueue(deck,(const void *)b);
      h->hand_arr[index] = *(*a);
    }
  }
}
