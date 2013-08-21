#include "hand.h"

void hand_init(Hand* h){
  h->size = 0;
  h->hand_arr = malloc(sizeof(Card)*5);
  h->class = 0;
  h->def_card = 0;
  h->value = 0;
}

void hand_insert(Hand* h, Card* card){
  h->hand_arr[h->size] = *card;
  h->size++;
}

void hand_print(Hand* h){
  int i = 0;
  for(i = 0; i<h->size; i++){
    printf("%d%c " , (h->hand_arr[i]).value,(h->hand_arr[i]).suit);
  }
  if(h->class == 1)
    printf("(high card) \n");
  else if(h->class == 2){
    printf("(one pair) \n");
  }
  else if(h->class == 3){
    printf("(two pairs) \n");
  }
  else if(h->class == 4){
    printf("(three of a kind) \n");
  }
  else if(h->class == 5){
    printf("(straight) \n");
  }
  else if(h->class == 6){
    printf("(flush) \n");
  }
  else if(h->class == 7){
    printf("(full house) \n");
  }
  else if(h->class == 8){
    printf("(four of a kind) \n");
  }
  else if(h->class == 9){
    printf("(straight flush) \n");
  }
  else if(h->class == 10){
    printf("(royal flush) \n");
  }
  /*
  printf("the class: %d\n", h->class);
  printf("the def card: %d\n", h->def_card);
  printf("the value: %d\n", h->value);
  putchar('\n');
  */
}

void hand_print_simple(Hand* h){
  int i = 0;
  for(i = 0; i<h->size; i++){
    printf("%d%c " , (h->hand_arr[i]).value,(h->hand_arr[i]).suit);
  }
  putchar('\n');
}

int card_cmp(const void *c, const void *d){
  Card* a = (Card *)c;
  Card* b = (Card *)d;
  if(a->value > b->value){
    return 1;
  }
  else if(a->value < b->value)
    return -1;
  else if(a->value == b->value)
    return 0;
}

void deal_card(Hand* h, Deck* deck, int card_num){
  int i;
  for(i=0; i<card_num; i++){
    Card** a = malloc(sizeof(Card));
    deck_dequeue(deck, (const void **) a);
    hand_insert(h, (*a));
  }
  qsort(h->hand_arr,5,sizeof(Card),card_cmp);
  set_hand_class(h);
  compute_hand(h);
}

void change_card(Hand* h , Deck* deck, int index){
  
  Card** a = malloc(sizeof(Card));
  deck_dequeue(deck, (const void **) a);
  Card* b = malloc(sizeof(Card));
  b->value = h->hand_arr[index-1].value;
  b->suit = h->hand_arr[index-1].suit;
  deck_enqueue(deck,(const void *)b);
  h->hand_arr[index-1] = *(*a);

}



void compute_hand_afterchange(Hand* h){
  qsort(h->hand_arr,5,sizeof(Card),card_cmp);
  set_hand_class(h);
  compute_hand(h);
}

int compute_hand(Hand* h){
  int result = (h->class-1)*13 + h->def_card;
  h->value = result;
  return result;
}


void set_hand_class(Hand* hand){
  if(is_royalflush(hand)){
    hand->class = 10;
    hand->def_card = is_royalflush(hand);
  }
  else if(is_straightflush(hand)){
    hand->class = 9;
    hand->def_card = is_straightflush(hand);
  }
  else if(is_fourofakind(hand)){
    hand->class = 8;
    hand->def_card = is_fourofakind(hand);
  }
  else if(is_fullhouse(hand)){
    hand->class = 7;
    hand->def_card = is_fullhouse(hand);
  }
  else if(is_flush(hand)){
    hand->class = 6;
    hand->def_card = is_flush(hand);
  }
  else if(is_straight(hand)){
    hand->class = 5;
    hand->def_card = is_straight(hand);
  }
  else if(is_threeofakind(hand)){
    hand->class = 4;
    hand->def_card = is_threeofakind(hand);
  }
  else if(is_twopair(hand)){
    hand->class = 3;
    hand->def_card = is_twopair(hand);
  }
  else if(is_onepair(hand)){
    hand->class = 2;
    hand->def_card = is_onepair(hand);
  }
  else if(is_highcard(hand)){
    hand->class = 1;
    hand->def_card = is_highcard(hand);
  }
}

