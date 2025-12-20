#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  int id = 0;
  std::string user;
  int balance = 0;
  std::cin >> id;

  std::unordered_map<std::string, int> database;
  database.reserve(id);
  while (std::cin >> id) {
    if (id == 1) {
      std::cin >> user >> balance;
      database[user] += balance;
    } else {
      std::cin >> user;
      auto it = database.find(user);
      if (it == database.end()) {
        std::cout << "ERROR\n";
      } else {
        std::cout << it->second << '\n';
      }
    }
  }
  return 0;
}
