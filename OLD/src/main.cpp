#include <Arduino.h>
#include "variables.hpp"
//#include <FlexiTimer2.h>
#include "main.hpp"
//#include "assertvitesse.hpp"
//#include "moteurs.hpp"

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;


void setup() {
    // put your setup code here, to run once:
    //init();
    //Serial.begin(9600);
    //initMoteurs();
}

void loop() {
    // put your main code here, to run repeatedly:
  //  moteurDroit(100);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enB, 50);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
    analogWrite(enA, 50);
}
