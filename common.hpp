#ifndef BOARD
#define BOARD

typedef struct board{
    unsigned char* board;
    char turn;  //0 = white, 1 = black
} board;

typedef struct move{
    unsigned char newFile;
    unsigned char newRank;
} move;

typedef struct moves_t{
    struct move* moves;
    int nMoves;
    unsigned char piece;
    unsigned char index;  //initial piece index
} moves_t;

typedef struct bestMove_t{
    struct move* move_sequence;
    double eval;
} bestMove_t;

#define bIndex(file, rank) (rank<<3)+file
#define fileFromIndex(bIndex) bIndex%8
#define rankFromIndex(bIndex) (bIndex>>3)
#define black(piece) piece>15 ? piece : piece<<1
#define white(piece) piece>15 ? piece>>1 : piece

#define PAWN 10
#define KNIGHT 11
#define BISHOP 12
#define ROOK 13
#define QUEEN 14
#define KING 15

#define MAX_DEPTH 5
#define UNSET 9999

#endif