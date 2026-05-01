#include "../include/Teams.h"
#include <string>

class Task {
public:
  std::string title;
  User *assignee; // Виконавець
  bool isDone;

  Task(std::string t) : title(t), assignee(nullptr), isDone(false) {}

  void assignTo(User *u) { assignee = u; }
};
