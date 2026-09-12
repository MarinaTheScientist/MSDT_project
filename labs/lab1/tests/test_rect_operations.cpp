#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main()
{
    {
        Rect r(0, 4, 0, 6);
        r.move(3, 2);
        assert(r.get_left() == 3);
        assert(r.get_right() == 9);
        assert(r.get_bottom() == 2);
        assert(r.get_top() == 6);
        assert(r.get_width() == 6);
        assert(r.get_height() == 4);
    }
    {
        Rect r(0, 4, 0, 6);
        r.move(-2, -3);
        assert(r.get_left() == -2);
        assert(r.get_bottom() == -3);
    }
    {
        Rect r(2, 6, 2, 6);
        r.inflate(1);
        assert(r.get_left() == 1);
        assert(r.get_right() == 7);
        assert(r.get_bottom() == 1);
        assert(r.get_top() == 7);
    }
    {
        Rect r(0, 4, 0, 4);
        r.inflate(2, 1);
        assert(r.get_left() == -2);
        assert(r.get_right() == 6);
        assert(r.get_bottom() == -1);
        assert(r.get_top() == 5);
    }
    {
        Rect r(0, 10, 0, 10);
        r.inflate(1, 2, 3, 4);
        assert(r.get_bottom() == -1);
        assert(r.get_top() == 12);
        assert(r.get_left() == -3);
        assert(r.get_right() == 14);
    }
    {
        Rect r(0, 10, 0, 10);
        r.inflate(-2);
        assert(r.get_left() == 2);
        assert(r.get_right() == 8);
    }

    std::cout << "test_rect_operations: OK" << std::endl;
    return 0;
}