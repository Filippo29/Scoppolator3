class Game{
    private:
        struct board* b;
    public:
        Game();
        static struct board* init1();
        static void print(struct board* b);
        static void printMoves(struct board* b, struct moves_t* moves);
        struct board* doMove();
};