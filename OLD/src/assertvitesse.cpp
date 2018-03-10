#include <Arduino.h>
#include "assertvitesse.hpp"
#include "variables.hpp"
#include <FlexiTimer2.h>
#include <digitalWriteFast.h>
#include "moteurs.hpp"


volatile long ticksCodeur1 = 0;
volatile long ticksCodeur2 = 0;

volatile double dt = CADENCE_MS/1000.;
volatile double temps = -CADENCE_MS/1000.;

volatile double omega;
volatile double commande = 0.;
volatile double vref = 3.14;

// PID
volatile double Kp = 0.29;
volatile double Ki = 8.93;
volatile double P_x = 0.;
volatile double I_x = 0.;
volatile double ecart = 0.;





void GestionInterruptionCodeurPinA1()
{
  if (digitalReadFast(CODEUSE_1_A) == digitalReadFast(CODEUSE_1_B)) {
    ticksCodeur1--;
  }
  else {
    ticksCodeur1++;
  }
}


void GestionInterruptionCodeurPinB1()
{
  if (digitalReadFast(CODEUSE_1_A) == digitalReadFast(CODEUSE_1_B)) {
    ticksCodeur1++;
  }
  else {
    ticksCodeur1--;
  }
}



void GestionInterruptionCodeurPinA2()
{
  if (digitalReadFast(CODEUSE_2_A) == digitalReadFast(CODEUSE_2_B)) {
    ticksCodeur2--;
  }
  else {
    ticksCodeur2++;
  }
}


void GestionInterruptionCodeurPinB2()
{
  if (digitalReadFast(CODEUSE_2_A) == digitalReadFast(CODEUSE_2_B)) {
    ticksCodeur2++;
  }
  else {
    ticksCodeur2--;
  }
}

void isrt(){

  int codeurDeltaPos;

  // Nombre de ticks codeur depuis la dernière fois
  codeurDeltaPos = ticksCodeur1;
  ticksCodeur1 = 0;

  // Calcul de la vitesse de rotation
  omega = ((2.*3.141592*((double)codeurDeltaPos))/1632.)/dt;  // en rad/s

  /******* Régulation PID ********/
  // Ecart entre la consigne et la mesure
  ecart = vref - omega;

  // Terme proportionnel
  P_x = Kp * ecart;

  // Calcul de la commande
  commande = P_x + I_x;

  // Terme intégral (sera utilisé lors du pas d'échantillonnage suivant)
  I_x = I_x + Ki * dt * ecart;
  /******* Fin régulation PID ********/

  // Envoi de la commande au moteur
  moteurDroit(commande);
  moteurGauche(commande);
  temps += dt;
}




void init()
{
  // Codeur incrémental 1
  pinMode(CODEUSE_1_A, INPUT);      // entrée digitale pin A codeur
  pinMode(CODEUSE_1_B, INPUT);      // entrée digitale pin B codeur
  digitalWrite(CODEUSE_1_A, HIGH);  // activation de la résistance de pullup
  digitalWrite(CODEUSE_1_B, HIGH);  // activation de la résistance de pullup
  attachInterrupt(CODEUSE_1_A_I, GestionInterruptionCodeurPinA1, CHANGE);
  attachInterrupt(CODEUSE_1_B_I, GestionInterruptionCodeurPinB1, CHANGE);
  // Codeur incrémental 2
  pinMode(CODEUSE_2_A, INPUT);      // entrée digitale pin A codeur
  pinMode(CODEUSE_2_B, INPUT);      // entrée digitale pin B codeur
  digitalWrite(CODEUSE_2_A, HIGH);  // activation de la résistance de pullup
  digitalWrite(CODEUSE_2_B, HIGH);  // activation de la résistance de pullup
  attachInterrupt(CODEUSE_2_A_I, GestionInterruptionCodeurPinA2, CHANGE);
  attachInterrupt(CODEUSE_2_B_I, GestionInterruptionCodeurPinB2, CHANGE);
  // Compteur d'impulsions de l'encodeur
  ticksCodeur1 = 0;
  ticksCodeur2 = 0;
  // La routine isrt est exécutée à cadence fixe
  FlexiTimer2::set(CADENCE_MS, 1/1000., isrt); // résolution timer = 1 ms
  FlexiTimer2::start();
}
