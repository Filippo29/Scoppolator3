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