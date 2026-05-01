#include "Program.h"
#include "Timer.cpp"

int mai() {
  Prog Program{};
  while (Program.ShouldClose) {
    Program.loop();
  }
  return 0;
}
