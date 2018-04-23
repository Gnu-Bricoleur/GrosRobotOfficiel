#include  <Arduino.h>
#include "positionnement.hpp"
#include "asservissement.hpp"



char consignes[] = {'D', 'A','D','A','D', 'T', 'E'};
int val[] = {       5000, 200,1000, -200, 1000, 90  };
int etat = 0;
extern bool finduMvt;


void positionnement()
{
  if(finduMvt == true)
  {
    Serial.println(consignes[etat]);
    finduMvt = false;
    etat += 1;
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
