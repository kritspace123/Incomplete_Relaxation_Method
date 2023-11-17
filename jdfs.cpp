#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void matVecMult(double** A, double* x, double* result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = 0.0;
        for (int j = 0; j < N; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
} ///умножение матрицы на ветор

void scalarMult(double a, double* x, double* result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = a * x[i];
    }
}///умножение на скаляр


void vectorSub(double* x, double* y, double* result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = x[i] - y[i];
    }
}///азница векторов

double dotProduct(double* x, double* y, int N) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += x[i] * y[i];
    }
    return result;
} ///скалярное произведение

int main() {
    system("chcp 65001"); // Русификация ввода/вывода
    ifstream FI("input.txt"); //открываем файл "input.txt"
    if(!FI){
        cout << "Не удалось открыть файлы"<< endl;
        return 1;
    }
    int N, k;
    FI >> N; //Считываем размер матриц
    double** m_Arr;
    m_Arr = new double*[N]; //выделяем память ( создаем массив указателей на указатели )
    for (int i = 0; i < N; ++i) {
        m_Arr[i] = new double[N]; //выделяем память под массив размера n
        for (int j = 0; j < N; ++j) {
            FI >> m_Arr[i][j];
        }
    }
    double* x = new double[N]; ///Выберем начальное приближение x0
    double* r = new double[N]; ///r0
    double* z = new double[N]; ///z0
    double* m_Barr = new double[N];
    for (int i = 0; i < N; ++i) {
        FI >> m_Barr[i];
        x[i]  = 0;
    }
    double* c = new double[N];
    double* a = new double[N];
    double* t = new double[N];
    matVecMult(m_Arr, x, c, N);
    vectorSub(m_Barr, c,r,N); ///нашёл r0
    for (int i = 0; i < N; ++i) {
        z[i] = r[i];
    }

    for (int k = 0; k < 100; ++k) {
        double q = dotProduct(r,r, N); ///(r,r)
        matVecMult(m_Arr, z, c, N);///Az  = c
        double e = dotProduct(c, z, N);///(Az, z)
        int alf = q/e;
        double* new_x = new double[N];
        scalarMult(alf,z, t, N);///alf*z
        for (int i = 0; i < N; ++i) {
            new_x[i] = x[i]+t[i];
        }
        double* new_r = new double[N];
         
    }





    return 0;
}