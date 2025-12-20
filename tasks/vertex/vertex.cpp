#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;

  int k = 0;
  std::cin >> k;

  std::vector<std::vector<int>> g(n + 1);

  for (int i = 0; i < k; ++i) {
    int type = 0;
    std::cin >> type;

    if (type == 1) {
      int u = 0;
      int v = 0;
      std::cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    } else if (type == 2) {
      int u = 0;
      std::cin >> u;
      for (int v : g[u]) {
        std::cout << v << ' ';
      }
      std::cout << '\n';
    }
  }

  return 0;
}
