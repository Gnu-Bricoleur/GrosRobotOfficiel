#include <Arduino.h>
#include "obstacles.hpp"
#include "branchements.hpp"
#include "moteurs.hpp"


int trig = 15;
int echo = 14;
long lecture_echo;
long cm;





void detectobstacle()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo / 58;
  Serial.println(cm);

  if(cm < 50)
  {
    Serial.println("obstacle");
    moteurGauche(-50);
    moteurDroit(-50);
    delay(200);
    while(1)
    {
      moteurGauche(0);
      moteurDroit(0);
    }
    //digitalWrite(13, LOW);
  }

  // Serial.println(analogRead(A15));
  // Serial.println(analogRead(A14));
if (analogRead(A14) > 150)
{
  Serial.println("obstacle");
  moteurGauche(-50);
  moteurDroit(-50);
  delay(200);
  while(1)
  {
    moteurGauche(0);
    moteurDroit(0);
  }
}

  // static int count = 0;
  // static bool obs = false;
  //
  // if (digitalRead(OBSTACLE) == HIGH)
  // {
  //   count += 1;
  // }
  //
  //
  // while(digitalRead(OBSTACLE) == LOW /*&& count == 1*/)
  // {
  //   count = 0;
  //   moteurGauche(0);
  //   moteurDroit(0);
  //   Serial.println("Obstacle !!");
  //
  // }
}

void initObstacles()
{
  // pinMode(OBSTACLE, INPUT_PULLUP);
    pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  pinMode(INFRA_DROIT, INPUT);
  pinMode(INFRA_GAUCHE, INPUT);
}
