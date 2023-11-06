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

bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

void solution() {
  ifstream in("./in.txt");
  ofstream out("./out.txt");
  ofstream nums("./numbers.txt");

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
  if (!nums.is_open()) {
    cout << "failed to open ./numbers.txt; exiting\n";
    return;
  }

  char character;
  bool reading_number = false;
  while (in >> character) {
    if (is_digit(character) ||
        (character == '-' && is_digit(in.peek()) && !reading_number) ||
        (character == '.' && reading_number)) {
      reading_number = true;
      nums << character;
      continue;
    }

    if (reading_number) {
      nums << ' ';
      reading_number = false;
    }

    out << character;
  }

  cout << "done\n";
}

void solution_vec() {
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
  vector<int> nums(1);
  while (in.good()) {
    if (in >> nums[nums.size() - 1])
      nums.push_back(0);
    else {
      in.clear();
      in >> character;
      out << character;
    }
  }

  out << "\n";

  cout << "done\nnumbers: ";
  for (const auto v : nums)
    // cout << v << " ";
    out << v << " ";
}

int main() {
  cout << "this program removes all numbers from ./in.txt and puts the result "
          "into ./out.txt and ./numbers.txt\n";

  string shouldRepeat;
  do {
    // настоящий "main" программы.
    // он вынесен, чтобы отделить основную логику программы
    // от вторичной логики перезапуска.
    solution_vec();

    cout << "\nagain? (y / anything else quits): ";
    cin >> shouldRepeat;
    cout << "\n";
  } while (shouldRepeat == "y" || shouldRepeat == "Y");

  return 0;
}
