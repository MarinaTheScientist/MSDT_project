#pragma once
#include <iostream>

class BoolArray
{
private:
    unsigned char *data;
    int n;

    static int bytes_for(int n);
    bool get_bit(int i) const;
    void set_bit(int i, bool value);

public:
    class Reference
    {
    private:
        unsigned char *byte;
        unsigned char mask;

        Reference(unsigned char *byte, unsigned char mask);
        friend class BoolArray;

    public:
        operator bool() const;
        Reference& operator=(bool value);
        Reference& operator=(const Reference &other);
    };

    explicit BoolArray(int n, bool value = false);
    BoolArray(const BoolArray &other);
    BoolArray(BoolArray &&other) noexcept;
    ~BoolArray();

    BoolArray& operator=(const BoolArray &other);
    BoolArray& operator=(BoolArray &&other) noexcept;

    int size() const;
    void resize(int new_size, bool value = false);

    Reference operator[](int i);
    bool operator[](int i) const;
};

std::ostream& operator<<(std::ostream &os, const BoolArray &array);