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

int fact(int n) {
  for (int i = n - 1; i > 1; i--) {
    n *= i;
  }
  return n;
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

  double prev, curr, sum;

  // если a целое
  if (floor(a) == a) {
    cout << "a is whole; calculating first " << a << " elements:\n";
    for (int n = 1; n <= a; n++) {
      prev = curr;
      curr = f(x, n);
      sum += curr;

      if (n != 1 && abs(curr) > abs(prev)) {
        cout << "numbers are no longer correctly represented by double, "
                "exiting early\n";
        return;
      }

      printf("n: %d\ta(n): %f\tsum: %f\teps: %f\n", n, curr, sum,
             abs(prev - curr));
    }
  } else {
    cout << "a is real; calculating until eps < " << a << "\n";
    int n = 0;
    do {
      n += 1;

      prev = curr;
      curr = f(x, n);
      sum += curr;

      if (n != 1 && abs(curr) > abs(prev)) {
        cout << "numbers are no longer correctly represented by double, "
                "exiting early\n";
        return;
      }

      printf("n: %d;\ta(n): %f\tsum: %f\teps: %f\n", n, curr, sum,
             abs(prev - curr));

    } while (abs(prev - curr) > a);
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