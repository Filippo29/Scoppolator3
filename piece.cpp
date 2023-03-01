#include <string>
#include <iostream>

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

void Piece::addMove(struct moves_t* moves, int* currentLimit, struct move* newMove){
    if((*currentLimit) == moves->nMoves + 1){
        moves->moves = (struct move*)realloc(moves->moves, *(currentLimit)+50);
        (*currentLimit) += 50;
    }
    moves->moves[moves->nMoves] = (*newMove);
    moves->nMoves++;
    free(newMove);
}

struct moves_t* Piece::getMoves(struct board* b, unsigned char index){
    struct moves_t* moves = (struct moves_t*)malloc(sizeof(struct moves_t));
    moves->nMoves = 0;
    moves->piece = white(b->board[index]);

    int currentLimit = 50;
    moves->moves = (struct move*)malloc(currentLimit*sizeof(struct move));

    unsigned char file = fileFromIndex(index);
    unsigned char rank = rankFromIndex(index);
    moves->index = index;
    bool isWhite = b->board[index] == white(b->board[index]);

    switch (white(b->board[index]))
    {
        case PAWN: {
            char direction = isWhite ? 1 : -1;
            if(!b->board[bIndex(file, (rank+direction))]){
                struct move* newMove = (struct move*)malloc(sizeof(struct move));
                newMove->newFile = file;
                newMove->newRank = rank+direction;
                addMove(moves, &currentLimit, newMove);
                if(((isWhite && rank==1) || (!isWhite && rank==6)) && !b->board[bIndex(file, (rank+(direction<<1)))]){
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file;
                    newMove->newRank = rank+2*direction;
                    addMove(moves, &currentLimit, newMove);
                }
            }
            if(file+1 < 8 && b->board[bIndex(file+1, (rank+direction))] && (b->board[bIndex(file+1, (rank+direction))] == white(b->board[bIndex(file+1, (rank+direction))])) != isWhite){
                struct move* newMove = (struct move*)malloc(sizeof(struct move));
                newMove->newFile = file+1;
                newMove->newRank = rank+direction;
                addMove(moves, &currentLimit, newMove);
            }
            if(file-1 > -1 && b->board[bIndex(file-1, (rank+direction))] && (b->board[bIndex(file-1, (rank+direction))] == white(b->board[bIndex(file-1, (rank+direction))])) != isWhite){
                struct move* newMove = (struct move*)malloc(sizeof(struct move));
                newMove->newFile = file-1;
                newMove->newRank = rank+direction;
                addMove(moves, &currentLimit, newMove);
            }
            break;
        }
        case BISHOP:{
            int i;
            bool flag;  //true if there's a piece on the selected square
            bool flag2;  //true if the piece on the selected square is same color as the moving piece
            bool tmp;  //true if the piece on the selected square is white
            for(i = 1; i < 8 && file + i < 8 && rank + i < 8; i++){
                flag = b->board[index+9*i];
                tmp = (b->board[index+9*i] == (white(b->board[index+9*i])));
                flag2 = (isWhite == tmp);
                if(flag && flag2)
                    break;
                if(!flag){
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file+i;
                    newMove->newRank = rank+i;
                    addMove(moves, &currentLimit, newMove);
                } else if(flag && !flag2) {
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file+i;
                    newMove->newRank = rank+i;
                    addMove(moves, &currentLimit, newMove);
                    break;
                }
            }
            for(i = 1; i < 8 && file - i > -1 && rank + i < 8; i++){
                flag = b->board[index+7*i];
                tmp = (b->board[index+7*i] == (white(b->board[index+7*i])));
                flag2 = (isWhite == tmp);
                if(flag && flag2)
                    break;
                if(!flag){
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file-i;
                    newMove->newRank = rank+i;
                    addMove(moves, &currentLimit, newMove);
                } else if(flag && !flag2) {
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file-i;
                    newMove->newRank = rank+i;
                    addMove(moves, &currentLimit, newMove);
                    break;
                }
            }
            for(i = 1; i < 8 && file - i > -1 && rank - i > -1; i++){
                flag = b->board[index-9*i];
                tmp = (b->board[index-9*i] == (white(b->board[index-9*i])));
                flag2 = (isWhite == tmp);
                if(flag && flag2)
                    break;
                if(!flag){
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file-i;
                    newMove->newRank = rank-i;
                    addMove(moves, &currentLimit, newMove);
                } else if(flag && !flag2) {
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file-i;
                    newMove->newRank = rank-i;
                    addMove(moves, &currentLimit, newMove);
                    break;
                }
            }
            for(i = 1; i < 8 && file + i < 8 && rank - i > -1; i++){
                flag = b->board[index-7*i];
                tmp = (b->board[index-7*i] == (white(b->board[index-7*i])));
                flag2 = (isWhite == tmp);
                if(flag && flag2)
                    break;
                if(!flag){
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file+i;
                    newMove->newRank = rank-i;
                    addMove(moves, &currentLimit, newMove);
                } else if(flag && !flag2) {
                    std::cout << "diocane" << file+i << ", " << rank-i << "\n";
                    struct move* newMove = (struct move*)malloc(sizeof(struct move));
                    newMove->newFile = file+i;
                    newMove->newRank = rank-i;
                    addMove(moves, &currentLimit, newMove);
                    break;
                }
            }
            break;
        }
        case KNIGHT:{
            break;
        }
        case ROOK:{
            break;
        }
        case QUEEN:{
            break;
        }
        case KING:{
            break;
        }
        default:{
            break;
        }
    }
    return moves;
}