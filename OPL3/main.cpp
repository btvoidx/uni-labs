#include <iostream>
#include <vector>

using namespace std;

template <typename T> T ask(string msg) {
  double v;
  while (!(cout << msg) || !(cin >> v) || cin.peek() != '\n') {
    cout << "bad input\n";
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
  }
  return v;
}

void random_fill(vector<int> &vec) {
  for (int i = 0; i < (int)vec.size(); i++)
    // берём остаток деления, чтобы были красивые
    // и лёгкия для восприятия значения
    vec[i] = rand() % vec.size() + 1;
}

void print_vec(vector<int> vec) {
  cout << "[ ";
  // короткие вектора можно выводить полностью
  if (vec.size() <= 14)
    for (auto v : vec)
      cout << v << " ";
  // для длинных стоит выводить начало и конец
  else {
    for (int i = 0; i < 7; i++)
      cout << vec[i] << " ";

    cout << "... ";

    for (int i = 7; i > 0; i--)
      cout << vec[vec.size() - i] << " ";
  }
  cout << "]\n";
}

void quicksort(vector<int> &vec, int low, int high) {
  if (low >= high)
    return;

  // выбераем случайную опорную точку между low и high включительно
  int pivot = vec[low + rand() % (high - low + 1)];

  // для отладки
  // printf_s("pivot: %d\n", pivot);
  int i = low, j = high;
  while (i < j) {
    while (vec[i] < pivot)
      i++;
    while (vec[j] > pivot)
      j--;

    auto temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;

    // для отладки
    // printf_s("swap %d and %d:\t", vec[j], vec[i]);
    // print_vec(vec);

    // если элементы равны, while уйдёт в бесконечный цикл
    // т.к. все условия всегда выполняются.
    // смещение j на 1 не даёт задерживаться на
    // таких парах чисел дольше одной итерации.
    if (vec[i] == vec[j])
      j--;
  }

  quicksort(vec, low, i - 1);
  quicksort(vec, i + 1, high);
}

void run() {
  srand(time(0));

  int size;
  while (size < 2)
    size = ask<int>("array size (2+): ");

  vector<int> vec(size);
  random_fill(vec);

  printf_s("initial array:\n  ");
  print_vec(vec);

  quicksort(vec, 0, vec.size() - 1);

  printf_s("sorted array:\n  ");
  print_vec(vec);
}

int main() {
  cout << "this program implements quick sort algorithm\n";

  string shouldRepeat;
  do {
    // настоящий "main" программы.
    // он вынесен, чтобы отделить основную логику программы
    // от вторичной логики перезапуска.
    run();

    cout << "\nagain? (y / anything else quits): ";
    cin >> shouldRepeat;
    cout << "\n";
  } while (shouldRepeat == "y" || shouldRepeat == "Y");

  return 0;
}