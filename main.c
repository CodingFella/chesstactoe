#include "chess.h"

int main(void) {
    uint32_t board[SIZE][SIZE] = { { EMPTY } };



    while(1) {
        printBoard(&board);

        char move[MAX_MOVE_LENGTH];

        printf("\n");
        printf("It's your move: ");
        scanf("%s", move);
        printf("\n");

        makeMove(&board, move);

        if(strcmp(move, "exit") == 0) {
            break;
        }

        printf("You entered: %s\n", move);
    }

    return 0;
}
