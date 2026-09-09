#pragma once

#include "mystring.hpp"

class TextWrapper{
private:
    int max_width;
    const MyString  &input_text;

    int current_index;
    int current_line_len;

    bool is_end() const;
    MyString get_next_word();

public:
    TextWrapper(const MyString &input, int line_width);
    void print_wrapped();
    
};