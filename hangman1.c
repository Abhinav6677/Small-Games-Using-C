#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define WORDS 104
#define WORDLEN 80
#define CHANCE 6

bool randomused = false;

int rndm(int i) {
    if (!randomused) {
        srand(time(NULL) << 10);
        randomused = true;
    }
    return rand() % i;
}

void printWord(char* guess, int len) {
	printf("\t");
	for (int i = 0; i < len; ++i)
	{
		printf("%c ", guess[i]);
	}
	printf("\n\n");
}



void printBody(int mistakes, char* body) {
	printf("\tMistakes :%d\n", mistakes);
	switch(mistakes) {

		case 6: body[6] = '*'; break;
		case 5: body[5] = '*'; break;
		case 4: body[4] = '*'; break;
		case 3: body[3] = '*'; break;
		case 2: body[2] = '*'; break;
		case 1: body[1] = '*';break;
		default: break;

	}

	printf( "  %c %c %c %c %c %c\n",  body[1], body[2],
	       body[3], body[4], body[5], body[6]);
}


int main() {

	printf("\n\t Let's play the HANGMAN game.");

	printf("\n\n\t Condition");
	printf("\n\t - Total 6 maistakes are allowed");
	printf("\n\t - We are using only lower cases");
	printf("\n\t - We only have name of fruits to guess");
	
 // we had asked to do in limited fruits thats why we used 2d arrys to store these
 
	printf("\n\t ONLY WRITE ALPHABETS");
    char FRUITS[WORDS][WORDLEN] =  {"abiu", "acerola", "akebi", "ackee", "apple", "apricot", "araza",
                        "avocado", "banana", "bilberry", "blackberry", "blackcurrant", "blueberry",
                        "boysenberry", "breadfruit", "canistel", "cashew", "cempedak", "cherimoya",
                        "cherry", "cloudberry", "coconut", "cranberry", "currant", "damson", "date",
                        "dragonfruit", "pitaya", "durian", "elderberry", "feijoa", "fig", "gooseberry",
                        "grape", "raisin", "grapefruit", "guava", "honeyberry", "huckleberry", "jabuticaba",
                        "plinia", "jackfruit", "jambul", "jostaberry", "jujube", "kiwano", "kiwifruit", "kumquat",
                        "lemon", "lime", "loganberry", "longan", "loquat", "lulo", "lychee", "mango",
                        "mangosteen", "marionberry", "melon", "cantaloupe", "galia", "melon", "honeydew",
                        "watermelon", "mulberry", "nance", "nectarine", "orange", "clementine", "mandarine",
                        "tangerine", "papaya", "passionfruit", "pawpaw", "peach", "pear", "persimmon", "plantain",
                        "plum", "prune", "pineapple", "pineberry", "plumcot", "pluot", "pomegranate", "pomelo",
                        "quince", "raspberry", "salmonberry", "rambutan", "redcurrant", "salak", "sapodilla",
                        "sapote", "satsuma", "soursop", "strawberry", "tamarillo", "tamarind", "tangelo",
                        "tayberry", "ximenia", "yuzu"};
	char *body = malloc(CHANCE+1);
    
   
	int id = rndm(WORDS);
	
   char *word=FRUITS[id];
	int len = strlen(word);
	char *guessed = malloc(len);
	char falseWord[CHANCE];

	memset(body, ' ', CHANCE+1);
	memset(guessed, '_', len);
	char guess;
	bool found;
	char* win;

	int mistakes = 0;
	setvbuf(stdin, NULL, _IONBF, 0);

	do {

		found = false;
		printf("\n\n");
		printBody(mistakes, body);
		printf("\n\n");
		printf("\tFalse Letters : ");
		if(mistakes == 0) printf("None\n");
		for (int i = 0; i < mistakes; ++i)
		{
			printf("%c", falseWord[i]);
		}
		printf("\n\n");
		printWord(guessed, len);
		printf("\tGive me a alphabet in lower case : ");
		do {scanf("%c",&guess);} while ( getchar() != '\n' );
		for (int i = 0; i < len; ++i)
		{
			if(word[i] == guess) {
				found = true;
				guessed[i] = guess;
			}
		}
		if(!found) {
			falseWord[mistakes] = guess;
			mistakes += 1;
		}
		win = strchr(guessed, '_');
	}while(mistakes < CHANCE && win != NULL);

	if(win == NULL) {
		printf("\n");
		printWord(guessed, len);
		printf("\n\tCongrats! You have won : %s\n\n", word);
	} else {
		printf("\n");
		printBody(mistakes, body);
		printf("\n\n\tBetter try next time. Word was %s\n\n", word);
	}

	free(body);
	free(word);
	free(guessed);
	return EXIT_SUCCESS;
}