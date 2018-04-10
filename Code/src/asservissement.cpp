// inspiration : http://rco.fr.nf/index.php/2016/07/03/deplacement-dun-robot/

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



long codeuseDroite = 0;
long codeuseGauche = 0;

//Constantes permettant la transformation tic / millimètre
//40mm de diametere=>40*PImm de distance par 1024 tic de codeuse=>untic = 40*PI/1024
//40*PI/1024 = 0.12271846303
const double coeffGLong = 0.12271846303;
const double coeffDLong = 0.12271846303;

//Constantes permettant la transformation tic / degrés
//ecart codeuses 220mm => 360deg = 220pi mm =>360deg = 220pi/0.122718... tc/360deg => redivise par 360=>
const double coeffGAngl = 15.64445248;
const double coeffDAngl = 15.64445248;






// Déclaration des variables globales

// Variables (compteurs) qui vont stocker
// le nombre de tics comptés pour chaque codeur
long comptD = 0;
long comptG = 0;


//Variables allant contenir les positions du robots
double xR = 0.;
double yR = 0.;

//Variables permettant de stocker la position de la cible du robot
double xC = 20;
double yC = 0;

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


//Variables parametrant l'asservissement en angle du robot
double coeffP = 0.5;//0.4;
double coeffD = 0.0;//0.1;
double coeffI = 0.0;//0.000001;

double coeffProt = 0;
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
  // Pour tests frequence
  // unsigned long debut = millis();

  recupCodeuse();
  comptD = codeuseDroite;
  comptG = codeuseGauche;




  // supprimer mvt parasite/vibratipons
  // if ( abs(comptD) < 5 && abs(comptG) < 5)
  // {
  //   comptD = 0;
  //   comptG = 0;
  // }

  //calcul deplacement entre deux mvt codeuses
  dDist = (coeffGLong*comptG + coeffDLong*comptD)/2.;
	dAngl = coeffDAngl*comptD - coeffGAngl*comptG;



  dAngl = 0; //ATTENTION, A VIRER



	//Actualisation de la position du robot en xy et en orientation
	xR += dDist*cos(dAngl);
	yR += dDist*sin(dAngl);
	orientation += dAngl;

	//On calcule la distance séparant le robot de sa cible
	distanceCible = sqrt((xC-xR)*(xC-xR)+(yC-yR)*(yC-yR));


	//On calcule l'angle entre le robot et la cible
	consigneOrientation = signe * acos((xC-xR)/((xC-xR)*(xC-xR)*(yC-yR)*(yC-yR)));

  //resetCodeuse();
  deplaceRobot();



// if (dDist != 0)
// {
//       Serial.print("droite ");
//       Serial.println(comptD);
//       Serial.print("gauche ");
//       Serial.println(comptG);
//   Serial.print("sommeErreur : ");
//   Serial.println(sommeErreur);
//   Serial.print("Distance : ");
//   Serial.println(dDist);
//   Serial.print("Distance cible: ");
//   Serial.println(distanceCible);
//   Serial.print("Angle : ");
//   Serial.println(dAngl);
//   Serial.print("XR : ");
//   Serial.println(xR);
//   Serial.print("XY : ");
//   Serial.println(yR);
//   Serial.print("Angle : ");
//   Serial.println(dAngl);
//   Serial.println("-------------------------------------");
// }

  // Serial.print("XR : ");
  // Serial.println(xR);
  // Serial.print("XY : ");
  // Serial.println(yR);


  //resetCodeuse();
  deplaceRobot();

  // unsigned long fin = millis();
  // Serial.println(fin);
  // Serial.println(debut);
  // Serial.println("#################");

}


void deplaceRobot()
{
  if (xC-xR > 0)
  {
    distanceCible = distanceCible*(-1);
  }

  deltaErreurPasAngle = distanceCible - ErreurPasAnglePre;
  ErreurPasAnglePre = deltaErreurPasAngle;
  sommeErreur += distanceCible;
	//On détermine les commandes à envoyer aux moteurs
  // double maxI = coeffI*sommeErreur;
  // if (abs(maxI)>40)
  // {
  //   maxI = 40 * maxI/abs(maxI);
  // }
	cmdD = distanceCible*coeffP + coeffD*deltaErreurPasAngle + coeffI*sommeErreur;


	cmdG = cmdD;


  moteurDroit(cmdD);
  moteurGauche(cmdG);


}






void recupCodeuse()
{
  Serial1.println("a");
  String data[10];
  String content = "";
  char character;

  // if(Serial1.available())
  // {
  //   character = Serial1.read();
  //   if (character == '!')
  //   {
  //     while(!(Serial1.available()))
  //     {}
  //     character = Serial1.read();
  //     while(character != '!')
  //     {
  //       //Serial.println(character);
  //       content.concat(character);
  //       while(!(Serial1.available()))
  //       {}
  //       character = Serial1.read();
  //     }
  //   }
  // }
  //



  // char carlu; //variable contenant le caractère à lire
  // int cardispo = 0; //variable contenant le nombre de caractère disponibles dans le buffer
  // cardispo = Serial1.available();
  // Serial.println(cardispo);
  // bool fini = true;
  //   while(cardispo > 0 && fini) //tant qu'il y a des caractères à lire
  //   {
  //       carlu = Serial1.read(); //on lit le caractère
  //       //Serial.print(carlu); //puis on le renvoi à l’expéditeur tel quel
  //       if (carlu != -1)
  //       {
  //         Serial.println(carlu);
  //           if (carlu == '!')
  //           {
  //             fini = false;
  //           }
  //           else
  //           {
  //             content.concat(carlu);
  //           }
  //       }
  //       cardispo = Serial1.available(); //on relit le nombre de caractères dispo
  //   }
    // Serial.println("#################################aaaa");
    //Serial.println(content);


    //
    // splitString(content, ';', data);
    // codeuseDroite = data[0].toInt();
    // codeuseGauche = data[1].toInt();


    if(ET.receiveData()){
        // Serial.println("Go");
        codeuseDroite = codeuseset.codeuseDroiteet;
        codeuseGauche = -codeuseset.codeuseGaucheet;
    }

  //   if (codeuseDroite != 0)
  //   {
  //   Serial.print("D : ");
  //   Serial.println(codeuseDroite);
  //   Serial.print("G : ");
  //   Serial.println(codeuseGauche);
  // }
    // Serial.println("#################################aaaa");
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
