#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  int x = 0;
  std::cin >> x;

  int cnt = static_cast<int>(std::count(a.begin(), a.end(), x));
  std::cout << cnt << '\n';

  return 0;
}
