#include "Logger/SpecificCommandInterpretor.h"
#include "Logger/Logger.h"

SpecificCommandInterpretor::SpecificCommandInterpretor(Stream &stream, ClientCentrale *client)
    : BasicCommandInterpretor(stream), m_client(client)
{
    ;
}

bool SpecificCommandInterpretor::interpret(const String &command,
                                           const String &parameters)
{
    bool error = false;

    if (command == "specific")
    {
        Logger.println(F("specific Hello, world!"));
    }
    else if (command == "help")
    {
        Logger.println(F(""));
        Logger.println(F("  specific"));
        Logger.println(F(""));
        BasicCommandInterpretor::interpret(command, parameters);
    }
    else if (command == "coeur-reacteur")
    {

        String param = parameters;
        if (param == "status")
        {
            String status = this->m_client->m_etat;
            Logger.println("Le status du coeur reacteur est : ");
            Logger.println(status);
            Logger.println("");
        }
        else if (param == "activer")
        {
            if (this->m_client->m_etat == "actif")
            {
                Logger.println("Le coeur reacteur est deja actif");
                Logger.println("");
            }
            else
            {
                Logger.println("Activation du coeur reacteur");
                Logger.println("");
                this->m_client->ChangerEtatReacteur();
            }
        }
        else if (param == "desactiver")
        {
            if (this->m_client->m_etat == "repos")
            {
                Logger.println("Le coeur reacteur est deja au repos");
                Logger.println("");
            }
            else
            {
                Logger.println("Desactivation du coeur reacteur");
                Logger.println("");
                this->m_client->ChangerEtatReacteur();
            }
        }
    }
    else
    {
        error = !BasicCommandInterpretor::interpret(command, parameters);
    }

    return !error;
}

bool SpecificCommandInterpretor::getParameter(const String &key)
{
    return BasicCommandInterpretor::getParameter(key);
}

bool SpecificCommandInterpretor::setParameter(const String &key,
                                              const String &value)
{
    return BasicCommandInterpretor::setParameter(key, value);
}