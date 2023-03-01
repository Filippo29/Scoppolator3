class Game{
    private:
        struct board* b;
    public:
        Game();
        static struct board* init1();
        static void print(struct board* b);
        struct board* doMove();
};