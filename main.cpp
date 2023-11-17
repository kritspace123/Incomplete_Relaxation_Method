#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int N = 3; // Размерность СЛАУ

void matVecMult(double** A, double* x, double result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = 0.0;
        for (int j = 0; j < N; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

void scalarMult(double a, double x[N], double result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = a * x[i];
    }
}

void vectorSub(double x[N], double y[N], double result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = x[i] - y[i];
    }
}

double dotProduct(double x[N], double y[N]) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += x[i] * y[i];
    }
    return result;
}

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

    double* m_Barr = new double[N];
    for (int i = 0; i < N; ++i) {
        FI >> m_Barr[i];
    }
    double x[N];
    double r[N], p[N], Ap[N], r_prev[N];
    double alpha, beta;
    for(int i = 0; i < N; ++i){
        x[i] = 0;
        r_prev[i] = 0;
    }

    for (int k = 0; k < N; k++) {
        matVecMult(m_Arr, x, Ap); //умножение матрицы на вектор
        vectorSub(m_Barr, Ap, r); //разность векторов
        if (k == 0) {
            scalarMult(1.0, r, p); //множение вектора на скаляр
        } else {
            double beta = dotProduct    (r, r) / dotProduct(r_prev, r_prev);
            scalarMult(beta, r_prev, p);
            vectorSub(r, p, p);
        }

        double alpha = dotProduct(r, r) / dotProduct(p, Ap);
        scalarMult(alpha, p, step);
        vectorSub(x, step, x);
        for (int i = 0; i < N; i++) {
            r_prev[i] = r[i];
        }
    }

    std::cout << "Solution: ";
    for (int i = 0; i < N; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}