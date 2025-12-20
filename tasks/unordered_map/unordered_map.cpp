#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  // быстрый ввод
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::unordered_map<std::string, std::string> dictionary;
  dictionary.reserve(n * 2);
  std::string key;
  std::string value;
  for (int i = 0; i < n; ++i) {
    std::cin >> key >> value;
    dictionary[key] = value;
    dictionary[value] = key;
  }

  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> key;
    std::cout << dictionary[key] << '\n';
  }
  return 0;
}
