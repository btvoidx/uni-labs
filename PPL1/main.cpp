#include <iostream>
#include <string>

using namespace std;

int askInt(string msg) {
  cout << msg;

  int v;
  while (!(cin >> v) || cin.peek() != '\n') {
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
    cout << msg;
  };

  return v;
}

string askString(string msg) {
  cout << msg;

  string v;
  while (!(cin >> v) || cin.peek() != '\n') {
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
    cout << msg;
  };
  return v;
}

void run() {
  // размеры матрицы
  int w = 0, h = 0;
  while (w < 1)
    w = askInt("input matrix width (a positive number): ");
  while (h < 1)
    h = askInt("input matrix height (a positive number): ");

  // создаём матрицу
  // используется тип string вместо int или double
  // чтобы разрешить ввод конструкций типа "x + y"
  string **mat = new string *[h];
  for (int hi = 0; hi < h; hi++)
    mat[hi] = new string[w];

  cin.ignore(LLONG_MAX, '\n');

  // наполняем матрицу
  for (int hi = 0; hi < h; hi++)
    for (int wi = 0; wi < w; wi++) {
      printf_s("value at %d.%d: ", hi + 1, wi + 1);
      getline(cin, mat[hi][wi]);
    }

  // показываем изначальную матрицу
  cout << "\ninput matrix:\n  ";
  // min(x, 6) используется чтобы не выводить
  // слишком большие матрицы целиком
  for (int hi = 0; hi < min(h, 6); hi++) {
    for (int wi = 0; wi < min(w, 6); wi++) {
      cout << mat[hi][wi] << "\t";
    }
    cout << "\n  ";
  }

  // показываем транспонированную матрицу
  cout << "\ntransposed matrix:\n  ";
  for (int wi = 0; wi < min(w, 6); wi++) {
    for (int hi = 0; hi < min(h, 6); hi++) {
      cout << mat[hi][wi] << "\t";
    }
    cout << "\n  ";
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

    cout << "\nagain? (y / anything else quits): ";
    cin >> shouldRepeat;
  } while (shouldRepeat == "y" || shouldRepeat == "Y");
  return 0;
}
