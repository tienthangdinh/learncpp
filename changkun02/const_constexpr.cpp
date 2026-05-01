#include <iostream>
#define LEN 10

int len_foo() {
  int i = 2;
  return i;
}

constexpr int len_foo_constexpr() { return 5; }

constexpr int fibonacci(const int n) {
  return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  char arr_1[10];
  char arr_2[LEN];
  int len = 10;
  const int len2 = len + 1;
  // char arr_3[len_foo()]; illegal, because dependent on int
  constexpr int const_expr_len2 = 1 + 2 + 3;

  char arr_4[const_expr_len2];
  // char arr_5[len2]; illegal, because dependent on int
  char arr_6[len_foo_constexpr()];

  std::cout << fibonacci(10) << std::endl;

  return 0;
}

/*take home message 29.04.2026:
- const is const in run-time
- constexpr is const in compile-time!!! cannot be dependent on any normal
variable type like (int)
=> in robotics: some variables needed to be declared already before runtime
*/
