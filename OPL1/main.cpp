#include <iostream>
#include <limits>

using namespace std;

void readTime(string prompt, int *hours, int *minutes, int *seconds) {
  while (
      ((cout << prompt) && scanf_s("%d:%d:%d", hours, minutes, seconds) != 3) ||
      cin.peek() != '\n' ||
      (59 < *hours || *hours < 0 || 59 < *minutes || *minutes < 0 ||
       59 < *seconds || *seconds < 0)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "wrong time format: expected HH:MM:SS\n";
    cout << prompt;
  }
}

void run() {
  int startHours, startMinutes, startSeconds;
  int endHours, endMinutes, endSeconds;
  readTime("enter start time: ", &startHours, &startMinutes, &startSeconds);
  readTime("enter end time: ", &endHours, &endMinutes, &endSeconds);

  int days = 0;
  int startTime = startHours * 3600 + startMinutes * 60 + startSeconds;
  int endTime = endHours * 3600 + endMinutes * 60 + endSeconds;

  if (startTime > endTime) {
    cout << "task ended before starting: assuming task took multiple days\n";
    while (days <= 0) {
      cout << "enter day count (>0): ";
      cin >> days;
    }
  }

  int totalTimeSpent = endTime - startTime + days * 24 * 3600;

  printf_s("task took %d second(s)", totalTimeSpent);
  if (totalTimeSpent > 60)
    printf_s(" or about %d minute(s)", totalTimeSpent / 60);
  cout << "\n";

  int totalHoursSpent = totalTimeSpent / 3600;
  int totalMinutesSpent = (totalTimeSpent - totalHoursSpent * 3600) / 60;
  int totalSecondsSpent =
      totalTimeSpent - totalHoursSpent * 3600 - totalMinutesSpent * 60;
  printf_s("or a total of %d hour(s) %d minute(s) %d second(s)\n",
           totalHoursSpent, totalMinutesSpent, totalSecondsSpent);
}

int main() {
  char shouldRepeat;
  do {
    run();

    cout << "again? (y / anything else quits): ";
    cin >> shouldRepeat;
  } while (shouldRepeat == 'y' || shouldRepeat == 'Y');
  return 0;
}
