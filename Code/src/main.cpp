#include <Arduino.h>
#include <FlexiTimer2.h>//rend inutilisable les pin 9 et 10 l'arduino mega
//#include "main.hpp"
//#include "assertvitesse.hpp"
#include "moteurs.hpp"
#include "ligne.hpp"
#include "constantes.hpp"
#include "branchements.hpp"
#include "asservissement.hpp"
#include "positionnement.hpp"
#include "obstacles.hpp"
#include "fonctions.hpp"

extern unsigned long duree;

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

    assertInit();
    resetCodeuse();
    // FlexiTimer2::set(50, assert); // 500ms period
    // FlexiTimer2::start();
    initMoteurs();
    initObstacles();

    //On bloque le demarrage
    TireLaTirette();
    Serial.println("Attenzion zest partiii");
    // moteurGauche(100);
    // moteurDroit(100);
    initTemps();
    //delay(2000);

}

void loop()
{
  Serial.println("Hep !");
  assertpls();
  detectobstacle();
  verifTemps();
  Serial.println(duree);

  
  // assert();
  // positionnement();


}
