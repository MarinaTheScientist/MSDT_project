#include "matrix.hpp"
#include <iostream>
using namespace std;


Matrix::Matrix(int n) : rows(n), cols(n), data(new double*[n]){
    for (int i = 0; i < n; i++){
        data[i] = new double[n];
        for (int j = 0; j < n; j++){
            if (i == j){
                data[i][j] = 1;
            }
            else{
                data[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(int m, int n, double fill_value){
    rows = m;
    cols = n;
    data = new double*[m];
	for (int i = 0; i < m; i++) {
		data[i] = new double[n];
		for (int j = 0; j < n; j++) {
			data[i][j] = fill_value;
		}
	}
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols){
    data = new double*[rows];
    
    for (int i = 0; i < rows; i++){
        data[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < rows; i++){
        delete[] data[i];
    }
    delete[] data;
}

double Matrix::get(int i, int j){
    return data[i][j];
}

void Matrix::set(int i, int j, double value){
    data[i][j] = value;
}

int Matrix::get_width(){
    return cols;
}

int Matrix::get_height(){
    return rows;
}

void Matrix::negate(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] *= -1;
        }
    }
}

void Matrix::add_in_place(Matrix &other){
    if (cols != other.cols || rows != other.rows){
        throw 0;
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] += other.data[i][j];
        }
    } 
}

Matrix Matrix::multiply(Matrix &other){
    Matrix res_matrix(get_height(), other.get_width());
    if (get_width() != other.get_height()){
        throw 0;
    }
    for (int i = 0; i < get_height(); i++){
        for (int j = 0; j < other.get_width(); j++){
            for (int n = 0; n < get_width(); n++){
                res_matrix.data[i][j] += data[i][n] * other.data[n][j];
            }        
        }
    }
    return res_matrix;
}


