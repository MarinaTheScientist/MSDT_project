#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main()
{
    {
        Rect r(1, 5, 2, 8);
        assert(r.get_width() == 6);
        assert(r.get_height() == 4);
        assert(r.get_square() == 24);
    }
    {
        Rect r(3, 3, 2, 7);
        assert(r.get_height() == 0);
        assert(r.get_square() == 0);
    }
    {
        Rect r(0, 4, 2, 6);
        r.set_width(10);
        assert(r.get_width() == 10);
        assert(r.get_left() == 2);
        assert(r.get_right() == 12);
        assert(r.get_height() == 4);
    }
    {
        Rect r(0, 4, 2, 6);
        r.set_height(9);
        assert(r.get_height() == 9);
        assert(r.get_bottom() == 0);
        assert(r.get_top() == 9);
        assert(r.get_width() == 4);
    }
    {
        Rect r(0, 1, 0, 1);
        r.set_width(5);
        r.set_height(4);
        assert(r.get_square() == 20);
    }

    std::cout << "test_rect_properties: OK" << std::endl;
    return 0;
}