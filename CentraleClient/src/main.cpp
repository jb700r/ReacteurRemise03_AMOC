#include <Arduino.h>
#include "Program.h"
#include "Logger/Logger.h"

Program *program;
void setup() {
    Serial.begin(115200);
    Logger.begin(&Serial);
    
    program = new Program();
}

void loop() {
  program->loop();
}
