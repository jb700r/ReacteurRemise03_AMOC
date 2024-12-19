#include "Action/ActionBoutonPressee.h"
#include "Arduino.h"
ActionBoutonPressee::ActionBoutonPressee(ClientCentrale *p_client)
{
    this->m_client = p_client;
}
void ActionBoutonPressee::executer()
{
    this->m_client->ChangerEtatReacteur();
}