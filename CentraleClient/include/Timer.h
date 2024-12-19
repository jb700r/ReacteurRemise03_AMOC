#pragma once

#include "Callback.h"

class Timer {
 private:
  unsigned long m_nextTime;
  unsigned long m_interval;
 // Callback m_callback;

    std::function<void()> m_callback;


 public:
  Timer(unsigned long interval, std::function<void()> callback);
  void tick();
};

inline constexpr unsigned long operator"" _msecondes(unsigned long long ms) {
  return ms;
}

inline constexpr unsigned long operator"" _secondes(unsigned long long s) {
  return s * 1000;
}

inline constexpr unsigned long operator"" _minutes(unsigned long long minutes) {
  return minutes * 60 * 1000;
}

inline constexpr unsigned long operator"" _hours(unsigned long long h) {
  return h * 60 * 60 * 1000;
}