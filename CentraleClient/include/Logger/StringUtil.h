#pragma once

#include <Arduino.h>

class StringUtil {
public:
  static String padLeft(const String &value, char padChar, unsigned int length);
};