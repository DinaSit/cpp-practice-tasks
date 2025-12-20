#include <algorithm>
#include <iostream>
#include <vector>

struct Team {
  int solved;
  int time;
  int id;
};

int main() {
  int n = 0;
  if (!(std::cin >> n)) {
    return 0;
  }

  std::vector<Team> teams;
  teams.reserve(n);  // вместимость

  for (int i = 1; i <= n; ++i) {
    int s = 0;
    int t = 0;
    std::cin >> s >> t;
    teams.push_back(Team{s, t, i});
  }

  std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
    if (a.solved != b.solved) {  // количество задач по убыванию
      return a.solved > b.solved;
    }
    if (a.time != b.time) {  // время по возрастанию
      return a.time < b.time;
    }
    return a.id < b.id;  // номер команды по возрастанию
  });

  for (int i = 0; i < n; ++i) {
    std::cout << teams[i].id << '\n';
  }

  return 0;
}
