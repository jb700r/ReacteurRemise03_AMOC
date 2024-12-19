#include "Board/Bouton.h"

Bouton::Bouton(uint8_t p_pinBouton, ActionBoutonPressee *p_action)
    : pin(p_pinBouton),
      dernierEtatBouton(HIGH),
      dernierEtatStableBouton(HIGH),
      derniereDateChangement(0),
      m_action(p_action)
{
    pinMode(this->pin, INPUT);
}

void Bouton::tick()
{
    int etatBouton = digitalRead(this->pin);
    long dateActuelle = millis();
    if (etatBouton != dernierEtatBouton)
    {
        derniereDateChangement = dateActuelle;
        dernierEtatBouton = etatBouton;
    }
    if (dateActuelle - derniereDateChangement > MIN_DELAIS_PRESSION)
    {
        if (dernierEtatStableBouton == HIGH && etatBouton == LOW)
        {
            // rien a faire ici dans notre cas.
        }
        else if (dernierEtatStableBouton == LOW && etatBouton == HIGH)
        {
            // ICI
            Serial.println("Bouton pressé");
            m_action->executer();
            

        }
        dernierEtatStableBouton = etatBouton;
    }
}