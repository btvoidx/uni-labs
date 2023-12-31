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
#include <iostream>
#include <vector>

using namespace std;

class measurement {
public:
  int id;
  double speed;
  bool kmph;

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

  measurement in_kmph() const;
  measurement in_mps() const;

  friend istream &operator>>(istream &, measurement &);
  friend ostream &operator<<(ostream &, const measurement &);
};

istream &operator>>(istream &in, measurement &ms) {
  // предотвращает "0.6 km/h" как корректный ввод
  if (!(in >> ms.id) || in.peek() == '.') {
    in.setstate(istream::badbit);
    return in;
  }

  if (!(in >> ms.speed))
    return in;

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

class racer {
public:
  string full_name;
  vector<measurement> laps;

  racer() : full_name("John Doe"), laps() {}
  racer(string full_name, vector<measurement> laps)
      : full_name(full_name), laps(laps) {}

  measurement best_lap() const;

  friend istream &operator>>(istream &, measurement &);
  friend ostream &operator<<(ostream &, const measurement &);
};

measurement racer::best_lap() const {
  if (this->laps.size() == 0)
    return measurement();

  measurement current_best = this->laps[0];

  for (const auto &v : this->laps)
    if (current_best.in_mps().speed < v.in_mps().speed)
      current_best = v;

  return current_best;
}

istream &operator>>(istream &in, racer &r) {
  if (!(in >> r.full_name))
    return in;

  int lap_count;
  while (!(in >> lap_count)) {
    in.clear();

    string name_part;
    if (!(in >> name_part))
      return in;

    if (!r.full_name.empty())
      r.full_name += ' ';

    r.full_name += name_part;
  }

  r.laps = vector<measurement>(lap_count);
  for (auto &v : r.laps)
    if (!(in >> v))
      return in;

  return in;
};

ostream &operator<<(ostream &out, const racer &r) {
  out << r.full_name << " " << r.laps.size();
  for (const auto &v : r.laps)
    out << " " << v;

  return out;
};

void solution(istream &in, ostream &out) {
  cout << "legend:\n[racer count] ([name] [lap count] ([id] [speed] [m/s|km/h] "
          "...) ...)\n\n";
  cout << "reading!\n";

  int size = 0;
  if (!(in >> size) || size <= 0 || !isspace(cin.peek())) {
    cout << "size read failed; aborting\n";
    return;
  }

  vector<racer> data(size);
  for (auto &v : data)
    if (!(in >> v)) {
      cout << "measurement read failed; aborting\n";
      return;
    }

  for (const auto &v : data)
    out << v.full_name << "'s best lap: " << v.best_lap() << "\n";

  cout << "done!\n";
}

int main() {
  cout << ""
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
