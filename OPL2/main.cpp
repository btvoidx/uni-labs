/*
# Задание
Реализовать консольное приложение, предназначенное для приближённого
вычисления суммы бесконечного числового ряда, выбранного согласно номеру варианта.

Входные данные: параметр x и параметр α, характеризующий точность вычисления ряда.
Выходные данные: номер итерации (n), последний просуммированный член ряда (αn),
текущая частичная сумма (Sn), точность вычисления заданной текущей частичной суммы (αn).

# Особенности
- необходимо учесть два возможных варианта значений параметра α:
  точность вычислений (положительное значение с плавающей точкой)
	или число слагаемых ряда для суммирования (целочисленное положительное значение); 
- данные выводятся после каждой итерации, т.о. данные будут выводиться столько раз,
  сколько членов ряда было просуммировано;
- при вводе неправильного входного значения программа должна
  повторно его запрашивать.
*/

#include <iostream>
#include <math.h>

using namespace std;

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

  double curr = 0, sum = 0;
  double rn = 0;
  for (int n = 1; aIsWhole ? (n <= a) : (rn > a || rn == 0); n++) {
    curr = f(x, n);
    sum += curr;
    rn = abs(f(x, n + 1) / sum);

    printf_s("n: %d\ta(n): %g\tsum: %g\teps: %g\n", n, curr, sum, rn);
  }
}

int main() {
  cout << "this program calculates the scary formula given in the task\n";

  string shouldRepeat;
  do {
    // настоящий "main" программы.
    // он вынесен, чтобы отделить основную логику программы
    // от вторичной логики перезапуска.
    run();

    cout << "again? (y / anything else quits): ";
    cin >> shouldRepeat;
    cout << "\n\n";
  } while (shouldRepeat == "y" || shouldRepeat == "Y");

  return 0;
}
