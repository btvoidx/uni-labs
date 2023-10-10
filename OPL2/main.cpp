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

  double curr = 0, sum = 0;
  double rn = 0;

  // если a целое
  if (floor(a) == a) {
    cout << "a is whole; calculating first " << a << " elements:\n";
    for (int n = 1; n <= a; n++) {
      curr = f(x, n);
      sum += curr;
      rn = abs(f(x, n + 1) / sum);

      printf_s("n: %d\ta(n): %g\tsum: %g\teps: %g\n", n, curr, sum, rn);
    }
  } else {
    cout << "a is real; calculating until eps < " << a << "\n";
    int n = 0;
    do {
      n += 1;

      curr = f(x, n);
      sum += curr;
      rn = abs(f(x, n + 1) / sum);

      printf_s("n: %d\ta(n): %g\tsum: %g\teps: %g\n", n, curr, sum, rn);

    } while (rn >= a);
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