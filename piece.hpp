#ifndef PIECE
#define PIECE

#include <string>

class Piece{
    private:
        static void addMove(struct moves_t* moves,  int* currentLimit, struct move* newMove);
    public:
        static std::string toString(char piece);
        static char getColorTurn(char piece);
        static unsigned char toChar(char piece);
        static struct moves_t* getMoves(struct board* b, unsigned char bIndex);
};

#endif