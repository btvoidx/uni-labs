#include <iostream>
#include <string>
#include <limits>

using namespace std;

template <typename T> void ask(string q, T *v) {
  while ((cout << q) && (!(cin >> *v) || cin.peek() != '\n')) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  };
}

void run() {
  // размеры матрицы
  int w = 0, h = 0;
  while (w < 1)
    ask("input matrix width: ", &w);
  while (h < 1)
    ask("input matrix height: ", &h);

  // создаём матрицу
  double **mat = new double *[h];
  for (int hi = 0; hi < h; hi++)
    mat[hi] = new double[w];

  // наполняем матрицу
  for (int hi = 0; hi < h; hi++)
    for (int wi = 0; wi < w; wi++)
      ask("value at " + to_string(hi + 1) + "." + to_string(wi + 1) + ": ",
          &mat[hi][wi]);

  // показываем изначальную матрицу
  cout << "input matrix:\n";
  // min(x, 6) используется чтобы не выводить
  // слишком большие матрицы целиком
  for (int hi = 0; hi < min(h, 6); hi++) {
    for (int wi = 0; wi < min(w, 6); wi++) {
      cout << mat[hi][wi] << "\t";
    }
    cout << "\n";
  }

  // показываем результирующию матрицу
  cout << "output matrix:\n";
  for (int wi = 0; wi < min(w, 6); wi++) {
    for (int hi = 0; hi < min(h, 6); hi++) {
      cout << mat[hi][wi] << "\t";
    }
    cout << "\n";
  }

  // удаляем матрицу из памяти
  for (int hi = 0; hi < h; hi++)
    delete[] mat[hi];
  delete[] mat;
}

int main() {
  string shouldRepeat;
  do {
    run();

    cout << "again? (y/n): ";
    cin >> shouldRepeat;
  } while (shouldRepeat == "y" || shouldRepeat == "Y");
  return 0;
}