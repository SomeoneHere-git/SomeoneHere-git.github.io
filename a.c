#include <stdio.h>
int f(int a) { return a * a; };
int main() {

  int asqrt = f(10);
  printf("%d", asqrt);
  return 0;
}
