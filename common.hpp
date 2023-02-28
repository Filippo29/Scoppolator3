#ifndef BOARD
#define BOARD

typedef struct board{
    char turn;  //0 = white, 1 = black
    char* board;
} board;

#define bIndex(file, rank) (rank<<3)+file
#define black(piece) piece>15 ? piece : piece<<1
#define white(piece) piece>15 ? piece>>1 : piece

#define PAWN 10
#define KNIGHT 11
#define BISHOP 12
#define ROOK 13
#define QUEEN 14
#define KING 15

#endif