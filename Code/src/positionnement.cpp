#include  <Arduino.h>
#include "positionnement.hpp"
#include "asservissement.hpp"



char consignes[] = {'A', 'A','D','A','D', 'T', 'E'};
int val[] = {       100, 100,10000, -200, 1000, 90  };
int etat = 0;
extern bool finduMvt;


void positionnement()
{
  if(finduMvt == true)                          //ATTENTION POUR LE PASSAGE D4EATA DESACTIVE POUR L4INSTANT
  {
    Serial.println(consignes[etat]);
    finduMvt = false;
    //etat += 1;
    stopRobot();
    //delay(10000);
  }
    switch(consignes[etat])
    {
      case 'A':
        avancerdroit(val[etat]);
        break;
      case 'T':
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
