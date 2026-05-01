#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Task {
public:
  std::string title;
  bool isDone;

  Task(std::string t);
};