int is_royalflush(Hand* h){
  int result = 100;
  int i;
  char tempSuit = h->hand_arr[0].suit;
  for(i=0; i<5; i++){
    if(h->hand_arr[i].suit != tempSuit){
      return 0;
    }
  }
  int j = 10;
  for(i=0; i<5; i++){
    if(h->hand_arr[i].value != j){
      return 0;
    }
    j++;
  }
  return 100;
}

int is_straightflush(Hand* h){
  int result = 100;
  int i;
  char tempSuit = h->hand_arr[0].suit;
  for(i=0; i<5; i++){
    if(h->hand_arr[i].suit != tempSuit){
      return 0;
    }
  }
  int j = h->hand_arr[0].value;
  for(i=0; i<5; i++){
    if(h->hand_arr[i].value != j){
      return 0;
    }
    j++;
  }
  return h->hand_arr[4].value;
}

int is_fourofakind(Hand* h){
  int i,j;

  int result = 5;
  int v = h->hand_arr[0].value;
  for(i = 0; i<4; i++){
    if(h->hand_arr[i].value != v){
      result--;
      break;
    }
  }
  if(result ==5){
    return v;
  }

  result = 5;
  v = h->hand_arr[4].value;
  for(i = 1; i<5; i++){
    if(h->hand_arr[i].value != v){
	result--;
	break;
    }
  }
  if(result == 5){
    return v;
  }
  return 0;
}

int is_fullhouse(Hand* h){
  int i,j;
  int result = 5;
  int v1 = h->hand_arr[0].value;
  int v2 = h->hand_arr[2].value;
  if(h->hand_arr[1].value == v1 && h->hand_arr[3].value == v2 && h->hand_arr[4].value == v2){
    return v2;
  }
  v1 = h->hand_arr[0].value;
  v2 = h->hand_arr[3].value;
  if( h->hand_arr[1].value == v1 && h->hand_arr[2].value == v1 && h->hand_arr[4].value == v2){
    return v1;
  }
  else {
    return 0;
  }
}

int is_flush(Hand* h){
  int result = 100;
  int i;
  for(i=0; i<=3; i++){
    if(h->hand_arr[i].suit != h->hand_arr[i+1].suit){
      return 0;
    }
  }
  return (h->hand_arr[4]).value;
}

int is_straight(Hand* h){
  int i;
  int v = h->hand_arr[0].value;
  for(i = 0; i<5; i++){
    if(h->hand_arr[i].value != v+i)
      return 0;
  }
  return h->hand_arr[4].value;
}

int is_threeofakind(Hand* h){
  if(! is_fourofakind(h)){
    int v = h->hand_arr[0].value;
    if(h->hand_arr[1].value == v && h->hand_arr[2].value == v)
      return v;
    v = h->hand_arr[1].value;
    if(h->hand_arr[2].value == v && h->hand_arr[3].value == v)
      return v;
    v = h->hand_arr[2].value; 
    if(h->hand_arr[3].value == v && h->hand_arr[4].value == v)
      return v;
  }
  return 0;
}

int is_twopair(Hand* h){
  if(! is_fourofakind(h)){
    if(! is_fullhouse(h)){
      int v1 = h->hand_arr[0].value;
      int v2 = h->hand_arr[2].value;
      if( h->hand_arr[1].value == v1 && h->hand_arr[3].value == v2)
	return v2;
      v2 = h->hand_arr[3].value;
      if( h->hand_arr[1].value == v1 && h->hand_arr[4].value == v2)
	return v2;
      v1 = h->hand_arr[1].value;
      v2 = h->hand_arr[3].value;
      if( h->hand_arr[2].value == v1 && h->hand_arr[4].value == v2)
	return v2;
    }
  }
  return 0;
}

int is_onepair(Hand* h){
  if(! is_twopair(h)){
    int i;
    for(i = 0; i<4; i++){
      if(h->hand_arr[i].value == h->hand_arr[i+1].value)
	return h->hand_arr[i].value;
    }
  }
  return 0;
}

