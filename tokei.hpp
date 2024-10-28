#ifndef INCLUDE_TOKEI_HPP
#define INCLUDE_TOKEI_HPP

// header only time measurement library for c++
// works on c++ 11 or over

#include <chrono>
#include <iostream>
#include <sstream>

namespace tokei {

class Tokei {
public:
  Tokei() {
    // worm up
    std::chrono::high_resolution_clock::now();
  };
  void start() {
    if (isRunning) {
      return;
    }
    isRunning = true;
    m_start_point = std::chrono::high_resolution_clock::now();
  };
  void stop() {
    if (!isRunning) {
      return;
    }
    m_elapsed += std::chrono::duration(
        std::chrono::high_resolution_clock::now() - m_start_point);
    m_end_point = std::chrono::high_resolution_clock::now();
    isRunning = false;
  };
  void reset() {
    m_elapsed = std::chrono::nanoseconds::zero();
    if (isRunning) {
      m_start_point = std::chrono::high_resolution_clock::now();
    }
  };
  template <typename T = std::chrono::nanoseconds> long get() {
    if (isRunning) {
      return std::chrono::duration_cast<T>(
                 m_elapsed +
                 std::chrono::duration_cast<std::chrono::nanoseconds>(
                     std::chrono::high_resolution_clock::now() - m_start_point))
          .count();
    }
    return m_elapsed.count();
  };
  template <typename T = std::chrono::nanoseconds>
  void print(bool debug = false) {
    auto elapsed = std::chrono::duration_cast<T>(
        isRunning
            ? m_elapsed +
                  std::chrono::duration_cast<std::chrono::nanoseconds>(
                      std::chrono::high_resolution_clock::now() - m_start_point)
            : m_elapsed);
    if (debug) {
      auto time = std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now());
      std::tm *lt = std::localtime(&time);

      std::stringstream lt_ss;
      lt_ss << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec;

      std::cout << "[tokio][" << lt_ss.str()
                << "] isRunning: " << (isRunning ? "true" : "false")
                << std::endl;
      std::cout << "[tokio][" << lt_ss.str() << "] elapsed: " << elapsed.count()
                << std::endl;
    } else {
      std::cout << "[tokio] elapsed: " << elapsed.count() << std::endl;
    }
  };

private:
  std::chrono::high_resolution_clock::time_point m_start_point =
      std::chrono::time_point<std::chrono::high_resolution_clock>::min();
  std::chrono::high_resolution_clock::time_point m_end_point =
      std::chrono::time_point<std::chrono::high_resolution_clock>::min();

  std::chrono::nanoseconds m_elapsed = std::chrono::nanoseconds::zero();

  bool isRunning = false;
};
} // namespace tokei

#endif // !INCLUDE_TOKEI_HPP
