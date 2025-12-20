#include <iostream>
#include <ranges>  // STL v2
#include <algorithm>
#include <vector>
#include <string>

int main() {
  std::vector<int> v{3, 5, 7, 6, 4, 9, 0};

// Дан диапазон целых чисел. Необходимо в цикле проитерироваться только по положительным числам и вывести их на экран.
  for (int i : std::views::take_while(v, [](auto x) { return x > 0; })) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

// Дан диапазон целых чисел. Необходимо в цикле проитерироваться по квадратам этих чисел и вывести их на экран.
  for (int i : std::views::transform(v, [](auto x) { return x * x; })) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

// Дан диапазон целых чисел. Необходимо в цикле проитерироваться только по положительным числам, 
// возвести их в квадрат и вывести их на экран.
  for (int i : std::views::take_while(v, [](int x){ return x > 0; }) | std::views::transform([](int x){ return x * x; })) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

// Дан диапазон, состоящий из диапазонов целых чисел (например, std::vector<std::vector<int>>). 
// Необходимо одним циклом вывести все числа из этих последовательностей.
  std::vector<std::vector<int>> vv{{1,2,3}, {4}, {}, {5,6}};

  for (int x : vv | std::views::join) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

// Дан файл с логами работы некоторого сервиса. Логи имеют следующий формат: "<level>: message" (одна строка - одна запись лога).
// <level> - уровень логирования (ERROR, WARNING, INFO и т.д.). Необходимо посчитать, сколько раз в первой 1000
// записей встречаются логи уровня ERROR.
  std::vector<std::string> logs{"WARNING: message", "INFO: message", "ERROR: message"};
  int count = std::ranges::count_if(logs | std::views::take(1000), [](const std::string& line) {
    return line.rfind("ERROR:", 0) == 0;
  });
  std::cout << count << '\n';
}
