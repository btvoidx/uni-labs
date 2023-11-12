/*
# Задание
Реализовать одно консольное приложение с функциональностью согласно вариантам.

Отфильтровать строку от чисел.
Входные данные: строка.
Выходные данные: строка без чисел и массив чисел.

# Особенности:
- работа с со строками должна осуществляться без использования типа
  string (т.е. как с массивом символов);
- входные данные должны извлекаться из файла;
- выходные данные должны помещаться в файл.
*/

#include <fstream>
#include <iostream>
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

  char character;
  int number;
  vector<int> nums;
  while (in.good()) {
    if (in >> number)
      nums.push_back(number);
    else {
      in.clear();
      in >> character;
      out << character;
    }
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
