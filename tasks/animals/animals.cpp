#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n = 0;
  if (!(std::cin >> n)) {
    return 0;
  }

  std::vector<int> colors(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> colors[i];
  }

  int m = 0;
  std::cin >> m;

  for (int i = 0; i < m; ++i) {
    int x = 0;
    std::cin >> x;

    // считаем вхождения через бинарный поиск, возвращает первое вхождение и последнее или конец если такое не найдено
    auto range = std::equal_range(colors.begin(), colors.end(), x);
    int count = static_cast<int>(range.second - range.first);

    std::cout << count << '\n';
  }

  return 0;
}
