#pragma once
#include <iostream>

class MyString
{
private:
    char *str;
    
public:
    MyString();
    MyString(const char *str);
    MyString(const MyString &other);
    ~MyString();
    MyString(MyString &&other) noexcept;
    MyString& operator=(MyString &&other) noexcept;
    const char *c_str() const;
    MyString& operator=(const MyString &other);
    MyString& operator+=(const MyString &other);

    char& operator[](int i);
    char operator[](int i) const;

    friend std::istream& operator>>(std::istream &is, MyString &s);

    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char *str);
    void print() const;
    void read_line();
};
MyString operator+(const MyString &left, const MyString &right);

bool operator==(const MyString &a, const MyString &b);
bool operator!=(const MyString &a, const MyString &b);
bool operator<(const MyString &a, const MyString &b);
bool operator<=(const MyString &a, const MyString &b);

std::ostream& operator<<(std::ostream &os, const MyString &s);

