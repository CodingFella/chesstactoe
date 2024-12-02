//
// Created by Jacob Lin on 11/30/24.
//

#include "../chess.h"

#include <stdlib.h>

#define SUCCESS 0
#define SKIPPED 0
#define FAILURE 1

static int checkCaptureMove(const char *move, int expect) {
    if(expect == isCaptureMove(move)) {
        printf(C_GREEN("PASS") ": isCaptureMove \"%s\" == %d\n", move, expect);
        return SUCCESS;
    }
    else {
        printf(C_RED("FAIL") ": isCaptureMove \"%s\" == %d\n", move, expect);
        return FAILURE;
    }
}

static int checkPlacementMove(const char *move, int expect) {
    int result = isPlacementMove(move);
    if(expect == result) {
        printf(C_GREEN("PASS") ": isPlacementMove \"%s\" == %d\n", move, expect);
        return SUCCESS;
    }
    else {
        printf(C_RED("FAIL") ": isPlacementMove \"%s\", %d == %d\n", move, result, expect);
        return FAILURE;
    }
}

static int checkPlacePiece(uint32_t (*board)[SIZE][SIZE], int row, int col, int color, enum Piece piece) {
    int result = placePiece(board, row, col, color, piece);

    if(result == 0) {
        printf(C_YELLOW("SKIP") ": placePiece() failed.\n");
        return SKIPPED;
    }

    enum Piece resultPiece = getPiece(board, row, col);
    int resultColor = getColor(board, row, col);

    if (resultPiece == piece && resultColor == color) {
        printf(C_GREEN("PASS") ": placePiece() resultPiece \"%d\", piece \"%d\", "
               "resultColor \"%d\", color \"%d\"\n",
               resultPiece, piece, resultColor, color);
        return SUCCESS;
    } else if (resultPiece != piece && resultColor != color) {
        printf(C_RED("FAIL") ": placePiece() resultPiece \"%d\", piece \"%d\", "
               "resultColor \"%d\", color \"%d\"\n",
               resultPiece, piece, resultColor, color);
        return FAILURE;
    } else if (resultPiece != piece) {
        printf(C_RED("FAIL") ": placePiece() resultPiece \"%d\", piece \"%d\"\n", resultPiece, piece);
        return FAILURE;
    } else if (resultColor != color) {
        printf(C_RED("FAIL") ": placePiece() resultColor \"%d\", color \"%d\"\n", resultColor, color);
        return FAILURE;
    }

    return -1;
}

static int checkGetColor(uint32_t (*board)[SIZE][SIZE], int row, int col, int expectedColor) {
    int resultColor = getColor(board, row, col);

    if(resultColor == expectedColor) {
        printf(C_GREEN("PASS") ": getWord() resultColor \"%d\" == expectedColor \"%d\"\n", resultColor, expectedColor);
        return SUCCESS;
    } else {
        printf(C_GREEN("FAIL") ": getWord() resultColor \"%d\" != expectedColor \"%d\"\n", resultColor, expectedColor);
        return FAILURE;
    }
}

static int checkGetPiece(uint32_t (*board)[SIZE][SIZE], int row, int col, enum Piece expectedPiece) {
    enum Piece resultPiece = getPiece(board, row, col);

    if(resultPiece == expectedPiece) {
        printf(C_GREEN("PASS") ": getPiece() resultPiece \"%d\" == expectedPiece \"%d\"\n", resultPiece, expectedPiece);
        return SUCCESS;
    } else {
        printf(C_GREEN("FAIL") ": getPiece() resultPiece \"%d\" != expectedPiece \"%d\"\n", resultPiece, expectedPiece);
        return FAILURE;
    }
}

int main(void) {
    int fails = 0;

    {
        const char *move;
        int expect;

        move = "Rxd4";
        expect = 1;
        fails += checkCaptureMove(move, expect);

        move = "Rd4";
        expect = 0;
        fails += checkCaptureMove(move, expect);
    }

    {
        char *move;
        int expect;

        move = "R@d4";
        expect = 1;
        fails += checkPlacementMove(move, expect);

        move = "Rd4";
        expect = 0;
        fails += checkPlacementMove(move, expect);
    }

    {
        uint32_t board[SIZE][SIZE] = { { EMPTY } };

        int row;
        int col;
        int color;
        enum Piece piece;

        row = 3;
        col = 4;
        color = BLACK;
        piece = KING;

        checkPlacePiece(&board, row, col, color, piece);

        // place another piece

        piece = ROOK;
        color = WHITE;

        checkPlacePiece(&board, row, col, color, piece);
    }

    {
        uint32_t board[SIZE][SIZE] = { { EMPTY } };

        int row;
        int col;
        int color;
        enum Piece piece;

        // check empty
        row = 7;
        col = 6;
        color = EMPTY_GRID;

        checkGetColor(&board, row, col, color);

        // check black
        row = 7;
        col = 5;
        color = WHITE;
        piece = QUEEN;

        placePiece(&board, row, col, color, piece);
        checkGetColor(&board, row, col, color);

        // check black
        row = 7;
        col = 2;
        color = BLACK;
        piece = ROOK;

        placePiece(&board, row, col, color, piece);
        checkGetColor(&board, row, col, color);
    }

    {
        uint32_t board[SIZE][SIZE] = { { EMPTY } };

        int row;
        int col;
        int color;
        enum Piece piece;

        // check empty
        row = 7;
        col = 6;
        color = EMPTY_GRID;
        piece = EMPTY;

        checkGetPiece(&board, row, col, piece);

        // check black
        row = 7;
        col = 5;
        color = WHITE;
        piece = QUEEN;

        placePiece(&board, row, col, color, piece);
        checkGetPiece(&board, row, col, piece);

        // check black
        row = 7;
        col = 2;
        color = BLACK;
        piece = ROOK;

        placePiece(&board, row, col, color, piece);
        checkGetPiece(&board, row, col, piece);
    }

    return fails ? EXIT_FAILURE : EXIT_SUCCESS;
}