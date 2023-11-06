/*
# Задание
Реализовать возможность вычисления подряд (без повторного запуска) суммы для
различных значений аргумента x и α. Если значение x совпадает с предыдущим,
повторное вычисление рассчитанных ранее членов ряда и частичных сумм не
производится, а заимствуется из предыдущего расчета.

# Особенности
- необходимо учесть два возможных варианта значений параметра α:
	точность вычислений (положительное значение с плавающей точкой)
	или число слагаемых ряда для суммирования (целочисленное положительное
	значение); 
- данные выводятся после каждой итерации, т.о. данные будут выводиться столько 
	раз, сколько членов ряда было просуммировано;
- при вводе неправильных входных значений программа должна повторно их
	запрашивать.
*/

#include <iostream>
#include <map>
#include <math.h>
#include <vector>

using namespace std;

struct elem {
  double curr;
  double sum;
  double rn;
};

map<double, vector<elem>> caches;

double askDouble(string msg) {
  double v;
  while (!(cout << msg) || !(cin >> v) || cin.peek() != '\n') {
    cout << "bad input\n";
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
  }
  return v;
}

double fact(int n) {
  double f = 1;
  for (int i = 2; i <= n; i++)
    f *= i;
  return f;
}

double f(double x, int n) {
  return pow(-1, n) * ((2 * n * pow(x, 2 * n + 1)) / fact(2 * n + 1));
}

void run() {
  double x = askDouble("enter x: ");
  double a = askDouble("enter a: ");
  while (a <= 0) {
    cout << "a must be positive and non-zero\n";
    a = askDouble("enter a (correctly): ");
  }

  bool aIsWhole = floor(a) == a;
  if (aIsWhole)
    cout << "a is whole; calculating first " << a << " elements:\n";
  else
    cout << "a is real; calculating until eps < " << a << "\n";

  auto cache = caches[x];

  double curr = 0, sum = 0;
  double rn = 0;
  for (int n = 1; aIsWhole ? (n <= a) : (rn > a || rn == 0); n++) {
    // переводим в unsigned long long, чтобы компилятор не ругался
    // при -Wsign-compare
    bool cached = cache.size() >= (unsigned long long)n;
    if (cached) {
      int i = n - 1;
      curr = cache[i].curr;
      sum = cache[i].sum;
      rn = cache[i].rn;
    } else {
      curr = f(x, n);
      sum += curr;
      rn = abs(f(x, n + 1) / sum);
      cache.push_back(elem{curr, sum, rn});
    }

    printf_s("%s n: %d\ta(n): %g\tsum: %g\teps: %g\n", cached ? " " : "+", n,
             curr, sum, rn);
  }

  // сохраняем обновлённый кэш.
  caches[x] = cache;
}

int main() {
  cout << "this program calculates the scary formula given in the task "
          "and caches the results to be reused\n"
          "press Ctrl+C to exit\n";

  while (1)
    run();

  return 0;
}
