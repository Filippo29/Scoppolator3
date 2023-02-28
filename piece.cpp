#include <string>

#include "piece.hpp"
#include "common.hpp"

std::string Piece::toString(char piece){
    bool black = false;
    if(piece > 15){
        piece = piece >> 1;
        black = true;
    }
    if(piece == PAWN)
        return black ? "p" : "P";
    if(piece == ROOK)
        return black ? "r" : "R";
    if(piece == KNIGHT)
        return black ? "n" : "N";
    if(piece == BISHOP)
        return black ? "b" : "B";
    if(piece == QUEEN)
        return black ? "q" : "Q";
    if(piece == KING)
        return black ? "k" : "K";
    return " ";
}