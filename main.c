#include "player.h"

int main(int argc, char** argv){
  
  printf("**********************************************************\n");
  printf("*                    Runbai Ma                           *\n");            
  printf("*                    Final Project                       *\n");
  printf("*                Five draw Card Game                     *\n");
  printf("*                                                        *\n");
  printf("*                                                        *\n");
  printf("**********************************************************\n");

  printf("1.start game \n");
  printf("2.quit\n");

  char input = getchar();
  char play_again = '1';
  
  if(input == '1'){
    while(play_again == '1'){

      putchar('\n');

      srand((unsigned int)time(NULL));
      Deck* deck = (Deck*) malloc(sizeof(Deck));
      Card* card_arr = malloc (sizeof(Card)*52);
      int* ret_value = malloc(sizeof(int));
  
      card_arr = shuffle_card();
      deck_init(deck,card_arr);
    
      /* initial the four player*/
      char* name2 = malloc(sizeof(char)*15);
      name2 = "Computer 1";
      Player* p2 = malloc(sizeof(Player));
      player_init(p2,name2);
      deal_card(p2->hand,deck,5);
      printf("computer 1 hand: ");
      hand_print(p2->hand);

      char* name3 = malloc(sizeof(char)*15);
      name3 = "Computer 2";
      Player* p3 = malloc(sizeof(Player));
      player_init(p3,name3);
      deal_card(p3->hand,deck,5);
      printf("computer 2 hand: ");
      hand_print(p3->hand);

      char* name4 = malloc(sizeof(char)*15);
      name4 = "Computer 3";
      Player* p4 = malloc(sizeof(Player));
      player_init(p4,name4);
      deal_card(p4->hand,deck,5);
      printf("computer 3 hand: ");
      hand_print(p4->hand);

      char* name = malloc(sizeof(char)*15);
      name = "Poker King";
      Player* p1 = malloc(sizeof(Player));
      player_init(p1,name);
      deal_card(p1->hand,deck,5);
  
      printf("your hand:       ");
      hand_print(p1->hand);

      printf("----------------------------------------------------------\n");
      putchar('\n');

      ret_value = monte_carlo_advisor(p2->hand);
      change_card_by_montecarlo(ret_value,p2->hand,deck);
      compute_hand_afterchange(p2->hand);
 

      ret_value = monte_carlo_advisor(p3->hand);
      change_card_by_montecarlo(ret_value,p3->hand,deck);
      compute_hand_afterchange(p3->hand);
  

      ret_value = monte_carlo_advisor(p4->hand);
      change_card_by_montecarlo(ret_value,p4->hand,deck);
      compute_hand_afterchange(p4->hand);
  
      printf("Monte Carlor suggestion for u: \n");
      putchar('\n');
      ret_value= monte_carlo_advisor(p1->hand);
      print_montecarlo_result(ret_value);
      printf("----------------------------------------------------------\n");

      putchar('\n');
      printf("Your hand: ");
      hand_print(p1->hand);
      putchar('\n');

      char c;
      c = getchar();
      printf("Enter the card index you want to change: \n");
      while((c = getchar()) != '\n'){
	//int i = atoi(&c);
	//printf("oh god: %d\n", i);
	if(c == '1')
	  change_card(p1->hand, deck, 1);
	else if(c == '2')
	  change_card(p1->hand, deck, 2);
	else if(c == '3')
	  change_card(p1->hand, deck, 3);
	else if(c == '4')
	  change_card(p1->hand, deck, 4);
	else if(c == '5')
	  change_card(p1->hand, deck, 5);
      }
      compute_hand_afterchange(p1->hand);

      printf("----------------------------------------------------------\n");
      putchar('\n');
      printf("computer 1 after change is: ");
      hand_print(p2->hand);
      printf("computer 2 after change is: ");
      hand_print(p3->hand);
      printf("computer 3 after change is: ");
      hand_print(p4->hand);
      printf("your hand after change is : ");
      hand_print(p1->hand);

 
      printf("----------------------------------------------------------\n");
      putchar('\n');
      printf("the game result is: \n");
      
      Player* p[4] = {p1,p2,p3,p4};
      int winner = get_winner(p);

      if(winner == 0){
	printf("You won the game!\n");
      }
      else{
	printf("%s won the game!\n", p[winner]->name);
      }
      
      putchar('\n');
      putchar('\n');
      putchar('\n');
      printf("1.play again\n");
      printf("2.quit\n");
      play_again = getchar();
    }
  }
}
