#pragma once
#include <Arduino.h>
#include "Action/ActionBoutonPressee.h"
#define MIN_DELAIS_PRESSION 50


class Bouton
{
private:
    uint8_t pin;
    int dernierEtatBouton;
    int dernierEtatStableBouton;
    long derniereDateChangement;
    ActionBoutonPressee *m_action;

public:
    Bouton(uint8_t p_pinBouton, ActionBoutonPressee *p_action);
    void tick();
};