#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
  std::map<std::string, size_t> dict;
  std::string wd;
  while (std::cin >> wd) {
    if (!wd.empty()) {
      dict[std::move(wd)] += 1;
    }
  }

  std::vector<std::pair<size_t, std::string>> arr;
  arr.reserve(dict.size());

  for (const auto& p : dict) {
    arr.emplace_back(p.second, p.first);
  }

  std::sort(arr.begin(), arr.end(), [](const auto& a, const auto& b) {
    if (a.first != b.first) {
      return a.first > b.first;
    }
    return a.second < b.second;
  });

  for (const auto& p : arr) {
    std::cout << p.second << '\n';
  }

  return 0;
}
