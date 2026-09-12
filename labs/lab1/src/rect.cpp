#include "rect.hpp"
#include <iostream>
using namespace std;

int max(int n1, int n2){return (n1 > n2) ? n1 : n2;}
int min(int n1, int n2){return (n1 < n2) ? n1 : n2;}
int sub_abs(int a, int b){return (a >= b) ? a - b : b - a;}


Rect::Rect() : x(0), y(0), width(0), height(0){
    cout << "Вызов конструктора по умолчанию для адреса: " << this << "\n";
    // this->top = 0;
    // this->left = 0;
    // this->bottom = 0;
    // this->right = 0;
}
Rect::Rect(int bottom, int top, int left, int right) : x((left <= right) ? left : right), y((bottom <= top) ? bottom : top){
    cout << "Вызов конструктора класса задающего стороны прямогуольника в адресе: " << this << "\n";
    width = sub_abs(left, right);
    height = sub_abs(bottom, top);
}
// Rect::Rect(int x, int y, int width, int height){
//     cout << "Вызов конструктора класса задающего стороны прямогуольника в адресе: " << this << "\n";
//     this->x = x;
//     this->y = y;
//     this->width = width;
//     this->height = height;
// }
Rect::Rect(const Rect &other){
    cout << "Вызов конструктора копирования из адреса " << &other << " в адрес " << this << "\n";
    // this->top = other.top;
    // this->right = other.right;
    // this->bottom = other.bottom;
    // this->left = other.left;
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height;
}
Rect::~Rect(){
    cout << "Вызов деструктора для адреса: " << this << "\n";
    // this->top = 0;
    // this->left = 0;
    // this->bottom = 0;
    // this->right = 0;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

int Rect::get_top(){
    return y + height;
}
int Rect::get_left(){
    return x;
}
int Rect::get_bottom(){
    return y;
}
int Rect::get_right(){
    return x + width;
}
// int Rect::get_x(){
//     cout << "Вызов метода get_top для адреса: " << this << "\n";
//     return x;
// }
// int Rect::get_y(){
//     cout << "Вызов метода get_top для адреса: " << this << "\n";
//     return this->y;
// }

// void Rect::set_all(int bottom, int top, int left, int right){
//     cout << "Вызов метода set_all для адреса: " << this << "\n";
//     this->top = top;
//     this->left = left;
//     this->bottom = bottom;
//     this->right = right;
// }
void Rect::set_all(int bottom, int top, int left, int right){
    cout << "Вызов метода set_all для адреса: " << this << "\n";
    x = (left <= right) ? left : right;
    y = (bottom <= top) ? bottom : top;
    width = sub_abs(right, left);
    height = sub_abs(bottom, top);
}

// void Rect::inflate(int amount){
//     this->top += amount;
//     this->right += amount;
//     this->left -= amount;
//     this->bottom -= amount;
// }
void Rect::inflate(int amount){
    this->x -= amount;
    this->y -= amount;
    this->width += 2*amount;
    this->height += 2*amount;
}

// void Rect::inflate(int dw, int dh){
//     this->bottom -= dh;
//     this->top += dh;
//     this->left -= dw;
//     this->right += dw;
// }
void Rect::inflate(int dw, int dh){
    this->x -= dw;
    this->y -= dh;
    this->width += 2*dw;
    this->height += 2*dh;
}
// void Rect::inflate(int d_bottom, int d_top, int d_left, int d_right){
//     this->bottom -= d_bottom;
//     this->top += d_top;
//     this->left += d_left;
//     this->right -= d_right;
// }
void Rect::inflate(int d_bottom, int d_top, int d_left, int d_right){
    this->x -= d_left;
    this->y -= d_bottom;
    this->width += d_left + d_right;
    this->height += d_bottom + d_top;
}

// void Rect::move(int dx, int dy = 0){
//     this->bottom += dy;
//     this->top += dy;
//     this->left += dx;
//     this->right += dx;
// }
void Rect::move(int dx, int dy = 0){
    this->x += dx;
    this->y += dy;
}

// Rect bounding_rect(Rect r1, Rect r2){
//     Rect bounding_rect(
//     min(r1.get_bottom(), r2.get_bottom()),
//     max(r1.get_top(), r2.get_top()),
//     min(r1.get_left(), r2.get_left()),
//     max(r1.get_right(), r2.get_right())
//     );

//     return bounding_rect;
// }
Rect bounding_rect(Rect r1, Rect r2){
    Rect bounding_rect(
    min(r1.get_bottom(), r2.get_bottom()),
    max(r1.get_top(), r2.get_top()),
    min(r1.get_left(), r2.get_left()),
    max(r1.get_right(), r2.get_right())
    );

    return bounding_rect;
}
// void print_rect(Rect &r){
// int height = this->top - this->bottom;
// int width = this->right - this->left;
//     for (int i = 0; i < height; i++){
//         for (int j = 0; j < width; j++){
//             cout << "*";
//         }
//         cout << "\n";
//     }
// }
void print_rect(Rect &r){
    for (int i = 0; i < r.get_height(); i++){
        for (int j = 0; j < r.get_width(); j++){
            cout << "*";
        }
        cout << "\n";
    }
}

// int Rect::get_width(){
//     return this->right - this->left;
// }
int Rect::get_width(){
    return width;
}

// int Rect::get_height(){
//     return this->top - this->bottom;
// }
int Rect::get_height(){
    return height;
}


int Rect::get_square(){
    return this->get_width() * this->get_height();
}

// void Rect::set_width(int width){
//     this->right = this->left + width; 
// }
void Rect::set_width(int width){
    this->width = width; 
}

// void Rect::set_height(int height){
//     this->top = this->bottom + height; 
// }
void Rect::set_height(int height){
    this->height = height; 
}
    // комментарий
// комментарий для проверки хука
