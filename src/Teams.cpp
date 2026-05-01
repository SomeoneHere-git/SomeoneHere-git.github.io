#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class User {
public:
  std::string name;
  User(std::string n) : name(n) {}
};

class Team {
private:
  std::string teamName;
  std::vector<User *> members;

public:
  Team(std::string name) : teamName(name) {}

  void addUser(User *user) { members.push_back(user); }

  void removeUser(std::string userName) {
    auto it = std::remove_if(members.begin(), members.end(),
                             [&](User *u) { return u->name == userName; });
    if (it != members.end()) {
      members.erase(it, members.end());
    }
  }

  void printTeam() {
    std::cout << "Команда " << teamName << ": ";
    for (auto u : members) {
      std::cout << u->name << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  User u1("Олексій");
  User u2("Марія");
  User u3("Дмитро");

  Team team("Jira Killer");

  team.addUser(&u1);
  team.addUser(&u2);
  team.addUser(&u3);
  team.printTeam();

  team.removeUser("Марія");
  team.printTeam();

  return 0;
}
