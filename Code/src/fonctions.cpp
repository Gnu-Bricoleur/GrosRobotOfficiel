#include <Arduino.h>
#include "fonctions.hpp"
#include "moteurs.hpp"
#include "branchements.hpp"

unsigned long duree;

unsigned long debut;

void initTemps()
{
  debut = millis();

}

void verifTemps()
{
  duree = millis() - debut;
  if ((millis() - debut) > 90000)
  {
    moteurDroit(0);
    moteurGauche(0);
    //Autres ationneurs
    while(1)
    {
      Serial.println("Fin du match");
    }
  }
}

void TireLaTirette()
{
  Serial.println(digitalRead(TIRETTE));
  while(digitalRead(TIRETTE) == HIGH)
  {
    Serial.println("Et la bobinette cherra !");
  }
}
