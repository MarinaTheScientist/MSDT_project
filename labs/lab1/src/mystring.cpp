#include "mystring.hpp"
#include <iostream>
#include <cstring>

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
    delete this->str;
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

void MyString::print(){
    cout << str << "\n";
}

void MyString::read_line(){
    delete[] str;
    int n = 10;
    char c = ' ';
    char *str = new char[n];
    int i = 0;

    while ((c = getchar()) != '\n')
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