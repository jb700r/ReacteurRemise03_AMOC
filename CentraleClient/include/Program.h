#pragma once
#include "ClientCentrale.h"
#include <Arduino.h>
#include "Timer.h"
#include "Board/Bouton.h"

class Program{
public:
    Program();
    void loop();

private:
    void connexionReseau(String ssid, String password);
    ClientCentrale *m_client;
    Timer* m_timer;
    Bouton* m_bouton;
};
