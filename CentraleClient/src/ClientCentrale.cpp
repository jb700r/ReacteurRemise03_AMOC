#include "ClientCentrale.h"
#include <HTTPClient.h>
#include "config.h"
#include <ArduinoJson.h>
#include "Board/DEL.h"

ClientCentrale::ClientCentrale()
{
    Serial.println("Initialisation du client");
    this->m_delRouge = new DEL(DEL_ROUGE);
    this->m_delVerte = new DEL(DEL_VERTE);
}

void ClientCentrale::interrogerCoeur()
{
    HTTPClient http;
    http.begin(SERVER_URL);
    int httpReponse = http.GET();

    String reponse = http.getString();

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, reponse);
    String etat = doc["etat"];

    http.end();
    gestionDEL(etat);
    this->m_etat = etat;
}

void ClientCentrale::ChangerEtatReacteur()
{

    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    String json;
    if (this->m_etat == "actif")
    {
        json = "{\"etat\":\"repos\"}";
    }
    else
    {
        json = "{\"etat\":\"actif\"}";
    }
    int codeRetour = http.PUT(json);
    if (codeRetour == HTTP_CODE_OK)
    {
        Serial.println("Changement d'état effectué");
    }
    else
    {
        Serial.println("Erreur lors du changement d'état"); 
    }
    http.end();
}

void ClientCentrale::gestionDEL(String etat)
{
    if (etat == "actif")
    {
        m_delRouge->allumer();
        m_delVerte->eteindre();
    }
    else if (etat == "repos")
    {
        m_delRouge->eteindre();
        m_delVerte->allumer();
    }
}
