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
  static const int MAX_MEMBERS = 5;

public:
  Team(std::string name) : teamName(name) {}

  void addUser(User *user) {
    if (members.size() < MAX_MEMBERS) {
      members.push_back(user);
    }
  }

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


