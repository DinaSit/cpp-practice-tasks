#include <iostream>
#include <cmath>
#include <set>

int main() {
  int n = 0;
  std::cin >> n;

  std::set<int> s;
  const auto mod = static_cast<int>(std::pow(10, 9));

  int last = 0;
  char prev_op = 0;

  for (int i = 0; i < n; ++i) {
    char op = 0;
    int x = 0;
    std::cin >> op >> x;

    if (op == '+') {
      if (prev_op == '?') {
        x = (x + last) % mod;
      }
      s.insert(x);
    } else if (op == '?') {
      auto it = s.lower_bound(x);
      int ans = -1;
      if (it != s.end()) {
        ans = *it;
      }
      std::cout << ans << '\n';
      last = ans;
    }
    prev_op = op;
  }
  return 0;
}
