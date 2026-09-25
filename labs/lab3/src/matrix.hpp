#pragma once

class Matrix
{
private:
    int rows;
    int cols;
    double **data;

public:
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0.0);
    Matrix(const Matrix &other);
    ~Matrix();
    Matrix(Matrix &&other) noexcept;
    Matrix& operator=(Matrix &&other) noexcept;
    Matrix& operator=(const Matrix &other);
    Matrix& operator+=(const Matrix &other);
    Matrix& operator-=(const Matrix &other);
    Matrix& operator*=(double k);
    Matrix& operator/=(double k);
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(double k) const;
    Matrix operator/(double k) const;

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;
    void negate();
    void add_in_place(Matrix &other) const;
    Matrix multiply(Matrix &other) const;

};
Matrix operator*(double k, const Matrix &m);
Matrix operator-(const Matrix &m);


