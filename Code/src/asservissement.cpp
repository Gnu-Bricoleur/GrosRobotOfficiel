#include <Arduino.h>
#include "asservissement.hpp"

float codeuseDroite = 0;
float codeuseGauche = 0;

//Constantes permettant la transformation tic / millimètre
const double coeffGLong = 0.12;
const double coeffDLong = 0.12;

//Constantes permettant la transformation tic / degrés
const double coeffGAngl = 0.0001;
const double coeffDAngl = 0.0001;



// Déclaration des variables globales

// Variables (compteurs) qui vont stocker
// le nombre de tics comptés pour chaque codeur
long comptD = 0;
long comptG = 0;


//Variables allant contenir les positions du robots
double xR = 0.;
double yR = 0.;

//Variables permettant de stocker la position de la cible du robot
double xC = 1000;
double yC = 1000;

//Variables allant contenir les delta position et angle
double dDist = 0.;
double dAngl = 0.;

//Variable contenant le cap du robot
double orientation = 0.;

//Variable contenant l'angle entre le robot et la cible
double consigneOrientation = 0.;

//Variable permettant de savoir si la cible est à gauche ou à droite du robot.
int signe = 1;

//Variable contenant la distance entre le robot et la cible
double distanceCible = 0.;






void assert()
{

  recupCodeuse();
  //Serial.println(codeuseDroite);
  comptD = codeuseDroite;
  comptG = codeuseGauche;

  if ( abs(comptD) < 5 && abs(comptG) < 5)
  {
    comptD = 0;
    comptG = 0;
  }

  dDist = (coeffGLong*comptG + coeffDLong*comptD)/2.;
	dAngl = coeffDAngl*comptD - coeffGAngl*comptG;

	//Actualisation de la position du robot en xy et en orientation
	xR += dDist*cos(dAngl);
	yR += dDist*sin(dAngl);
	orientation += dAngl;

	//On calcule la distance séparant le robot de sa cible
	distanceCible = sqrt((xC-xR)*(xC-xR)+(yC-yR)*(yC-yR));

	//On regarde si la cible est à gauche ou à droite du robot
	if(yR > yC)
	{
		signe = 1;
	}else
	{
		signe = -1;
	}

	//On calcule l'angle entre le robot et la cible
	consigneOrientation = signe * acos((xC-xR)/((xC-xR)*(xC-xR)*(yC-yR)*(yC-yR)));


if (dDist != 0)
{
  Serial.print("Distance : ");
  Serial.println(dDist);
  Serial.print("Angle : ");
  Serial.println(dAngl);
  Serial.print("XR : ");
  Serial.println(xR);
  Serial.print("XY : ");
  Serial.println(yR);
  Serial.print("Angle : ");
  Serial.println(dAngl);
  Serial.println("-------------------------------------");
}
  resetCodeuse();


}

void recupCodeuse()
{
  Serial1.println("a");

  String data[10];
  String content = "";



  char carlu = 0; //variable contenant le caractère à lire
    int cardispo = 0; //variable contenant le nombre de caractère disponibles dans le buffer
    cardispo = Serial1.available();
  //Serial.println(cardispo);
    while(cardispo > 0) //tant qu'il y a des caractères à lire
    {
        carlu = Serial1.read(); //on lit le caractère
        //Serial.print(carlu); //puis on le renvoi à l’expéditeur tel quel
        content.concat(carlu);
        cardispo = Serial1.available(); //on relit le nombre de caractères dispo
    }

    splitString(content, ';', data);
    codeuseDroite = data[0].toFloat();
    codeuseGauche = data[1].toFloat();

    // Serial.print(codeuseDroite);
    // Serial.print(" ; ");
    // Serial.println(codeuseGauche);


    //delay(1000);

}


void resetCodeuse()
{
    Serial1.println("R");
}



void splitString(String message, char separator, String* data) {
    int index = 0;
    int cnt;
    for(int i=0; i<10;i++)
      {
        data[i]="";
      }
    cnt = 0;
      do {
        index = message.indexOf(separator);
        if(index != -1) {// s'il y a bien un caractère séparateu
            // on découpe la chaine et on stocke le bout dans le tableau
            data[cnt] = message.substring(0,index);
            cnt++;
            // on enlève du message le bout stocké
            message = message.substring(index+1, message.length());
        } else {
           // après le dernier espace
           // on s'assure que la chaine n'est pas vide
           if(message.length() > 0) {

             data[cnt] = message.substring(0,index); // dernier bout
             cnt++;
           }
        }
     } while(index >=0); // tant qu'il y a bien un séparateur dans la chaine

  }