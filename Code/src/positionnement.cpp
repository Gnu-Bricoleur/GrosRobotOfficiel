#include  <Arduino.h>
#include "positionnement.hpp"
#include "asservissement.hpp"



char consignes[] = {'D', 'A',  'A',  'T',  'A', 'E'};
int val[] = {       100, 200,  -200, 90 ,  200 };
int etat = 0;
extern bool finduMvt;


void positionnement()
{
  if(finduMvt == true)
  {
    finduMvt = false;
    etat = etat++;
    stopRobot();
    delay(500);
  }
  else
  {
    switch(consignes[etat])
    {
      case 'A':
        avancerdroit(val[etat]);
        break;
      case 'T':
        break;
      case 'D':
        break;
      case 'E':
        stopRobot();
        while(1);
        break;
    }
  }
}
