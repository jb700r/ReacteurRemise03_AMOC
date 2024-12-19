#include "Logger/BasicCommandInterpretor.h"

#include <Arduino.h>
#include <Stream.h>

#include "Logger/Logger.h"

#include "Logger/Device.h"
#include "Logger/StringUtil.h"

#ifdef ESP32
#include <ESP.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <vector>
#endif

BasicCommandInterpretor::BasicCommandInterpretor(Stream &stream)
    : m_stream(stream), m_lastSerialInput("") {
  ;
}

void BasicCommandInterpretor::tick() {
  while (this->m_stream.available()) {
    char c = this->m_stream.read();
    this->m_stream.print(c);
    if (c == '\n') {
      this->executeCommand(m_lastSerialInput);
      this->m_lastSerialInput = "";
    } else {
      this->m_lastSerialInput += c;
    }
  }
}

bool BasicCommandInterpretor::executeCommand(const String &command) {
  String cmd = command;

  String parameters = "";
  int index = cmd.indexOf(' ');
  if (index != -1) {
    parameters = cmd.substring(index + 1);
    cmd = cmd.substring(0, index);
  }
  cmd.trim();
  parameters.trim();

  Logger.verboseln(String(F("> ")) + cmd + " " + parameters);

  return this->interpret(cmd, parameters);
}

bool BasicCommandInterpretor::interpret(const String &command,
                                        const String &parameters) {
  bool error = false;

  if (command == "hello") {
    Logger.println(F("Hello, world!"));
  } else if (command == "set") {
    String key = parameters.substring(0, parameters.indexOf(' '));
    String value = parameters.substring(parameters.indexOf(' ') + 1);
    error = !this->setParameter(key, value);
  } else if (command == "get") {
    String key = parameters;
    error = !this->getParameter(key);
  } else if (command == "id") {
    Logger.println(String(F("ID: ")) + Device::getId());
  } 
#ifdef ESP32
  else if (command == "reboot") {
    Logger.infoln(F("Rebooting..."));
    ESP.restart();
  } 
#endif  
  else if (command == "scan") {
    String deviceType = parameters;

    if (deviceType == "i2c") {
      #ifdef ARDUINO_AVR_UNO
      SimpleCollection<uint16_t> i2cAddresses = Device::getI2CAddresses();
      #elif ESP32
      std::vector<uint16_t> i2cAddresses = Device::getI2CAddresses();
      #endif
      Logger.println(F("I2C addresses:"));
      for (size_t i = 0; i < i2cAddresses.size(); i++) {
        Logger.println(String(F("  - 0x")) +
                       StringUtil::padLeft(String(i2cAddresses[i], HEX), 2, '0'));
      }
      Logger.println(String(F("")));
    } 
    #ifdef ESP32
    else if (deviceType == "wifi") {
      std::vector<WiFiNetwork> networks = Device::getWiFiNetworks();
      Logger.println(F("Wifi networks:"));
      for (size_t i = 0; i < networks.size(); i++) {
        String encryption = "unknown";
        switch (networks[i].encryptionType) {
          case (WIFI_AUTH_OPEN):
            encryption = "Open";
            break;
          case (WIFI_AUTH_WEP):
            encryption = "WEP";
            break;
          case (WIFI_AUTH_WPA_PSK):
            encryption = "WPA_PSK";
            break;
          case (WIFI_AUTH_WPA2_PSK):
            encryption = "WPA2_PSK";
            break;
          case (WIFI_AUTH_WPA_WPA2_PSK):
            encryption = "WPA_WPA2_PSK";
            break;
          case (WIFI_AUTH_WPA2_ENTERPRISE):
            encryption = "WPA2_ENTERPRISE";
            break;
        }
        Logger.println(
            String(F("  - ")) + networks[i].ssid + String(F(" (")) +
            encryption + String(F(") : ")) + String(networks[i].rssi) +
            String(F(" dBm - ")) +
            String(constrain((100.0 + networks[i].rssi) * 2, 0, 100)) +
            String(F("% - BSSID: ")) + networks[i].bssid);
      }
      Logger.println("");
    }
    #endif
     else {
      Logger.errorln(String(F("Unknown device type ")) + deviceType);
    }
  } 
  #ifdef ESP32
  else if (command == "flash") {
    Logger.println(String(F("Flash size: ")) + ESP.getFlashChipSize() +
                   String(F(" bytes")));
    Logger.println(String(F("Flash speed: ")) + ESP.getFlashChipSpeed() +
                   String(F(" Hz")));
    Logger.println(String(F("Flash mode: ")) + ESP.getFlashChipMode());
  } else if (command == "network") {
    Logger.println(String(F("Network: ")));
    Logger.println(String(F("  - SSID: ")) + WiFi.SSID());
    Logger.println(String(F("  - IP: ")) + WiFi.localIP().toString());
    Logger.println(String(F("  - MAC: ")) + WiFi.macAddress());
    Logger.println(String(F("  - RSSI: ")) + String(WiFi.RSSI()) +
                   String(F(" dBm")));
    Logger.println(String(F("  - Channel: ")) + String(WiFi.channel()));
    Logger.println(String(F("  - DNS: ")) + WiFi.dnsIP().toString());
    Logger.println(String(F("  - DNS: ")) + WiFi.dnsIP(1).toString());
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    Logger.println(String(F("  - SSID: ")) + String((char *)conf.sta.ssid));
    Logger.verboseln(String(F("  - Password: ")) +
                     String((char *)conf.sta.password));

    Logger.println(String(F("")));
  }
#endif
  else if (command == "help") {
    Logger.println(F("Available commands:"));
    Logger.println(F("  hello"));
    Logger.println(F("  id"));
    Logger.println(F("  set <key> <value>"));
    Logger.println(F("  get <key>"));
#ifdef ESP32
    Logger.println(F("  scan i2c|wifi"));
    Logger.println(F("  reboot"));
    Logger.println(F("  flash"));
    Logger.println(F("  network"));
#elif ARDUINO_AVR_UNO
    Logger.println(F("  scan i2c"));
#endif
    Logger.println(F(""));
    Logger.println(F("  help"));
  } else {
    Logger.errorln(String(F("Unknown command: ")) + command);
    error = true;
  }

  return !error;
}

bool BasicCommandInterpretor::getParameter(const String &key) {
  bool error = false;

  if (key == "debug") {
    Logger.println(String(F("debug: ")) + Logger.getLoggerLevel());
  } else {
    Logger.errorln(F("get : Invalid key"));
    error = true;
  }

  return !error;
}

bool BasicCommandInterpretor::setParameter(const String &key,
                                           const String &value) {
  bool error = false;

  if (key == "debug") {
    int debugLevel = value.toInt();
    if (debugLevel > 0 && debugLevel <= 4) {
      Logger.setLoggerLevel((LoggerLevel)debugLevel);
    } else {
      Logger.errorln(F("Invalid debug level"));
    }
  } else {
    Logger.errorln(F("set : Invalid key"));
    error = true;
  }

  return !error;
}