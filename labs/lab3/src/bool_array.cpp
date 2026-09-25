#include "bool_array.hpp"
#include <stdexcept>

using namespace std;

int BoolArray::bytes_for(int n){
    return (n + 7) / 8;
}

bool BoolArray::get_bit(int i) const {
    return (data[i / 8] >> (i % 8)) & 1;
}

void BoolArray::set_bit(int i, bool value){
    unsigned char mask = 1 << (i % 8);
    if (value){
        data[i / 8] |= mask;
    }
    else{
        data[i / 8] &= ~mask;
    }
}

BoolArray::Reference::Reference(unsigned char *byte, unsigned char mask)
    : byte(byte), mask(mask) {}

BoolArray::Reference::operator bool() const {
    return (*byte & mask) != 0;
}

BoolArray::Reference& BoolArray::Reference::operator=(bool value){
    if (value){
        *byte |= mask;
    }
    else{
        *byte &= ~mask;
    }
    return *this;
}

BoolArray::Reference& BoolArray::Reference::operator=(const Reference &other){
    return *this = bool(other);
}

BoolArray::BoolArray(int n, bool value) : data(nullptr), n(0) {
    if (n < 0){
        throw invalid_argument("BoolArray: negative size");
    }
    resize(n, value);
}

BoolArray::BoolArray(const BoolArray &other) : data(nullptr), n(other.n) {
    int bytes = bytes_for(n);
    if (bytes > 0){
        data = new unsigned char[bytes];
        for (int i = 0; i < bytes; i++){
            data[i] = other.data[i];
        }
    }
}

BoolArray::BoolArray(BoolArray &&other) noexcept : data(other.data), n(other.n) {
    other.data = nullptr;
    other.n = 0;
}

BoolArray::~BoolArray(){
    delete[] data;
}

BoolArray& BoolArray::operator=(const BoolArray &other){
    if (this != &other){
        BoolArray tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

BoolArray& BoolArray::operator=(BoolArray &&other) noexcept {
    if (this != &other){
        delete[] data;
        data = other.data;
        n = other.n;
        other.data = nullptr;
        other.n = 0;
    }
    return *this;
}

int BoolArray::size() const {
    return n;
}

void BoolArray::resize(int new_size, bool value){
    if (new_size < 0){
        throw invalid_argument("BoolArray: negative size");
    }
    int bytes = bytes_for(new_size);
    unsigned char *new_data = nullptr;
    if (bytes > 0){
        new_data = new unsigned char[bytes]();
    }

    unsigned char *old_data = data;
    int old_n = n;
    data = new_data;
    n = new_size;

    for (int i = 0; i < new_size; i++){
        if (i < old_n){
            set_bit(i, (old_data[i / 8] >> (i % 8)) & 1);
        }
        else{
            set_bit(i, value);
        }
    }
    delete[] old_data;
}

BoolArray::Reference BoolArray::operator[](int i){
    if (i < 0 || i >= n){
        throw out_of_range("BoolArray: index out of range");
    }
    return Reference(&data[i / 8], 1 << (i % 8));
}

bool BoolArray::operator[](int i) const {
    if (i < 0 || i >= n){
        throw out_of_range("BoolArray: index out of range");
    }
    return get_bit(i);
}

ostream& operator<<(ostream &os, const BoolArray &array){
    os << "[";
    for (int i = 0; i < array.size(); i++){
        if (i > 0){
            os << ", ";
        }
        os << array[i];
    }
    os << "]";
    return os;
}