int is_highcard(Hand* h){
  int result = 100;
  int i;
  for(i=0; i<=3; i++){
    if(h->hand_arr[i].value == h->hand_arr[i+1].value){
      return 0;
    }
  }
  return (h->hand_arr[4]).value;
}

int* monte_carlo_advisor(Hand* h){
  int count = 0;
  int sum_value = 0;
  double max,max_change_one_card, max_change_two_cards, max_change_three_cards;
  int index_one_card, index_two_card1, index_two_card2, index_three_card1, index_three_card2, index_three_card3;
  int* ret_value = malloc(sizeof(int)*4);
  int j,k,m;

  max = (double)h->value;
  Card* copy1 = malloc(sizeof(Card));
  Card* copy2 = malloc(sizeof(Card));
  Card* copy3 = malloc(sizeof(Card));
  Card* copy4 = malloc(sizeof(Card));
  Card* copy5 = malloc(sizeof(Card));
  copy_card(copy1,h,0);
  copy_card(copy2,h,1);
  copy_card(copy3,h,2);
  copy_card(copy4,h,3);
  copy_card(copy5,h,4);

  /* change one card*/
  for(j = 0; j<5; j++){
    //printf("----------------------------------\n");
    count = 0;
    sum_value = 0;
    while(count<10000){
    //printf("----------------------------------\n");
      int is_card_ok = 0;
      Card* card = malloc(sizeof(Card));
      do{
          int random = (int)(rand() % 13) + 2;
          int i =  (int)(rand() % 3);
          card_init(card,random,i);
          is_card_ok = check_card(card,h);
      }while(!is_card_ok);
    
      h->hand_arr[j] = *card;
      //hand_print(h);
      compute_hand_afterchange(h);
      //printf("the hand value after change is: %d\n", h->value);
      sum_value += h->value;
      h->hand_arr[0] = *copy1;
      h->hand_arr[1] = *copy2;
      h->hand_arr[2] = *copy3;
      h->hand_arr[3] = *copy4;
      h->hand_arr[4] = *copy5;
      count++;
      //free(card);
    }
    h->hand_arr[0] = *copy1;
    h->hand_arr[1] = *copy2;
    h->hand_arr[2] = *copy3;
    h->hand_arr[3] = *copy4;
    h->hand_arr[4] = *copy5;
    compute_hand_afterchange(h);

   double average = (double) sum_value/ (double) 10000;
   //putchar('\n');
   //printf("the average value for changing card is: %.2f\n", average);
   if(average > max_change_one_card){
     max_change_one_card = average;
     index_one_card = j;
   }
  }
  //printf("the max value for changing one card is: %.2f\n", max_change_one_card);
  //printf("the change card is: %d\n", index_one_card+1);
  if(max_change_one_card > max)
    max = max_change_one_card;
  
  /* change 2 cards */
  for(j = 0; j<4; j++){
    for(k = j+1; k<5; k++){
      count = 0;
      sum_value = 0;
      while(count<10000){
	//printf("----------------------------------\n");
	int random,i;
	int is_card_ok= 0;
	Card* card = malloc(sizeof(Card));

	do{
	  random = (int)(rand() % 13) + 2;
	  i =  (int)(rand() % 3);
	  card_init(card,random,i);
	  is_card_ok = check_card(card,h);
	}while(!is_card_ok);
	h->hand_arr[j] = *card;

	do{
	  random = (int)(rand() % 13) + 2;
	  i =  (int)(rand() % 3);
	  card_init(card,random,i);
	  is_card_ok = check_card(card,h);
	}while(!is_card_ok);
	h->hand_arr[k] = *card;

	compute_hand_afterchange(h);
	//printf("the hand value after change is: %d\n", h->value);
	sum_value += h->value;
	h->hand_arr[0] = *copy1;
	h->hand_arr[1] = *copy2;
	h->hand_arr[2] = *copy3;
	h->hand_arr[3] = *copy4;
	h->hand_arr[4] = *copy5;
	count++;
      }
      h->hand_arr[0] = *copy1;
      h->hand_arr[1] = *copy2;
      h->hand_arr[2] = *copy3;
      h->hand_arr[3] = *copy4;
      h->hand_arr[4] = *copy5;
      compute_hand_afterchange(h);
      double average2 = (double) sum_value/ (double) 10000;
      //printf("the average value for changing first and second card is: %.2f\n", average2);
      if(average2 > max_change_two_cards){
	max_change_two_cards = average2;
	index_two_card1 = j;
	index_two_card2 = k;
      }
    }
  } // end of change 2 cards

  //printf("the max value for changing two cards is: %.2f\n", max_change_two_cards);
  //printf("the change card is: %d %d\n", index_two_card1+1, index_two_card2+1);
  if(max_change_two_cards > max)
    max = max_change_two_cards;

  /*change 3 cards */
  for(j= 0; j<5; j++){
    for(k=j+1; k<5; k++){
      for(m = k+1; m<5; m++){
	count = 0;
	sum_value = 0;
	while(count<10000){
	  int random,i;
	  int is_card_ok= 0;
	  Card* card = malloc(sizeof(Card));
	  do{
	    random = (int)(rand() % 13) + 2;
	    i =  (int)(rand() % 3);
	    card_init(card,random,i);
	    is_card_ok = check_card(card,h);
	  }while(!is_card_ok);
	  h->hand_arr[j] = *card;
	  
	  do{
	    random = (int)(rand() % 13) + 2;
	    i =  (int)(rand() % 3);
	    card_init(card,random,i);
	    is_card_ok = check_card(card,h);
	  }while(!is_card_ok);
	  h->hand_arr[k] = *card;

	  do{
	    random = (int)(rand() % 13) + 2;
	    i =  (int)(rand() % 3);
	    card_init(card,random,i);
	    is_card_ok = check_card(card,h);
	  }while(!is_card_ok);
	  h->hand_arr[m] = *card;

	  compute_hand_afterchange(h);
	//printf("the hand value after change is: %d\n", h->value);
	  sum_value += h->value;
	  h->hand_arr[0] = *copy1;
	  h->hand_arr[1] = *copy2;
	  h->hand_arr[2] = *copy3;
	  h->hand_arr[3] = *copy4;
	  h->hand_arr[4] = *copy5;
	  count++;
	}
	h->hand_arr[0] = *copy1;
	h->hand_arr[1] = *copy2;
	h->hand_arr[2] = *copy3;
	h->hand_arr[3] = *copy4;
	h->hand_arr[4] = *copy5;
	compute_hand_afterchange(h);
	double average3 = (double) sum_value/ (double) 10000;
	//printf("the average value for changing 3 cards is: %.2f\n", average3);
	if(average3 > max_change_three_cards){
	  max_change_three_cards = average3;
	  index_three_card1 = j;
	  index_three_card2 = k;
	  index_three_card3 = m;
	}

      }
    }
  } // end of change 3 cards

  if(max_change_three_cards > max)
    max = max_change_three_cards;

  if(max == max_change_one_card){
    ret_value[0] = 1;
    ret_value[1] = index_one_card;
    //printf("the change card is: %d\n", index_one_card+1);
  }
  else if( max == max_change_two_cards){
    ret_value[0] = 2;
    ret_value[1] = index_two_card1;
    ret_value[2] = index_two_card2;
    //printf("the change card is: %d %d\n", index_two_card1+1, index_two_card2+1);
  }
  else if( max == max_change_three_cards){
    ret_value[0] = 3;
    ret_value[1] = index_three_card1;
    ret_value[2] = index_three_card2;
    ret_value[3] = index_three_card3;
    //printf("the change card is: %d %d %d\n", index_three_card1+1, index_three_card2+1, index_three_card3+1);
  }
  else {
    ret_value[0] = 0;
  }
  return ret_value;
} 

void card_init(Card* card, int value, int suit){
  card->value = value;
  if(suit == 0)
    card->suit = 'D';
  else if(suit == 1)
    card->suit = 'S';
  else if(suit == 2)
    card->suit = 'H';
  else if(suit == 3)
    card->suit = 'C';
}

int check_card(Card* card, Hand* hand){
  int i;
  for(i = 0; i<5; i++){
    if(card->value == hand->hand_arr[i].value && card->suit == hand->hand_arr[i].suit)
      return 0;
  }
  return 1;
}

void copy_card(Card* card, Hand* hand, int index){
  card->value = hand->hand_arr[index].value;
  card->suit = hand->hand_arr[index].suit;
}
