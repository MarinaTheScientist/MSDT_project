class Rect{
    private:
    int x, y, width, height;
    //int top, right, bottom, left;
    public:
    Rect();
    Rect(int bottom, int top, int left, int right);
    // Rect(int x, int y, int width, int height);
    Rect(const Rect &other);
    ~Rect();

    int get_top();
    int get_left();
    int get_bottom();
    int get_right();
    // int get_x();
    // int get_y();
    void set_all(int bottom, int top, int left, int right);
    // void set_all(int x, int y, int width, int height);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_bottom, int d_top, int d_left, int d_right);

    void move(int dx, int dy);

    int get_width();
    int get_height();
    int get_square();

    void set_width(int width);
    void set_height(int height);
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);



