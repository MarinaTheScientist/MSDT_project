#include "mystring.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

MyString::MyString(){
    str = new char[1]{'\0'};
}

MyString::MyString(const char *str){
    this->str = new char[strlen(str)+1];
    strcpy(this->str, str);

}

MyString::MyString(const MyString &other){
    int len = strlen(other.str);
    str = new char[len + 1];
    strcpy(str, other.str);
}

void MyString::set_new_string(const char *str){
    delete[] this->str;
    this->str = new char[strlen(str)+1];
    strcpy(this->str, str);
}

MyString::~MyString(){
    delete[] str;
}

char MyString::get(int i) const {
    if (i < 0 || i >= (int)strlen(str)){return 0;}
    return str[i];
}

void MyString::set(int i, char c){
    if (i < 0 || i >= (int)strlen(str)){return;}
    str[i] = c;
}

void MyString::print() const {
    cout << str << "\n";
}

void MyString::read_line(){
    delete[] str;
    int n = 10;
    char *str = new char[n];
    int i = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        str[i++] = c;

        if (i == n){
            char *temp = new char[2*n];
            for (int j = 0; j < n; j++){
                temp[j] = str[j];
            }
            delete[] str;
            str = temp;
            n *= 2;
        }
    }
    str[i] = '\0';
    this->str = str;
}

MyString& MyString::operator=(const MyString &other){
    if (this == &other){
        return *this;
    }
    char *tmp = new char[strlen(other.str) + 1];
    strcpy(tmp, other.str);
    delete[] str;
    str = tmp;
    return *this;
}

MyString& MyString::operator+=(const MyString &other){
    int len1 = strlen(c_str());
    int len2 = strlen(other.c_str());
    char *tmp = new char[len1 + len2 + 1];
    strcpy(tmp, c_str());
    strcpy(tmp + len1, other.c_str());
    delete[] str;
    str = tmp;
    return *this;
}

MyString operator+(const MyString &left, const MyString &right){
    MyString res(left);
    res += right;
    return res;
}

MyString::MyString(MyString &&other) noexcept {
    str = other.str;
    other.str = nullptr;
}

MyString& MyString::operator=(MyString &&other) noexcept {
    if (this == &other){
        return *this;
    }
    delete[] str;
    str = other.str;
    other.str = nullptr;
    return *this;
}

const char *MyString::c_str() const {
    if (str == nullptr){
        return "";
    }
    return str;
}

bool operator==(const MyString &a, const MyString &b){ return strcmp(a.c_str(), b.c_str()) == 0; }
bool operator!=(const MyString &a, const MyString &b){ return !(a == b); }
bool operator<(const MyString &a, const MyString &b){ return strcmp(a.c_str(), b.c_str()) < 0; }
bool operator<=(const MyString &a, const MyString &b){ return !(b < a); }

char& MyString::operator[](int i){
    if (i < 0 || i >= (int)strlen(c_str())){
        throw out_of_range("MyString: index out of range");
    }
    return str[i];
}

char MyString::operator[](int i) const{
    if (i < 0 || i >= (int)strlen(c_str())){
        throw out_of_range("MyString: index out of range");
    }
    return str[i];
}

ostream& operator<<(ostream &os, const MyString &s){
    os << s.c_str();
    return os;
}

istream& operator>>(istream &is, MyString &s){
    int n = 10;
    char *buf = new char[n];
    int i = 0;

    char c;
    while (is.get(c) && c != '\n'){
        buf[i++] = c;

        if (i == n){
            char *temp = new char[2 * n];
            for (int j = 0; j < n; j++){
                temp[j] = buf[j];
            }
            delete[] buf;
            buf = temp;
            n *= 2;
        }
    }
    buf[i] = '\0';

    delete[] s.str;
    s.str = buf;
    return is;
}