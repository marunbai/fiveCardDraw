#include "deck.h"


void knuthShuffle(Card* arr) { 
  int random,i; 
    for(i=51;i>=1;i--){ 
      random = (int)(rand() % i) + 0;
      //printf("the random number is : %d\n", random);
      Card temp;
      temp.value = arr[i].value;
      temp.suit = arr[i].suit;
      //printf("%d%c " , temp.value,temp.suit); 
      arr[i].value = arr[random].value;
      arr[i].suit = arr[random].suit;
      arr[random].value = temp.value;
      arr[random].suit = temp.suit; 
    } 
}

Card* shuffle_card(){
  Card* card_arr = malloc (sizeof(Card)*52);
  char tempSuit;
  int count = 0;
  int i,j;
  for(i=2; i<15; i++){
    for(j = 0; j<4; j++){
      if(j == 0) tempSuit = 'S';
      else if(j == 1 ) tempSuit = 'H';
      else if(j == 2) tempSuit = 'C';
      else if(j == 3) tempSuit = 'D';
      Card* c = malloc(sizeof(Card));
      c->value = i;
      c->suit = tempSuit;
      card_arr[count] = *c;
      count++;
    }
  }
  knuthShuffle(card_arr);
  return card_arr;
}

void deck_init(Deck* deck, Card* card_arr){
  deck->head = NULL;
  deck->tail = NULL;
  deck->size = 0;
  int i, j;
  int z = 0;
  for(i = 0; i<13; i++){
    for(j = 0; j<4; j++){
      deck_enqueue(deck,&card_arr[z]);
      z++;
    }
  }
  //deck_print(deck);
}

int deck_enqueue(Deck *deck, const void *data){
  return list_ins_next(deck, list_tail(deck), data);
}

int deck_dequeue(Deck *deck,const void **data){
  return list_rem_next(deck, NULL, data);
}

void deck_destory(void *data){
  free(data);
}

char* tostr(void* data){
  Card* t = malloc(sizeof(Card));
  t = (Card*) data;
  char* str = malloc(sizeof(char)*5);
  sprintf( str , "%d%c " , t->value,t->suit);
  return str;
  /*
  if(t->value <= 10){
    sprintf( str , "%d%c " , t->value,t->suit);
    return str;
  }
  if(t->value == 11){
    sprintf( str , "%c%c " , 'J',t->suit);
    return str;
  }
  if(t->value == 12){
    sprintf( str , "%c%c " , 'Q',t->suit);
    return str;
  }
  if(t->value == 13){
    sprintf( str , "%c%c " , 'K',t->suit);
    return str;
  }
  if(t->value == 14){
    sprintf( str , "%c%c" , 'A',t->suit);
    return str;
  }
  */
}

void deck_print(Deck *deck){
  ListElmt *node = list_head(deck);
  printf("[ "); 
  while (node != NULL){
    printf("%s ", tostr(node->data));
    node = node->next;
  }
  printf(" ]\n"); 
  return;
}
