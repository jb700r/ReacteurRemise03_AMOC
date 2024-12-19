#pragma once

class DEL{
    public:
        DEL(int pin);
        void allumer();
        void eteindre();
    private:
        int pin;
};