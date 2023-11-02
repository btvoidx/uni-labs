#include <fstream>
#include <iostream>

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
    if (is_digit(character) || (reading_number && character == '.')) {
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

int main() {
  cout << "this program removes all numbers from ./in.txt and puts the result "
          "into ./out.txt and ./numbers.txt\n";

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
