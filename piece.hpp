#ifndef PIECE
#define PIECE

#include <string>

class Piece{
    private:
        static void addMove(struct move* moves, int* nMoves,  int* currentLimit, struct move* newMove);
    public:
        static std::string toString(char piece);
        static struct move* getMoves(struct board* b, unsigned char bIndex);
};

#endif