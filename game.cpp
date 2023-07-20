#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <map>

#include "piece.hpp"
#include "game.hpp"
#include "common.hpp"

int main(int argc, char** argv){
    Game();
    return 0;
}

Game::Game(){
    //struct board* bb = getFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    struct board* fork = getFromFEN("4k3/8/8/5q2/4N3/8/3P4/4K3 w - - 0 1");
    //this->b = Game::init1();
    this->b = fork;
    struct moves_t* m = Piece::getMoves(this->b, bIndex(3, 4));
    Game::printMoves(this->b, m);
    Game::print(this->b);
    doMove(this->b, m, 0);
    //std::cout << evaluate(this->b);
    bestMove_t* bm = findBest(this->b);
    std::cout << std::endl << "Evaluation after " << bm->move_sequence[0].newFile << "," << bm->move_sequence[0].newRank << ": " << bm->eval;
    //Game::print(b);
}

struct board* Game::init1(){
    struct board* b = (struct board*)malloc(sizeof(struct board));
    b->board = (unsigned char*)calloc(64, sizeof(unsigned char));
    b->turn = 0; //white's turn

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

    //b->board[bIndex(4, 2)] = black(QUEEN);
    b->board[bIndex(4, 3)] = white(KNIGHT);

    for(int file = 0; file < 8; file++)
        b->board[bIndex(file, 6)] = black(PAWN);
    return b;
}

struct board* Game::getFromFEN(std::string FEN){
    std::string s1 = FEN.substr(0, FEN.find(" "));
    std::string s2 = FEN.substr(FEN.find(" ")+1, FEN.length());

    struct board* b = (struct board*)malloc(sizeof(struct board));
    b->board = (unsigned char*)calloc(64, sizeof(char));
    std::string ns = "";
    int rankN = 0;
    for(int i = 0; i < s1.length(); i++){
        if(s1.at(i) == '/'){
            int spaces = 0;
            for(int y = 0; y < ns.length(); y++){
                if(isdigit(ns.at(y))){
                    int nspace = ns.at(y) - 48;
                    std::cout << std::endl << nspace;
                    for(int z = 0; z < nspace; z++){
                        b->board[bIndex(y+z+spaces, (7-rankN))] = 0;
                    }
                    spaces += nspace;
                }else{
                    b->board[bIndex(y+spaces, (7-rankN))] = Piece::toChar(ns.at(y));
                }
            }
            ns = "";
            rankN++;
        }else{
            ns += s1.at(i);
        }
    }
    for(int y = 0; y < ns.length(); y++){
        if(isdigit(ns.at(y))){
            int nspace = ns.at(y) - 48;
            for(int z = 0; z < nspace; z++){
                b->board[bIndex(y, (7-rankN))] = 0;
                y++;
            }
        }else{
            b->board[bIndex(y, (7-rankN))] = Piece::toChar(ns.at(y));
        }
    }
    
    if(s2.at(0) == 'w')
        b->turn = 0;
    else
        b->turn = 1;
    
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

double Game::evaluate(struct board* b){
    double eval = 0.0;
    int isWhite;
    std::map<unsigned char, double> values;
    values[PAWN] = 1.0;
    values[KNIGHT] = 3.0;
    values[BISHOP] = 3.0;
    values[ROOK] = 5.0;
    values[QUEEN] = 9.0;
    values[KING] = 0.0;
    
    for(int i = 0; i < 64; i++){
        if(b->board[i] == (white(b->board[i])))
            isWhite = 1;
        else
            isWhite = -1;
        
        eval += isWhite*values[white(b->board[i])];
    }
    return eval;
}

bestMove_t* Game::findBest(struct board* b){
    bestMove_t* ret = (struct bestMove_t*)malloc(sizeof(bestMove_t));
    ret->move_sequence = (struct move*)malloc(MAX_DEPTH*sizeof(move));
    double ev = findBestMove(b, ret->move_sequence, 0);
    return ret;
}

char Game::isBest(double eval, double oldEval, char turn){
    if(turn) // black's turn
        return eval < oldEval;
    else // white's turn
        return oldEval > eval;
}

double Game::findBestMove(struct board* b, struct move* move_sequence, int depth){
    double bestEval = UNSET;
    move bestMove;
    if(depth>=MAX_DEPTH){
        for(int i = 0; i < 64; i++){
            if(b->turn == Piece::getColorTurn(b->board[i])){
                moves_t* legalMoves = Piece::getMoves(b, i);
                for(int y = 0; y < legalMoves->nMoves; y++){
                    board* nb = doMove(b, legalMoves, y);
                    nb->turn = !b->turn;
                    double eval = evaluate(nb);
                    if(bestEval == UNSET || isBest(eval, bestEval, b->turn)){
                        bestEval = eval;
                        bestMove = legalMoves->moves[y];
                    }
                }
            }
        }
        move_sequence[depth] = bestMove;
        return bestEval;
    } else {
        for(int i = 0; i < 64; i++){
            if(b->turn == Piece::getColorTurn(b->board[i])){
                moves_t* legalMoves = Piece::getMoves(b, i);
                for(int y = 0; y < legalMoves->nMoves; y++){
                    board* nb = doMove(b, legalMoves, y);
                    nb->turn = !b->turn;
                    double eval = Game::findBestMove(nb, move_sequence, depth+1);
                    if(bestEval == UNSET || isBest(eval, bestEval, b->turn)){
                        bestEval = eval;
                        bestMove = legalMoves->moves[y];
                    }
                }
            }
        }
        move_sequence[depth] = bestMove;
        return bestEval;
    }
}

void Game::printMoves(struct board* b, struct moves_t* moves){
    std::cout << "Number of legal moves: " << moves->nMoves << "\n";
    for(int i = 0; i < moves->nMoves; i++){
        unsigned char isCapture = (b->board[bIndex(moves->moves[i].newFile, moves->moves[i].newRank)] != 0);
        switch(moves->piece){
            case PAWN: {
                if(!isCapture)
                    std::cout << (char)(97+(int)fileFromIndex(moves->index)) << (int)moves->moves[i].newRank+1;
                else
                    std::cout << (char)(97+(int)fileFromIndex(moves->index)) << "x" << (char)(97+(int)moves->moves[i].newFile) << (int)moves->moves[i].newRank+1;
                break;
            }
            default:{
                if(!isCapture)
                    std::cout << Piece::toString(moves->piece) << (char)(97+moves->moves[i].newFile) << (int)moves->moves[i].newRank+1;
                else
                    std::cout << Piece::toString(moves->piece) << "x" << (char)(97+(int)moves->moves[i].newFile) << (int)moves->moves[i].newRank+1;
                break;
            }
        }
        std::cout << "\n";
    }
}

struct board* Game::doMove(struct board* b, struct moves_t* ms, int i){
    struct board* nBoard = (struct board*)malloc(sizeof(struct board));
    nBoard->board = (unsigned char*)calloc(64, sizeof(unsigned char));
    struct move m = ms->moves[i];
    memcpy(nBoard->board, b->board, 64*sizeof(unsigned char));
    nBoard->board[bIndex(m.newFile, m.newRank)] = ms->piece;
    nBoard->board[ms->index] = 0;
    return nBoard;
}