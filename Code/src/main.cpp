#include <Arduino.h>
//#include <FlexiTimer2.h>
//#include "main.hpp"
//#include "assertvitesse.hpp"
#include "moteurs.hpp"
#include "ligne.hpp"
#include "constantes.hpp"
#include "branchements.hpp"



void setup() {
    // put your setup code here, to run once:
    //init();
    Serial.begin(9600);
    //initMoteurs();
}

void loop() {
    // put your main code here, to run repeatedly:
    if(centre())
    {
      moteurDroit(70);
      moteurGauche(70);
    }
    else if (gauche())
    {
      moteurDroit(40);
      moteurGauche(70);
    }
    else
    {
      moteurDroit(70);
      moteurGauche(40);
    }

}
