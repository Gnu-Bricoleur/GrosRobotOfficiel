// inspiration : http://rco.fr.nf/index.php/2016/07/03/deplacement-dun-robot/
// https://www.cs.princeton.edu/courses/archive/fall11/cos495/COS495-Lecture5-Odometry.pdf
// https://www.dca.ufrn.br/~adelardo/artigos/ICINCO04a.pdf
// http://projet.eu.org/pedago/sin/term/6-asservissement_arduino.pdf

#include <Arduino.h>
#include "asservissement.hpp"
#include "moteurs.hpp"
#include <EasyTransfer.h>


EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  long codeuseDroiteet;
  long codeuseGaucheet;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE codeuseset;

int delais = 0;
int distanceCibleprec = 0;
long codeuseDroite = 0;
long codeuseGauche = 0;

double ecartangle = 0;

bool finduMvt = false;

//Constantes permettant la transformation tic / millimètre
//40mm de diametere=>40*PImm de distance par 1024 tic de codeuse=>untic = 40*PI/1024
//40*PI/1024 = 0.12271846303
const double coeffGLong = 0.12271846303;
const double coeffDLong = 0.12271846303;

//Constantes permettant la transformation tic / degrés
//ecart codeuses 220mm => 360deg = 220pi mm =>360deg = 220pi/0.122718... tc/360deg => redivise par 360=>
const double coeffGAngl = 0.23560253561/7.22;
const double coeffDAngl = 0.23560253561/7.22;

double diffAngle = 0;

long anciD;
long anciG;


// Déclaration des variables globales

// Variables (compteurs) qui vont stocker
// le nombre de tics comptés pour chaque codeur
long comptD = 0;
long comptG = 0;


//Variables allant contenir les positions du robots
double xR = 0.;
double yR = 0.;

//Variables permettant de stocker la position de la cible du robot
double xC = 0;
double yC = 0;

//Variables allant contenir les delta position et angle
double dDist = 0.;
double dAngl = 0.;

//Variable contenant le cap du robot
double orientation = 0.;
double orientationCible = 0;

//Variable contenant l'angle entre le robot et la cible
double consigneOrientation = 0.;

//Variable permettant de savoir si la cible est à gauche ou à droite du robot.
int signe = 1;

//Variable contenant la distance entre le robot et la cible
double distanceCible = 0.;


//Variables parametrant l'asservissement en angle du robot
double coeffP = 0.45;//0.4;
double coeffD = 0.1;//0.1;
double coeffI = 0.00002;//0.000001;

double coeffProt = 2;
double coeffDrot = 0;
double coeffIrot = 0;


//Variables utilisées pour asservir le robot
double erreurAngle = 0.;
double erreurPre = 0.;
double  deltaErreur = 0.;

//Variables représentant les commandes à envoyer aux moteurs
int cmdG = 0;//Commande gauche
int cmdD = 0; //commande droite

int moteurMax = 100;


double deltaErreurPasAngle = 0;
double ErreurPasAnglePre  =0;

double sommeErreur = 0;

void assertInit()
{
   ET.begin(details(codeuseset), &Serial1);
}



void assert()
{
  recupCodeuse();

  comptD = codeuseDroite - anciD;
  comptG = codeuseGauche - anciG;
  anciD = codeuseDroite;
  anciG = codeuseGauche;

  //calcul deplacement entre deux mvt codeuses
  dDist = (coeffGLong*comptG + coeffDLong*comptD)/2.;
	dAngl = coeffDAngl*comptD - coeffGAngl*comptG;


	//Actualisation de la position du robot en xy et en orientation
	xR += dDist*cos(dAngl/2);
	yR += dDist*sin(dAngl/2);
  orientation += dAngl;

	//On calcule la distance séparant le robot de sa cible
	distanceCible = xC-xR;


	//On calcule l'angle entre le robot et la cible
	consigneOrientation = signe * acos((xC-xR)/((xC-xR)*(xC-xR)*(yC-yR)*(yC-yR)));

  deplaceRobot();

}


void deplaceRobot()
{

  deltaErreurPasAngle = distanceCible - ErreurPasAnglePre;
  ErreurPasAnglePre = deltaErreurPasAngle;
  sommeErreur += distanceCible;

	cmdD = (xC-xR)*coeffP + coeffD*deltaErreurPasAngle + coeffI*sommeErreur;

  if(cmdD > 70)
  {
    cmdD = 70;
  }
  else if(cmdD < -70)
  {
    cmdD = -70;
  }

	cmdG = cmdD;
  ecartangle = (codeuseDroite - codeuseGauche)*0.1;

  ecartangle = 0;     // ON vire al correection en angle, a voir ....

  diffAngle = orientationCible - orientation;

  cmdD += diffAngle*coeffProt;
  cmdG -= diffAngle*coeffProt;

if (finduMvt == false)
{
  moteurDroit(-cmdD + ecartangle);
  moteurGauche(-cmdG - ecartangle);
}
else
{
  moteurDroit(0);
  moteurGauche(0);
}


  finMvt();
}






void recupCodeuse()
{
  Serial1.println("a");
  String data[10];
  String content = "";
  char character;


    if(ET.receiveData()){
        // Serial.println("Go");
        codeuseDroite = codeuseset.codeuseDroiteet;
        codeuseGauche = -codeuseset.codeuseGaucheet;
    }
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











void stopRobot()
{
  xC = 0;
  xR = 0;
  yC = 0;
  yR = 0;
  orientationCible = 0;
  orientation = 0;
}

void avancerdroit(int distanceAParcourir)
{
  Serial.print("Avancer de ");
  Serial.println(distanceAParcourir);
  xC = distanceAParcourir;
}

void tourner(int angle)
{
  Serial.print("tourner de ");
  Serial.println(angle);
  orientationCible = angle;
}

void finMvt()
{
  if( abs(distanceCible) < 10 && finduMvt == false && abs(diffAngle)<10 )
  {
    finduMvt = true;
    //Serial.println("fin du mouvement");
  }
}
