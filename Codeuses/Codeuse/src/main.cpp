#include "Arduino.h"


/*
Code pour la carte arduino en charge des codeuses


*/

//Declarations globales


int codeuseDroite = 2;//Pins sur lesquels la codeuse est branchée
int codeuseGauche = 3;


//Variables globales intermédiaires
double ticksDroit = 0;
double ticksGauche = 0;
double X = 0;
double Y = 0;

//prototypes
void incDroit();
void incGauche();

void setup() {
  Serial.begin(9600);
  pinMode(codeuseDroite, INPUT_PULLUP);
  pinMode(codeuseGauche, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  attachInterrupt(0, incDroit, RISING);
  attachInterrupt(1, incGauche, RISING);
}

void loop() {

  int donneesALire = Serial.available(); //lecture du nombre de caractères disponibles dans le buffer
  if(donneesALire > 0) //si le buffer n'est pas vide
  {
      char choseLue = Serial.read();
      //Serial.println(choseLue);
      //Serial.flush();
      if (choseLue == 'R')
      {
        ticksDroit = 0;
        ticksGauche = 0;
      }
      else if (choseLue == 'a')
      {
        Serial.print(ticksDroit);
        Serial.print(";");
        Serial.println(-ticksGauche);
      }
  }
}


void incDroit()
{
  if (digitalRead(4)==HIGH)
  {
    ticksDroit +=1;
  }
  else
  {
    ticksDroit -=1;
  }
}

void incGauche()
{
  if (digitalRead(5)==LOW)
  {
    ticksGauche +=1;
  }
  else
  {
    ticksGauche -=1;
  }
}
