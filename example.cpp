#include "./tokei.hpp"
#include <chrono>

int main() {
  // initialize tokei object
  tokei::Tokei tokei;

  // start tokei
  tokei.start();

  // get current elapsed time
  std::cout << tokei.get() << std::endl;

  // reset tokei
  // if tokei is running, reset don't stop tokei.
  tokei.reset();

  // stop tokei
  tokei.stop();

  // tokei.get() and .print() can call with template
  std::cout << tokei.get<std::chrono::milliseconds>() << std::endl;

  // print current elapsed time with format
  tokei.print();

  // tokei.print() can enable debug mode
  tokei.print(true);
}
