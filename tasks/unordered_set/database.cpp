#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

int main() {
  std::string name;
  std::string good;
  size_t cnt = 0;
  //       user                  good         cnt
  std::map<std::string, std::map<std::string, size_t>> database;
  while (std::cin >> name >> good >> cnt) {
    database[name][good] += cnt;
  }
  // print info
  // идем по элементам бд (пара пользователя и внутренней бд)
  for (const auto& [name, goods] : database) {
    std::cout << name << ":\n";
    // внутренняя бд (товар и кол-во)
    for (const auto& [item, cnt] : goods) {
      std::cout << item << ' ' << cnt << '\n';
    }
  }
  return 0;
}
