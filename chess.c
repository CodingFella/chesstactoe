//
// Created by Jacob Lin on 11/29/24.
//

#include "chess.h"

static char *whitePieces[] = {"x", "P", "K", "Q", "B", "N", "R"};
static char *blackPieces[] = {"x", "p", "k", "q", "b", "n", "r"};

static int currentTurn = WHITE;

void printBoard(uint32_t (*board)[SIZE][SIZE]) {
    int i, j;
    char starter = 'a';

    // print header
    printf("  ");
    for(i = 0; i < SIZE; i++) {
        printf("%c ", starter + i);
    }
    printf(" \n");

    // print main board
    for(i = 0; i < SIZE; i++) {
        // left side numbers
        printf("%d ", SIZE - i);
        for(j = 0; j < SIZE; j++) {
            uint32_t current = (*board)[i][j];

            uint32_t color = (current & (1 << 3)) >> 3;
            uint32_t piece = current & (7);

            char boardPiece = 'x';

            // empty piece
            if(piece == EMPTY) {
                printf("%c ", boardPiece);
            }
            // white piece
            else if(color == WHITE) {
                boardPiece = *(whitePieces[piece]);
                printf(C_BLUE("%c "), boardPiece);
            }
            // black piece
            else {
                boardPiece = *(blackPieces[piece]);
                printf(C_RED("%c "), boardPiece);
            }
        }

        // right side numbers
        printf("%d\n", SIZE - i);
    }

    // print footer
    printf("  ");
    for(i = 0; i < SIZE; i++) {
        printf("%c ", starter + i);
    }
    printf(" \n");
}

enum Piece getPiece(uint32_t (*board)[SIZE][SIZE], int row, int col) {
    if(row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
        return -1;
    }

    uint32_t selected = (*board)[row][col];

    return (selected & 7);
}

// check if the move string contains an 'x', denoting a capture
int isCaptureMove(const char move[MAX_MOVE_LENGTH]) {
    int i;
    for(i = 0; i < MAX_MOVE_LENGTH; i++) {
        if(move[i] == 'x') {
            return 1;
        }
        if(move[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

// check if the move string contains an 'x', denoting a capture
int isPlacementMove(const char move[MAX_MOVE_LENGTH]) {
    int i;
    for(i = 0; i < MAX_MOVE_LENGTH; i++) {
        if(move[i] == '@') {
            return 1;
        }
        if(move[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

// -1 for empty. 0 is white and 1 is black (#define)
int getColor(uint32_t (*board)[SIZE][SIZE], int row, int col) {
    if(row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
        return -1;
    }

    int selected = (int)(*board)[row][col];

    if(getPiece(board, row, col) != EMPTY) {
        return (selected & (1 << 3)) >> 3;
    }

    return -1;
}

// return 1 for success, 0 for failure
int placePiece(uint32_t (*board)[SIZE][SIZE], int row, int col, int color, enum Piece piece) {
    if(row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return 0;
    }

    if((*board)[row][col] != EMPTY) {
        return 0;
    }

    uint32_t pieceToPlace = 0;

    pieceToPlace += piece;
    pieceToPlace += color << COLOR_OFFSET;

    (*board)[row][col] = pieceToPlace;

    return 1;
}

int movePiece(uint32_t (*board)[SIZE][SIZE], int row, int col, int disambiguateRow, int disambiguateCol) {

}

// return 0 for invalid move. 1 for valid move.
int makeMove(uint32_t (*board)[SIZE][SIZE], const char move[MAX_MOVE_LENGTH]) {
    char pieceChar = move[0];
    enum Piece current;

    size_t len = strlen(move);

    int moveRow;
    int moveCol;

    if(len < 2) {
        return 0;
    }

    // extract piece
    if(pieceChar >= 'a' && pieceChar <= 'h') {
        current = PAWN;
    } else if(pieceChar == 'K') {
        current = KING;
    } else if(pieceChar == 'Q') {
        current = QUEEN;
    } else if(pieceChar == 'B') {
        current = BISHOP;
    } else if(pieceChar == 'N') {
        current = KNIGHT;
    } else if(pieceChar == 'R') {
        current = ROOK;
    } else {
        current = EMPTY;
    }

    // extract row/col of extraction
    // TODO: verify that the last character is (1-8) and second to last character is (a-h)
    moveCol = move[len-2] - 'a';
    moveRow = '8' - move[len-1];



    // check if col and row make sense
    if(moveCol < 0 || moveCol >= SIZE || moveRow < 0 || moveRow >= SIZE) {
        return 0;
    }

    if(isPlacementMove(move)) {
        if(placePiece(board, moveRow, moveCol, currentTurn, current)) {
            currentTurn = !currentTurn;
            return 1;
        } else {
            return 0;
        }
    }

    // contains disambiguating move
    if(len >= 4) {

    }

    printf("You are trying to move a: %d to column: %d and row: %d\n", current, moveCol, moveRow);
    printf("Piece is color: %d\n", getColor(board, moveRow, moveCol));



    return 1;
}




