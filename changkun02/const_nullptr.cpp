#include <cstddef>
#include <iostream>
#include <type_traits>

void foo(int);
void foo(char *);

int main() {
  if (std::is_same<decltype(NULL), decltype(0)>::
          value) // https://en.cppreference.com/cpp/types/is_same
    std::cout << "NULL = 0" << std::endl;
  if (std::is_same<decltype(NULL), decltype((void *)0)>::value)
    std::cout << "NULL = (void*)0" << std::endl;
  if (std::is_same<decltype(NULL), std::nullptr_t>::value)
    std::cout << "NULL = nullptr" << std::endl;

  foo(0);
  foo(nullptr);
  return 0;
}

void foo(int i) { std::cout << "foo(int) is called" << std::endl; }

void foo(char *c) { std::cout << "foo(char*) is called" << std::endl; }

/*take home message 29.04.2026:
- char* p or char *p doesnt matter, they both refer to a pointer
- cppreference
- decltype to derive type
*/