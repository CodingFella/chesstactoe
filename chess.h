//
// Created by Jacob Lin on 11/30/24.
//

#ifndef CHESSTACTOE_CHESS_H
#define CHESSTACTOE_CHESS_H


#include <stdio.h>
#include <string.h>
#include <stdint.h>


#define SIZE 8
#define EMPTY_GRID (-1)
#define WHITE 0
#define BLACK 1
#define COLOR_OFFSET 3
#define MAX_MOVE_LENGTH 10

#define C_RED(s)     "\033[31;1m" s "\033[0m"
#define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#define C_BLUE(s)   "\033[34;1m" s "\033[0m"
#define C_YELLOW(s)  "\033[33;1m" s "\033[0m"
#define C_MAGENTA(s) "\033[35;1m" s "\033[0m"

enum Piece {EMPTY, PAWN, KING, QUEEN, BISHOP, KNIGHT, ROOK};

void printBoard(uint32_t (*board)[SIZE][SIZE]);
enum Piece getPiece(uint32_t (*board)[SIZE][SIZE], int row, int col);
int isCaptureMove(const char move[MAX_MOVE_LENGTH]);
int isPlacementMove(const char move[MAX_MOVE_LENGTH]);
int placePiece(uint32_t (*board)[SIZE][SIZE], int row, int col, int color, enum Piece piece);
int getColor(uint32_t (*board)[SIZE][SIZE], int row, int col);
int movePiece(uint32_t (*board)[SIZE][SIZE], int row, int col, int disambiguateRow, int disambiguateCol);
int makeMove(uint32_t (*board)[SIZE][SIZE], const char move[MAX_MOVE_LENGTH]);


#endif //CHESSTACTOE_CHESS_H
