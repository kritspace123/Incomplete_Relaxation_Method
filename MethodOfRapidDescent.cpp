//
// Created by Антон on 09.11.2023.
//
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
double const eps = 1e-3;

void PrintVector(double* x, int N){
    for (int i = 0; i < N; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
    cout << endl;
}
void Printmatrix(double**  m_Arr, int N){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << m_Arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


double Scalar_Product(double* m_X, double* m_Y, int N){
    double result = 0;
    for (int i = 0; i < N; ++i) {
        result += m_X[i] * m_Y[i];
    }
    return result;
}
double Scalar_Product(double* m_X, int N){
    double result = 0;
    for (int i = 0; i < N; ++i) {
        result += m_X[i] * m_X[i];
    }
    return result;
}
double* MultiplyMatrixVector(double** m_Arr, double *m_X, int N){
    double* result = new double [N];
    for (int i = 0; i < N; ++i) {
        result[i] = 0;
        for (int j = 0; j < N; ++j) {
            result[i] += m_Arr[i][j] * m_X[j];
        }
    }
    return result;
}
double* residuals(double** m_Arr, double* m_X0, double* B, int N){
    double* r;
    r = MultiplyMatrixVector(m_Arr, m_X0, N);
    for (int i = 0; i < N; ++i) {
        r[i] = r[i] + B[i];
    }
    return r;
}
double tao(double** m_Arr, double *r, int N){
    double a = Scalar_Product(r, r, N);
    double B = Scalar_Product(MultiplyMatrixVector(m_Arr, r, N),r, N);
    return a / B;
}

double Norma(double* m_X, int N){
    return sqrt(Scalar_Product(m_X, N));
}
void RapidDesc(int N, double** m_Arr, double* m_X0, double* B){
    int counter = 0;
    double* rk = residuals(m_Arr, m_X0, B, N);
    double tk1 = tao(m_Arr, rk, N);
    double* xk = m_X0;
    double* xk1 = new double [N];
    while (Norma(residuals(m_Arr, xk, B, N), N) > eps){
        if(counter > 10000) {
            cerr << "Метод не сходится";
            break;
        }
        counter++;
        for (int i = 0; i < N; ++i) {
            xk1[i] = xk[i] - tk1*rk[i];
        }
        xk = xk1;
        rk = residuals(m_Arr, xk, B, N);
        tk1 = tao(m_Arr, rk, N);
    }
    cout << "Количество итераций:"<< counter << endl;
    cout << "X: ";
    PrintVector(xk, N);
}

int main(){
    system("chcp 65001");
    ifstream FI("input.txt"); //открываем файл "input777.txt"
    if(!FI){
        cout << "Не удалось открыть файлы"<< endl;
        return 1;
    }
    int N;
    FI >> N;
    double** m_Arr = new double * [N];
    for (int i = 0; i < N; ++i) {
        m_Arr[i] = new double [N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            FI >> m_Arr[i][j];
        }
    }

    double* m_B = new double[N];
    for (int i = 0; i < N; ++i) {
        FI >> m_B[i];
    }
    double* m_X0 = new double[N];
    for (int i = 0; i < N; ++i) {
        FI >> m_X0[i];
    }

    RapidDesc(N, m_Arr, m_X0, m_B);


    return 0;
}