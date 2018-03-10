#include <Arduino.h>
#include "variables.hpp"
#include "moteurs.hpp"

// // motor one
// int enA = 10;
// int in1 = 9;
// int in2 = 8;
// // motor two
// int enB = 5;
// int in3 = 7;
// int in4 = 6;


void initMoteurs()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void moteurDroit(double commande)
{
if (commande > 0)
  {
    Serial.println("Go !");
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB, commande);
  }
  else
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB, -commande);
  }
}

void moteurGauche(double commande)
{
  if (commande > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enA, commande);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
    analogWrite(enA, -commande);
  }

}
