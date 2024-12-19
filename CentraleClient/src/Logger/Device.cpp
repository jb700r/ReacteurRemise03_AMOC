#include "Logger/Device.h"

#include <Wire.h>
#ifdef ESP32
#include <WiFi.h>
#endif

#include "Logger/Logger.h"

#include "Logger/StringUtil.h"

String Device::getId() {
#ifdef ESP32
  uint32_t macPart = ESP.getEfuseMac() & 0xFFFFFFFF;
  return String(macPart, HEX);
#elif ARDUINO_AVR_UNO
  return String("Undefined");
#else
  #error "Unsupported platform";
#endif

}
#ifdef ARDUINO_AVR_UNO
SimpleCollection<uint16_t> Device::getI2CAddresses() {
#elif ESP32
std::vector<uint16_t> Device::getI2CAddresses() {
#endif
  byte error, address;
#ifdef ARDUINO_AVR_UNO
  SimpleCollection<uint16_t> i2cAddresses;
#elif ESP32
  std::vector<uint16_t> i2cAddresses;
#endif

  Logger.infoln(F("Scanning I2C devices..."));

  Wire.begin();
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Logger.verboseln(String(F("Sanning I2C devices at address 0x")) +
                     StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Logger.verboseln(String(F("I2C device found at address 0x")) +
                       StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
      ;

      i2cAddresses.push_back(address);
      nDevices++;
    } else if (error == 4) {
      Logger.infoln(String(F("Unknown error at address 0x")) +
                    StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
    }
  }
  if (nDevices == 0) {
    Logger.infoln(F("No I2C devices found."));
  } else {
    Logger.infoln(F("done."));
  }

  return i2cAddresses;
}

#ifdef ESP32
std::vector<WiFiNetwork> Device::getWiFiNetworks() {
  std::vector<WiFiNetwork> networks;
  WiFi.scanNetworks();
  for (int i = 0; i < WiFi.scanComplete(); i++) {
    WiFiNetwork network;
    network.ssid = WiFi.SSID(i);
    network.rssi = WiFi.RSSI(i);
    network.encryptionType = WiFi.encryptionType(i);
    network.bssid = WiFi.BSSIDstr(i);
    networks.push_back(network);
  }
  return networks;
}
#endif