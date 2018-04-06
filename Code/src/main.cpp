#include <Arduino.h>
#include <FlexiTimer2.h>//rend inutilisable les pin 9 et 10 l'arduino mega
//#include "main.hpp"
//#include "assertvitesse.hpp"
#include "moteurs.hpp"
#include "ligne.hpp"
#include "constantes.hpp"
#include "branchements.hpp"
#include "asservissement.hpp"


/*
     .--._____,
  .-='=='==-, "
 (O_o_o_o_o_O)
*/

void setup()
{
    // put your setup code here, to run once:
    //init();
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial.println("#################################################################################");
    Serial.println("                                  Salut, Oh un char ascii ;-) ");
    Serial.println("                                   .--._____,   ");
    Serial.println("                                .-='=='==-, `   ");
    Serial.println("                           .   (O_o_o_o_o_O)     /");
    Serial.println("                            '''''''''''''''''''''    ");
    Serial.println("##################################################################################");

    resetCodeuse();
    FlexiTimer2::set(30, assert); // 500ms period
    FlexiTimer2::start();
    initMoteurs();
    //assertInit();
}

void loop()
{
  //moteurDroit(100);
  //moteurGauche(-254);


}
