#include <string>

#include "piece.hpp"
#include "common.hpp"

std::string Piece::toString(char piece){
    bool black = false;
    if(piece > 15){
        piece = piece >> 1;
        black = true;
    }

    switch(piece){
        case PAWN:
            return black ? "p" : "P";
        case ROOK:
            return black ? "r" : "R";
        case KNIGHT:
            return black ? "n" : "N";
        case BISHOP:
            return black ? "b" : "B";
        case QUEEN:
            return black ? "q" : "Q";
        case KING:
            return black ? "k" : "K";
        default:
            return " ";
    }
}

void Piece::addMove(struct move* moves, int* nMoves, int* currentLimit, struct move* newMove){
    if(currentLimit == nMoves + 1){
        moves = (struct move*)realloc(moves, *(currentLimit)+50);
        (*currentLimit) += 50;
    }
    moves[*(nMoves)] = (*newMove);
    free(newMove);
}

struct move* Piece::getMoves(struct board*){
    struct move* moves = (struct move*)malloc(50*sizeof(struct move));
    int currentLimit = 50;
    int nMoves = 0;


}