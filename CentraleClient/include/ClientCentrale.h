#pragma once
#include <Arduino.h>
#include "Board/DEL.h"

class ClientCentrale
{
public:
    ClientCentrale();
    void interrogerCoeur();
    void ChangerEtatReacteur();

private:
    DEL *m_delRouge;
    DEL *m_delVerte;
    void gestionDEL(String etat);

private:
    String m_etat;
};