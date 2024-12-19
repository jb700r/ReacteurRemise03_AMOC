#pragma once
#include "Action.h"
#include "ClientCentrale.h"

class ActionBoutonPressee : public Action
{
public:
    ActionBoutonPressee(ClientCentrale *p_client);
    void executer() override;

private:
    ClientCentrale *m_client;
};