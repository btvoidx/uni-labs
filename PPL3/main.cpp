#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace std::chrono;

template <typename T> T ask(string msg) {
  T v;
  while (!(cout << msg) || !(cin >> v) || cin.peek() != '\n') {
    cout << "bad input\n";
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
  }
  return v;
}

void random_fill(vector<int> &vec, int modulo) {
  for (long long unsigned int i = 0; i < vec.size(); i++)
    vec[i] = rand() % modulo + 1;
}

void random_fill(vector<int> &vec) {
  for (long long unsigned int i = 0; i < vec.size(); i++)
    // берём остаток деления, чтобы были лёгкия для восприятия значения
    vec[i] = rand() % vec.size() + 1;
}
void user_fill(vector<int> &vec) {
  for (long long unsigned int i = 0; i < vec.size(); i++)
    while (!(cin >> vec[i]) || !(cout << "read " << vec[i] << "; ")) {
      cout << "read fail: try again\n";
      cin.clear();
      cin.ignore(LLONG_MAX, '\n');
    }
  cout << "\n\n";
}

void print_vec(vector<int> const &vec) {
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
  // for(cout << "1"; true; cout<<2);
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

  int size = 0;
  while (size < 2)
    size = ask<int>("array size (2+)\n> ");

  vector<int> vec(size);

  for (int answer = 0; answer == 0;) {
    answer = ask<int>("array source:\n"
                      "1 - random\n"
                      "2 - random with little variation\n"
                      "3 - user input\n"
                      "> ");
    switch (answer) {
    case 1:
      random_fill(vec);
      break;
    case 2:
      random_fill(vec, log2(vec.size()));
      break;
    case 3:
      printf_s("input %d integers: ", vec.size());
      user_fill(vec);
      break;
    default:
      answer = 0;
    }
  }

  vector<int> vec_quicksort = vec, vec_stdsort = vec;

  auto quicksort_start = high_resolution_clock::now();
  quicksort(vec_quicksort, 0, vec_quicksort.size() - 1);
  auto quicksort_duration = high_resolution_clock::now() - quicksort_start;

  auto stdsort_start = high_resolution_clock::now();
  sort(vec_stdsort.begin(), vec_stdsort.end());
  auto stdsort_duration = high_resolution_clock::now() - stdsort_start;

  printf_s("initial array:\n  ");
  print_vec(vec);

  printf_s("sorted array (quicksort) (took %dus):\n  ",
           duration_cast<microseconds>(quicksort_duration));
  print_vec(vec_quicksort);

  printf_s("sorted array (std::sort) (took %dus):\n  ",
           duration_cast<microseconds>(stdsort_duration));
  print_vec(vec_stdsort);

  if (quicksort_duration < stdsort_duration)
    printf_s("quicksort is %g times faster than std::sort\n",
             (double)stdsort_duration.count() /
                 (double)quicksort_duration.count());
  else
    printf_s("std::sort is %g times faster than quicksort\n",
             (double)quicksort_duration.count() /
                 (double)stdsort_duration.count());
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
