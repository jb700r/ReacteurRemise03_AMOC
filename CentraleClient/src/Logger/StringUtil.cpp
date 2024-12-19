#include "Logger/StringUtil.h"

String StringUtil::padLeft(const String &value, char padChar, unsigned int length) {
  String result = value;
  while (result.length() < length) {
    result = padChar + result;
  }
  return result;
}