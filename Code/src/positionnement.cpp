#include  <Arduino.h>
#include "positionnement.hpp"
#include "asservissement.hpp"



char consignes[] = {'D', 'A','D','T','D', 'T', 'E'};
int val[] = {       2000, 400,1000, 90, 1000, 90  };
int etat = 0;
extern bool finduMvt;
bool bavancer;
bool btourner;

void positionnement()
{
  if(finduMvt == true)                          //ATTENTION POUR LE PASSAGE D4EATA DESACTIVE POUR L4INSTANT
  {
    bavancer = false;
    btourner = false;
    finduMvt = false;
    etat += 1;
    Serial.print("consigne : ");
    Serial.println(consignes[etat]);
    Serial.print("valeur : ");
    Serial.println(val[etat]);
    stopRobot();
    delay(10000);
  }
    switch(consignes[etat])
    {
      case 'A':
        bavancer = true;
        avancerdroit(val[etat]);
        break;
      case 'T':
        btourner = true;
        tourner(val[etat]);
        break;
      case 'D':
        Serial.print("Debut attente");
        Serial.println(val[etat]);
        delay(val[etat]);
        Serial.println("Fin attente");
        finduMvt = true;
        break;
      case 'E':
        stopRobot();
        while(1);
        Serial.println("Fin du match");
        break;

  }
}
