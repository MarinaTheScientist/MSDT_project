#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main()
{
    {
        Rect r1(0, 2, 0, 2);
        Rect r2(5, 8, 6, 9);
        Rect b = bounding_rect(r1, r2);
        assert(b.get_left() == 0);
        assert(b.get_right() == 9);
        assert(b.get_bottom() == 0);
        assert(b.get_top() == 8);
    }
    {
        Rect outer(0, 10, 0, 10);
        Rect inner(2, 5, 3, 6);
        Rect b = bounding_rect(outer, inner);
        assert(b.get_left() == 0);
        assert(b.get_right() == 10);
        assert(b.get_bottom() == 0);
        assert(b.get_top() == 10);
    }
    {
        Rect r(1, 4, 2, 7);
        Rect b = bounding_rect(r, r);
        assert(b.get_left() == 2);
        assert(b.get_right() == 7);
        assert(b.get_bottom() == 1);
        assert(b.get_top() == 4);
    }
    {
        Rect r1(5, 1, 8, 2);
        Rect r2(0, 3, 0, 3);
        Rect b = bounding_rect(r1, r2);
        assert(b.get_left() == 0);
        assert(b.get_right() == 8);
        assert(b.get_bottom() == 0);
        assert(b.get_top() == 5);
    }

    std::cout << "test_bounding_rect: OK" << std::endl;
    return 0;
}