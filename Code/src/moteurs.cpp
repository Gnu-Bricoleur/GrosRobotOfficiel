#include <Arduino.h>
#include "branchements.hpp"
#include "moteurs.hpp"

int enA = EN_A;
int in1 = IN_1;
int in2 = IN_2;

int enB = EN_B;
int in3 = IN_3;
int in4 = IN_4;

void moteurDroit(double commande)
{
if (commande > 0)
  {
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

void moteurStop()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enA, 0);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB, 0);

}


void initMoteurs()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
