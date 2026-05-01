#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class User {
public:
  std::string name;
  User(std::string n);
};

class Team {
private:
  std::string teamName;
  std::vector<User *> members;

public:
  Team(std::string name);

  void addUser(User *user);
  void removeUser(const std::string &userName);
  void printTeam() const;
};
