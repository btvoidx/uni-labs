/*
# Задание
Реализовать консольное приложение, предназначенное для работы с массивом
экземпляров класса.

Входные данные: количество элементов массива, экземпляры класса.
Выходные данные: массив экземпляров класса и массив результатов работы метода по
обработке данных.

# Особенности:
- у класса должны быть перегружены операторы взятия из потока и помещения в
поток;
- должна быть создана функция-член класса, реализующая обработку данных
экземпляра класса согласно варианту;
- должна быть реализована возможность выбора чтения из файла или с консоли;
- должна быть реализована возможность выбора записи в файла или вывода в
консоль.
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class measurement {
public:
  measurement() {
    this->id = 0;
    this->speed = 0;
    this->kmph = false;
  };

  measurement(int id, double speed, bool kmph) {
    this->id = id;
    this->speed = speed;
    this->kmph = kmph;
  }

  measurement(const measurement &rhs) {
    this->id = rhs.id;
    this->speed = rhs.speed;
    this->kmph = rhs.kmph;
  }

  measurement &operator=(const measurement &rhs) { return *this; };

  int id;
  double speed;
  bool kmph;

  measurement in_kmph() const;
  measurement in_mps() const;

  friend istream &operator>>(istream &, measurement &);
  friend ostream &operator<<(ostream &, const measurement &);
};

istream &operator>>(istream &in, measurement &ms) {
  in >> ms.id;
  in >> ms.speed;

  string unit;
  if (!(in >> unit))
    return in;

  ms.kmph = unit == "km/h";
  if (unit != "m/s" && unit != "km/h")
    in.setstate(istream::badbit);

  return in;
};

ostream &operator<<(ostream &out, const measurement &ms) {
  out << ms.id << " " << ms.speed << (ms.kmph ? "km/h" : "m/s");
  return out;
};

measurement measurement::in_kmph() const {
  if (this->kmph)
    return *this;

  return measurement(this->id, this->speed * 3.6, true);
}

measurement measurement::in_mps() const {
  if (!this->kmph)
    return *this;

  return measurement(this->id, this->speed / 3.6, false);
}

void solution(istream &in, ostream &out) {
  cout << "reading!\n";

  int size = 0;
  if (!(in >> size) || size <= 0) {
    cout << "size read failed; aborting\n";
    return;
  }

  vector<measurement> data(size);
  for (auto &v : data)
    if (!(in >> v)) {
      cout << "measurement read failed; aborting\n";
      return;
    }

  out << "In m/s:" << "\n";
  for (const auto &v : data)
    out << v.in_mps() << "\n";
  
  out << "\n";
  out << "In km/h:" << "\n";
  for (const auto &v : data)
    out << v.in_kmph() << "\n";

  cout << "done!\n";
}

int main() {
  cout << "this program reads measurements and outputs them in km/h and m/s"
          "press Ctrl+C to exit\n";

  while (true) {
    int choice = 0;
    cout << "choose data in/out:\n"
            "[1] cin/cout\n"
            "[2] cin/out.txt\n"
            "[3] in.txt/cout\n"
            "[4] in.txt/out.txt\n"
            "> ";
    if (!(cin >> choice) || cin.peek() != '\n') {
      cin.clear();
      cin.ignore(LLONG_MAX, '\n');
      cout << "quit meddling around\n> ";
      continue;
    }

    switch (choice) {
    case 1: {
      solution(cin, cout);
      cin.clear();
      cin.ignore(LLONG_MAX, '\n');
    } break;
      
    case 2: {
      ofstream out("out.txt");
      if (!out.is_open()) {
        cout << "failed to open out.txt; aborting\n";
        continue;
      }

      cout << "have fun typing it out by hand!\n";
      solution(cin, out);
      cin.clear();
      cin.ignore(LLONG_MAX, '\n');
    } break;
      
    case 3: {
      ifstream in("in.txt");
      if (!in.is_open()) {
        cout << "failed to open in.txt; aborting\n";
        continue;
      }

      solution(in, cout);
    } break;
      
    case 4: {
      ifstream in("in.txt");
      ofstream out("out.txt");
      if (!in.is_open() || !out.is_open()) {
        cout << "failed to open the files; aborting\n";
        continue;
      }

      solution(in, out);
    } break;
      
    default:
      cout << "unknown input\n";
    }

    cout << "\n\n";
  }

  return 0;
}
