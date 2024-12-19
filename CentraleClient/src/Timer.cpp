#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long interval, std::function<void()> callback)
    : m_nextTime(0), m_interval(interval), m_callback(callback) {
  ;
}

void Timer::tick() {
  unsigned long now = millis();
  if (now >= this->m_nextTime) {
    while (now >= this->m_nextTime ) {
      this->m_nextTime += this->m_interval;
    }
    this->m_callback();
  }
}