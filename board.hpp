class Board{
    private:
        struct board* b;
    public:
        Board();
        static struct board* init1();
        static void print(struct board* b);
};