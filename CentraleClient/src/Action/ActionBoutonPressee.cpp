#include "Action/ActionBoutonPressee.h"
#include "Arduino.h"
ActionBoutonPressee::ActionBoutonPressee(ClientCentrale *p_client)
{
    this->m_client = p_client;
}
void ActionBoutonPressee::executer()
{
    Serial.println("Bouton pressé");
    this->m_client->ChangerEtatReacteur();
}