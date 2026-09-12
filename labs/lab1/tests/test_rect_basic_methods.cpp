#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main()
{
    {
        Rect r;
        assert(r.get_bottom() == 0);
        assert(r.get_top() == 0);
        assert(r.get_left() == 0);
        assert(r.get_right() == 0);
    }

    {
        Rect r(1, 5, 2, 8);
        assert(r.get_bottom() == 1);
        assert(r.get_top() == 5);
        assert(r.get_left() == 2);
        assert(r.get_right() == 8);
    }

    {
        Rect r(-4, -1, -6, -2);
        assert(r.get_bottom() == -4);
        assert(r.get_top() == -1);
        assert(r.get_left() == -6);
        assert(r.get_right() == -2);
    }

    {
        Rect original(3, 7, 1, 9);
        Rect copy(original);
        assert(copy.get_bottom() == original.get_bottom());
        assert(copy.get_top() == original.get_top());
        assert(copy.get_left() == original.get_left());
        assert(copy.get_right() == original.get_right());
    }

    {
        Rect original(0, 10, 0, 10);
        Rect copy(original);
        original.set_all(1, 2, 3, 4);
        assert(copy.get_bottom() == 0);
        assert(copy.get_top() == 10);
        assert(copy.get_left() == 0);
        assert(copy.get_right() == 10);
    }

    {
        Rect r;
        r.set_all(2, 6, 3, 9);
        assert(r.get_bottom() == 2);
        assert(r.get_top() == 6);
        assert(r.get_left() == 3);
        assert(r.get_right() == 9);
    }

    {
        Rect r(1, 1, 1, 1);
        r.set_all(0, 4, 0, 4);
        r.set_all(-2, 2, -3, 3);
        assert(r.get_bottom() == -2);
        assert(r.get_top() == 2);
        assert(r.get_left() == -3);
        assert(r.get_right() == 3);
    }

    std::cout << "test_rect_basic_methods: OK" << std::endl;
    return 0;
}
