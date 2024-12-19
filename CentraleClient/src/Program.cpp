#include "Program.h"
#include <Arduino.h>
#include "config.h"
#include <WiFi.h>

Program::Program()
: m_client(nullptr), m_timer(nullptr)
{
    connexionReseau(WIFI_SSID, WIFI_PASSWORD);
    m_client = new ClientCentrale();
    m_timer = new Timer(2_secondes, [this](){
        this->m_client->interrogerCoeur();
    });
    m_bouton = new Bouton(PIN_BOUTON, new ActionBoutonPressee(m_client));
    
}

void Program::connexionReseau(String ssid, String password)
{
    const uint8_t nbEssaisMaximum = 30;
    uint8_t nbEssais = 0;

    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("Connexion : ");
    while (nbEssais < nbEssaisMaximum && WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        nbEssais++;
    }
    Serial.println("");

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("Connecté au réseau WiFi, adresse IP : ");
        Serial.println(WiFi.localIP());
        Serial.println("");
    }
    else{
        Serial.println("Impossible de se connecter au réseau WiFi");
        Serial.println("Connexion au point d'acces");
        connexionReseau(WIFI_SSID_ACCESS_POINT, WIFI_PASSWORD_ACCESS_POINT);
    }
}



void Program::loop()
{
    m_timer->tick();
    m_bouton->tick();
}