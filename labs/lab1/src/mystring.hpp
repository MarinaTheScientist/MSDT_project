#pragma once

class MyString
{
private:
    char *str;
    
public:
    MyString();
    MyString(const char *str);
    MyString(const MyString &other);
    ~MyString();

    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char *str);
    void print();
    void read_line();
};

