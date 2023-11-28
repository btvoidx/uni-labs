/*
# Задание
Реализовать одно консольное приложение с функциональностью согласно вариантам.

Отфильтровать строку от чисел.
Входные данные: строка.
Выходные данные: строка без чисел и массив чисел.

# Особенности:
- входные данные должны извлекаться из файла;
- выходные данные должны помещаться в файл.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void solution() {
  ifstream in("./in.txt");
  ofstream out("./out.txt");

  // выключает пропуск пробелов
  in.unsetf(ios_base::skipws);

  if (!in.is_open()) {
    cout << "failed to open ./in.txt; exiting\n";
    return;
  }
  if (!out.is_open()) {
    cout << "failed to open ./out.txt; exiting\n";
    return;
  }

  vector<int> nums;

  while (in.good()) {
    string s;
    getline(in, s);

    if (!s.find_first_of("0123456789")) {
      out << s << "\n";
      continue;
    }

    istringstream iss(s);
    ostringstream oss;
    iss.unsetf(ios_base::skipws);

    char character;
    int number;
    while (iss.good()) {
      if (iss >> number)
        nums.push_back(number);
      else {
        iss.clear();
        iss >> character;
        oss << character;
      }
    }

    out << oss.str() << "\n";
  }

  out << "\n";

  for (const auto v : nums)
    out << v << " ";
}

int main() {
  cout << "this program removes all numbers from ./in.txt and puts the result "
          "into ./out.txt\n";

  string shouldRepeat;
  do {
    // настоящий "main" программы.
    // он вынесен, чтобы отделить основную логику программы
    // от вторичной логики перезапуска.
    solution();

    cout << "\nagain? (y / anything else quits): ";
    cin >> shouldRepeat;
    cout << "\n";
  } while (shouldRepeat == "y" || shouldRepeat == "Y");

  return 0;
}
