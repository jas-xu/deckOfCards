/* Student Name: Jason Xu
 * Student Number: 991545529
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUITS 4
#define RANKS 13
#define DECK_SIZE 52

typedef struct {
  char *rank;
  char *suit;
  char *colour;
}Card;

Card *make_deck ();
void print (Card *);
void shuffle (Card *);
void printToFile (char *, Card *);

/****** DO NOT ALTER THE MAIN FUNCTION ********/
int main (int argc, char *argv[]) {

  Card *deck = make_deck();

  printf(" *************** Original Deck ***************\n");
  print (deck); /* print original deck */
  // If there are 3 CL arguments, prints original deck to specified file.
  if (argc == 3) {
    printToFile(argv[1], deck);
  }

  printf("\n\n *************** Shuffled Deck ***************\n");
  shuffle (deck);
  print (deck); /* print shuffled deck */
  // If there are 3 CL arguments, prints shuffled deck to specified file.
  if (argc == 3) {
    printToFile(argv[2], deck);
  }

  free(deck); // Free up memory being used.

  return 0;
}

Card* make_deck() {
  /* You may want to use these arrays to point rank and suit to, or to strcpy from. Your choice which
   * you choose */
  char *ranks[] = {"King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2", "Ace"};
  char *suits[] = {"Spades", "Clubs", "Hearts", "Diamonds"};

  /* allocate space for 52 cards on the heap */
  Card *deck = malloc(52 * sizeof(Card));

  /* put cards into the space */
  for (int i = 0; i < 52; i++) {
    Card card = *(deck + i);
  }

  /* Set the ranks,suits and colours of the cards  */
  for (int i = 0; i < 52; i++) {
    deck[i].rank = ranks[i % 13]; // Sets rank from King to Ace 4 times
    deck[i].suit = suits[i / 13]; // Sets each suit 13 times

    // Checks the suit and sets the colour accordingly
    if (strcmp(deck[i].suit, "Spades") == 0 
        || strcmp (deck[i].suit, "Clubs") == 0) {
      deck[i].colour = "Black";
    } else {
      deck[i].colour = "Red";
    }
  }

  return deck;
}

/* print the deck to the screen (see sample output on assignment sheet). */
void print(Card *deck) {
  // Iterates 52 times to print each card.
  for (int i = 0; i < 52; i++) {
    printf("%s %s %s\n", deck[i].colour, deck[i].suit, deck[i].rank);
  }
}

/* traverse the deck, one card at a time, swapping the current card
 * with a randomly chosen card from the deck
 */
void shuffle (Card *deck) {
  srand(time(NULL)); // Used to generate random numbers.

  // Iterates 52 times to switch each card
  for (int i = 0; i < 52; i++) {
    Card temp = *(deck + i); // Card being moved is the current iteration number
    int randomCard = rand() % 52; // Random card is chosen randomly from 52 cards
    *(deck + i) = deck[randomCard]; // Moves random card into current card position
    deck[randomCard] = temp; // Moves current card into random card position
  }
}

/* Prints the deck to specified file.
 */
void printToFile(char *fileName, Card *deck) {
  FILE *outputFile;
  outputFile = fopen(fileName, "w"); // Creates file to be output to.
  // Prints all 52 cards individually to the file.
  for (int i = 0; i < 52; i++) {
    fprintf(outputFile, "%s %s %s\n", deck[i].colour, deck[i].suit, deck[i].rank);
  }
  fclose(outputFile); // Closes file
}
