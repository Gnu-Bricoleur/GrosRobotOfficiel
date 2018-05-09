#include <CircularBuffer.h>


//#define TAILLE 10
//#define SEUIL 500
//
//
//CircularBuffer<int,TAILLE> avant;
//CircularBuffer<int,TAILLE> arriere;
//CircularBuffer<int,TAILLE> droite;
//CircularBuffer<int,TAILLE> gauche;



int trig = 11;
int echo = 12;
long lecture_echo;
long cm;



void setup()
{
  pinMode(2, OUTPUT);
  
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

void loop()
{

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo / 58;
  //Serial.println(cm);

  if(cm < 30)
  {
    Serial.println("obstacle");
    digitalWrite(13, LOW);
  }
  else
  {
    digitalWrite(13, HIGH);
   
  }
  
//  int valavant = analogRead(A0);
//  int valarriere = analogRead(A1);
//  int valdroite = analogRead(A2);
//  int valgauche = analogRead(A3);
//  //Serial.println(valavant);
//
//  avant.push(valavant);
//  arriere.push(valarriere);
//  droite.push(valdroite);
//  gauche.push(valgauche);
//
//  int sum = 0;
//  for(int i = 0; i < TAILLE; i++)
//  {
//    sum += avant[i];
//  }
//  if(sum/TAILLE > SEUIL)
//  {
//    digitalWrite(13, HIGH);
//    //Serial.print("avant");
//  }
//
//
//  sum = 0;
//  for(int i = 0; i < TAILLE; i++)
//  {
//    sum += arriere[i];
//  }
//  if(sum/TAILLE > SEUIL)
//  {
//    digitalWrite(13, HIGH);
//    //Serial.print("arriere");
//  }
//
//
//  sum = 0;
//  for(int i = 0; i < TAILLE; i++)
//  {
//    sum += droite[i];
//  }
//  if(sum/TAILLE > SEUIL)
//  {
//    digitalWrite(13, HIGH);
//    //Serial.print("droite");
//  }
//
//
//  sum = 0;
//  for(int i = 0; i < TAILLE; i++)
//  {
//    sum += gauche[i];
//  }
//  if(sum/TAILLE > SEUIL)
//  {
//    digitalWrite(13, HIGH);
//    //Serial.print("gauche");
//  }

//  delay(500);
//  digitalWrite(13, LOW);
//  Serial.println("");
  
}
