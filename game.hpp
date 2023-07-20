class Game{
    private:
        struct board* b;
    public:
        Game();
        static struct board* init1();
        static struct board* getFromFEN(std::string FEN);
        static void print(struct board* b);
        static void printMoves(struct board* b, struct moves_t* moves);
        static double evaluate(struct board* b);
        static struct bestMove_t* findBest(struct board* b);
        static char isBest(double eval, double oldEval, char turn);
        static double findBestMove(struct board* b, struct move* move_sequence, int depth);
        static struct board* doMove(struct board* b, struct moves_t* m, int i);
};