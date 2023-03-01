#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "piece.hpp"
#include "game.hpp"
#include "common.hpp"

int main(int argc, char** argv){
    std::cout << sizeof(unsigned char) << "\n";
    Game();
    return 0;
}

Game::Game(){
    this->b = Game::init1();
    Game::print(b);
}

struct board* Game::init1(){
    struct board* b = (struct board*)malloc(sizeof(struct board));
    b->board = (unsigned char*)calloc(64, sizeof(char));

    b->board[bIndex(0, 0)] = white(ROOK);
    b->board[bIndex(1, 0)] = white(KNIGHT);
    b->board[bIndex(2, 0)] = white(BISHOP);
    b->board[bIndex(3, 0)] = white(QUEEN);
    b->board[bIndex(4, 0)] = white(KING);
    b->board[bIndex(5, 0)] = white(BISHOP);
    b->board[bIndex(6, 0)] = white(KNIGHT);
    b->board[bIndex(7, 0)] = white(ROOK);

    for(int file = 0; file < 8; file++)
        b->board[bIndex(file, 1)] = white(PAWN);

    b->board[bIndex(0, 7)] = black(ROOK);
    b->board[bIndex(1, 7)] = black(KNIGHT);
    b->board[bIndex(2, 7)] = black(BISHOP);
    b->board[bIndex(3, 7)] = black(QUEEN);
    b->board[bIndex(4, 7)] = black(KING);
    b->board[bIndex(5, 7)] = black(BISHOP);
    b->board[bIndex(6, 7)] = black(KNIGHT);
    b->board[bIndex(7, 7)] = black(ROOK);

    for(int file = 0; file < 8; file++)
        b->board[bIndex(file, 6)] = black(PAWN);
    return b;
}

void Game::print(struct board* b){
    for(int rank = 7; rank >= 0; rank--){
        for(int file = 0; file < 8; file++){
            std::cout << Piece::toString(b->board[bIndex(file, rank)]) << " ";
        }
        std::cout << "\n";
    }
}

struct board* doMove(){
    
}