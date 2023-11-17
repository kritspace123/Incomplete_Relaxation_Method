//
// Created by Антон on 06.10.2023.
//

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Параметр релаксации (вы можете настроить его)
double omega = 1.22;//параметр релаксации
int maxIterations = 1000;
double tolerance = 1e-7;

int main() {
    system("chcp 65001"); // Русификация ввода/вывода
    ifstream FI("input.txt"); //открываем файл "input.txt"
    if(!FI){
        cout << "Не удалось открыть файлы"<< endl;
        return 1;
    }
    int n, k;
    FI >> n; //Считываем размер матриц
    cout << n;
    double** m_Arr;
    m_Arr = new double*[n]; //выделяем память ( создаем массив указателей на указатели )
    for (int i = 0; i < n; ++i) {
        m_Arr[i] = new double[n]; //выделяем память под массив размера n
        for (int j = 0; j < n; ++j) {
            FI >> m_Arr[i][j];
        }
    }

    double* m_Barr = new double[n];
    for (int i = 0; i < n; ++i) {
        FI >> m_Barr[i];
    }

    double* m_X = new double[n];// Исходное приближение
    for (int i = 0; i < n; ++i) {
        m_X[i] = 0;
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        double maxError = 0.0;

        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum += m_Arr[i][j] * m_X[j];
                }
            }

            double newX = (1.0 - omega) * m_X[i] + (omega / m_Arr[i][i]) * (m_Barr[i] - sum);
            double error = abs(newX - m_X[i]); //погрешность
            if (error > maxError) {
                maxError = error;
            }

            m_X[i] = newX;      // сохраняем решение
        }

        // Проверка на критерий сходимости
        if (maxError < tolerance) {
            cout << "Сходимость достигнута после " << iter + 1 << " итераций." << endl;
            break;
        }
    }

    // Вывод результата
    cout << "Решение:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x[" << i << "] = " << m_X[i] << endl;
    }

    return 0;
}
