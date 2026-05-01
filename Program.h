#pragma once
enum Theme {
  Night,
  Grey,
  Gruvbox,
  Dracula,
  Day,
};
class Prog {

public:
  Prog();
  void loop();

public:
  bool ShouldClose{};

private:
  Theme theme{};
};
void Prog::loop() {
  switch (this->theme) {
  case Night:
  case Grey:
  case Gruvbox:
  case Dracula:
  case Day:
  default:
    break;
  }
}
