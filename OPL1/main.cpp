#include <iostream>

using namespace std;

void readTime(string prompt, int *hours, int *minutes, int *seconds) {
  while (
      // выполняем цикл, пока:
      // введено не ровно три числа через ':'
      // ИЛИ одно из них не входит в интервал 0 <= x <= 59 (23 для часов)
      ((cout << prompt) && scanf_s("%d:%d:%d", hours, minutes, seconds) != 3) ||
      cin.peek() != '\n' ||
      (23 < *hours || *hours < 0 || 59 < *minutes || *minutes < 0 ||
       59 < *seconds || *seconds < 0)) {
    cin.clear(); // сбрасываем ошибку

    // == cin.ignore(numeric_limits<streamsize>::max(), '\n')
    while (cin.get() != '\n') {
    };

    cout << "wrong time format: expected HH:MM:SS\n\n";
  }
}

void run() {
  // запрашиваем у пользователя входные данные: время начало и конца процесса
  int startHours, startMinutes, startSeconds;
  int endHours, endMinutes, endSeconds;
  readTime("enter start time: ", &startHours, &startMinutes, &startSeconds);
  readTime("enter end time: ", &endHours, &endMinutes, &endSeconds);

  int days = 0;
  int startTime = startHours * 3600 + startMinutes * 60 + startSeconds;
  int endTime = endHours * 3600 + endMinutes * 60 + endSeconds;

  // если время завершения окажется меньше времени начала,
  // можем предположить, что задача заняла несколько дней,
  // ведь машину времени не изобрели
  if (startTime > endTime) {
    cout << "task ended before starting: assuming task took multiple days\n";
    while (((cout << "enter day count: ") && !(cin >> days)) || days <= 0) {
      cout << "wrong day count: expected a positive integer\n\n";
      cin.clear(); // сбрасываем ошибку

      // == cin.ignore(numeric_limits<streamsize>::max(), '\n')
      while (cin.get() != '\n') {
      };
    }
  }

  // подсчитываем общее потраченное время в секундах
  int totalTimeSpent = endTime - startTime + days * 24 * 3600;

  printf_s("task took %d second(s)", totalTimeSpent);
  if (totalTimeSpent > 60)
    printf_s(" or about %d minute(s)", totalTimeSpent / 60);
  cout << "\n";

  // переводим секунды в часы и минуты для наиболее точного вывода
  int totalHoursSpent = totalTimeSpent / 3600;
  int totalMinutesSpent = (totalTimeSpent - totalHoursSpent * 3600) / 60;
  int totalSecondsSpent =
      totalTimeSpent - totalHoursSpent * 3600 - totalMinutesSpent * 60;
  printf_s("or a total of %d hour(s) %d minute(s) %d second(s)\n",
           totalHoursSpent, totalMinutesSpent, totalSecondsSpent);
}

int main() {
  cout << "this program calculates the difference between two time stamps\n";
  cout << "expected time format: HH:MM:SS\n";

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
