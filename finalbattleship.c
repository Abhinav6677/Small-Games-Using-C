#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



void printMatrix(char matrix[10][10]) {
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

char (* buildBoard(char board[][10], char p))[10] {
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            board[i][j] = p;
        }
    }
    return board;
}

void placeShipHorizontal(char board[][10], int shipLen, int i, int j) {
    char shipChar = shipLen + '0';
    for (int k = j; k < j + shipLen; k++) {
        board[i][k] = shipChar;
    }
}

int* getHorizontal(int boardSize, int shipLen) {
    int* position = malloc(2 * sizeof(int));
    position[0] = rand() % boardSize;
    position[1] = rand() % (boardSize - shipLen + 1);
    return position;
}

void placeShipVertical(char board[][10], int shipLen, int i, int j) {
    char shipChar = shipLen + '0';
    for (int k = i; k < i + shipLen; k++) {
        board[k][j] = shipChar;
    }
}

int* getVertical(int boardSize, int shipLen) {
    int* position = malloc(2 * sizeof(int));
    position[0] = rand() % (boardSize - shipLen + 1);
    position[1] = rand() % boardSize;
    return position;
}

void fillingBoards(char board[][10]) {
    buildBoard(board, '0');
    int length[] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    for (int i = 0; i < 10; i++) {
        int orientation = rand() % 2;
        int* position;
        if (orientation == 0) {
            position = getHorizontal(10, length[i]);
            placeShipHorizontal(board, length[i], position[0], position[1]);
        } else {
            position = getVertical(10, length[i]);
            placeShipVertical(board, length[i], position[0], position[1]);
        }
        free(position);
    }
}
// These are the steps we are going to follow
void shoot(char solution[][10], char game[][10], int i, int j) {
    int count;
    if (solution[i][j] != '0') {
       
       /*  if(solution[i][j+5]!= '0' ||solution[i+5][j]!='0') {
            game[i][j] = '5';
            printf("You hit a ship!\n");
        }else if(solution[i][j+4]!= '0' ||solution[i+4][j]!='0') {
            game[i][j] = '4';
            printf("You hit a ship!\n");
        }else if(solution[i][j+3]!= '0' ||solution[i+3][j]!='0') {
            game[i][j] = '3';
            printf("You hit a ship!\n");
        }else if(solution[i][j+2]!= '0' ||solution[i+2][j]!='0') {
            game[i][j] = '2';
            printf("You hit a ship!\n");
        }*/

        //  while(count<5){
        //     for(int l=0; l<5; l++){ 
        //     if (solution[i-l][j]!='0')
        //     {
        //        count++;
        //     }
        //      if (solution[i+l][j]!='0')
        //     {
        //        count++;
        //     }
        //      if (solution[i][j-l]!='0')
        //     {
        //        count++;
        //     }
        //      if (solution[i][j+l]!='0')
        //     {
        //        count++;
        //     }
        //     }
        // }

       /* if(count==4){
            game[i][j] = '5';
            printf("You hit a ship!\n");
        } else if(count==3){
            game[i][j] = '4';
            printf("You hit a ship!\n");
        } else if(count==2){
            game[i][j] = '3';
            printf("You hit a ship!\n");
        } else if(count==1){
            game[i][j] = '2';
            printf("You hit a ship!\n");
        }*/
        game[i][j] = 'h';
        printf("You hit a ship!\n");

        }
         
     else {
        game[i][j] = 'm';
        printf("You missed.\n");
    }
}


int checktheVictory(char solution[][10], char game[][10]) {
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(solution[i][j] != '0' && game[i][j] != 'X') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    srand(time(NULL)); // seed random number generator with current time
    char solution[10][10];
    char game[10][10];
    fillingBoards(solution);
    buildBoard(game, 'x');
    printf("Welcome to Battleship!\n");
    printf("The board has been filled with ships. You have 50 shots to sink them all!\n");
    printf("There are total of 10 ships on the battleground\n");
    printf("One boat takes 5 space\n");
    printf("Two boat takes 2 space\n");
    printf("Three boat takes 3 space\n");
    printf("Fore boat takes 2 space\n");


    printMatrix(game);
    int shotsRemaining = 50;
    while(shotsRemaining > 0) {
        int i, j;
        printf("Enter the row and column of your next shot (e.g. 3 5): ");
        scanf("%d %d", &i, &j);
        if(i < 0 || i >= 10 || j < 0 || j >= 10) {
            printf("Invalid coordinates. Please try again.\n");
            continue;
        }
        if(game[i][j] != 'x') {
            printf("You already fired at that spot. Please try again.\n");
            continue;
        }
        shoot(solution, game, i, j);
        printMatrix(game);
        if(checktheVictory(solution, game)) {
            printf("Congratulations, you won!\n");
            return 0;
        }
        shotsRemaining--;
        printf("You have %d shots remaining.\n", shotsRemaining);
    }
    printf("Sorry, you lost. Better luck next time!\n");
    return 0;
}

