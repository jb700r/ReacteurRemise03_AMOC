#pragma once

#include <Arduino.h>

#include <Stream.h>

enum LoggerLevel { ERROR = 1, WARNING = 2, INFO = 3, VERBOSE = 4 };

class LoggerImpl {
 public:
  void begin(Stream *Stream);

  void error(const String &value, bool writePrefix = true);
  void errorln(const String &value, bool writePrefix = true);
  void error(const char *value, bool writePrefix = true);
  void errorln(const char *value, bool writePrefix = true);

  void warning(const String &value, bool writePrefix = true);
  void warningln(const String &value, bool writePrefix = true);
  void warning(const char *value, bool writePrefix = true);
  void warningln(const char *value, bool writePrefix = true);

  void info(const String &value, bool writePrefix = true);
  void infoln(const String &value, bool writePrefix = true);
  void info(const char *value, bool writePrefix = true);
  void infoln(const char *value, bool writePrefix = true);

  void verbose(const String &value, bool writePrefix = true);
  void verboseln(const String &value, bool writePrefix = true);
  void verbose(const char *value, bool writePrefix = true);
  void verboseln(const char *value, bool writePrefix = true);

  void print(const String &value, bool writePrefix = true);
  void println(const String &value, bool writePrefix = true);

  static String millisToTime(unsigned long millis);

  void setLoggerLevel(LoggerLevel loggerLevel);
  LoggerLevel getLoggerLevel();

 private:
  Stream *m_stream = nullptr;
  LoggerLevel m_loggerLevel = LoggerLevel::INFO;
};

extern LoggerImpl Logger;

#define LOGGER_BEGIN_METHOD  Logger.verboseln(String(__FILE__) + String(F(" - ")) + String(__FUNCTION__) + String(F(": begin")));
#define LOGGER_END_METHOD    Logger.verboseln(String(__FILE__) + String(F(" - ")) + String(__FUNCTION__) + String(F(": end")));
#define LOGGER_VAR(var)      Logger.verboseln(String(__FILE__) + String(F(" - ")) + String(__FUNCTION__) + String(F(": @")) + String(__LINE__) + String(F(" - ")) + String(#var) + String(F(" = ")) + String(var));