/*
# Задание
Реализовать одно консольное приложение:

Транспонирование матрицы без дополнительных массивов.
Входные данные: размеры матрицы и матрица.
Выходные данные: транспонированная матрица.

# Особенности
- алгоритм должен быть реализован без использования функций из
	специальных библиотек;
- при вводе неправильного входного значения программа должна
	повторно его запрашивать.
*/

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int askInt(string msg, string errmsg) {
  cout << msg;

  int v;
  while (!(cin >> v) || cin.peek() != '\n') {
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
    cout << errmsg;
    cout << msg;
  };

  return v;
}

void transposeSquareMatrix(double **mat, int size) {
  for (int a = 1; a < size; a++) {
    for (int b = 0; b < a; b++) {
      int tmp = mat[a][b];
      mat[a][b] = mat[b][a];
      mat[b][a] = tmp;
    }
  }
}

void printMatrix(double **mat, int w, int h) {
  // min(x, 6) используется чтобы не выводить
  // слишком большие матрицы целиком
  for (int hi = 0; hi < min(h, 6); hi++) {
    for (int wi = 0; wi < min(w, 6); wi++) {
      cout << mat[hi][wi] << "\t";
    }
    cout << "\n  ";
  }
}

void run() {
  // размеры матрицы
  int size = 0;
  while (size < 2)
    size = askInt("input matrix size (a positive number): ",
                  "sorry, numbers > 2 only\n");

  double **mat = new double *[size];
  for (int hi = 0; hi < size; hi++)
    mat[hi] = new double[size];

  // наполняем матрицу
  for (int hi = 0; hi < size; hi++)
    for (int wi = 0; wi < size; wi++)
      while (!printf_s("value at %d.%d: ", hi + 1, wi + 1) ||
             !(cin >> mat[hi][wi]) || cin.peek() != '\n') {
        cout << "sorry, numbers only\n";
        cin.clear();
        cin.ignore(LLONG_MAX, '\n');
      }

  cout << "\ninput matrix:\n  ";
  printMatrix(mat, size, size);

  transposeSquareMatrix(mat, size);

  cout << "\ntransposed matrix:\n  ";
  printMatrix(mat, size, size);

  // удаляем матрицу из памяти
  for (int hi = 0; hi < size; hi++)
    delete[] mat[hi];
  delete[] mat;
}

int main() {
  string shouldRepeat;
  do {
    run();

    cout << "\nagain? (y / anything else quits): ";
    cin >> shouldRepeat;
  } while (shouldRepeat == "y" || shouldRepeat == "Y");
  return 0;
}
