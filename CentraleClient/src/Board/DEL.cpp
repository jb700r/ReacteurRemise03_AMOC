#include "Board/DEL.h"
#include <Arduino.h>

DEL::DEL(int pin){
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void DEL::allumer(){
    digitalWrite(pin, HIGH);
}

void DEL::eteindre(){
    digitalWrite(pin, LOW);
}