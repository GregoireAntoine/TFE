/*NRF24L01_Récepteur est un programme qui, grâce à un module NRF24L01, reçoit un tableau de valeurs
depuis une autre carte Arduino et les affiche dans le moniteur série.*/

#include <SPI.h>                                                       // appel des bibliothèques
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t adresse = 0xE8E8F0F0E1LL;        // adresse du canal de communication

RF24 radio(CE_PIN, CSN_PIN);                               // création de l'objet radio

int TableauPaire[10][2]; // tableau des paires recu                                      
int verif[10][2] = { {1, 30},{2, 30},{3, 30},{4, 30},{5, 30},{6, 30},{7, 30},{8, 30},{9, 30},{10, 30}}; // tableau des paires;                                        //descente moteur

const int stepPin = 7;  //5
const int dirPin = 6;   //2
const int enPin = 8;    //8 

const int btnplus=A4;    
const int btnmoins=A3;  

const int btnun = 2;
const int btndeux = 3;
const int btnquatre = 4 ;
const int btnhuit = 5;



int pairetableau=0;


void setup()   
{
  Serial.begin(9600);                                               // initialisation du moniteur série
  radio.begin();                                                         // initialisation du module NRF24L01
  radio.openReadingPipe(1,adresse);                   // configuration du canal de communication du module NRF24L01     
  radio.startListening();                            // configuration du module NRF24L01 en récepteur
  
 
    pinMode(stepPin,OUTPUT); 
    pinMode(dirPin,OUTPUT);

    pinMode(enPin,OUTPUT);
    digitalWrite(enPin,LOW);

    pinMode(btnplus, INPUT);
    pinMode(btnmoins, INPUT);

    pinMode(btnquatre,OUTPUT);
    pinMode(btnun,OUTPUT);
    pinMode(btnhuit,OUTPUT);
    pinMode(btndeux,OUTPUT);
}


void loop() {  
 
  while(digitalRead(btnplus)){
    if(pairetableau<=6){
      pairetableau=pairetableau+1;
      while(digitalRead(btnplus)){}
    }
  }
  
  while(digitalRead(btnmoins)){
    if(pairetableau>0){
      pairetableau=pairetableau-1;
      while(digitalRead(btnmoins)){}
    }
  }

  Serial.println(pairetableau);
  int num = pairetableau+1;
  Serial.println("num");
  Serial.println(num);
   Serial.println(TableauPaire[pairetableau][0]);
  Serial.println(TableauPaire[7][1]);
  switch (num) {
    case 1:
       digitalWrite(btnun,HIGH);
       digitalWrite(btnhuit,LOW);
       digitalWrite(btndeux,LOW);
       digitalWrite(btnquatre,LOW);
        
    break;
    case 2:
       digitalWrite(btnun,LOW);
       digitalWrite(btndeux,HIGH);
       digitalWrite(btnhuit,LOW);
       digitalWrite(btnquatre,LOW);
    break;
    case 3:
       digitalWrite(btnun,HIGH);
       digitalWrite(btndeux,HIGH);
       digitalWrite(btnhuit,LOW);
       digitalWrite(btnquatre,LOW);
    break;
    case 4:
       digitalWrite(btnun,LOW);
       digitalWrite(btnhuit,LOW);
       digitalWrite(btndeux,LOW);
       digitalWrite(btnquatre,HIGH);
    
    break;
    case 5:
       digitalWrite(btnquatre,HIGH);
       digitalWrite(btnun,HIGH);
       digitalWrite(btnhuit,LOW);
       digitalWrite(btndeux,LOW);
    break;
    case 6:
     digitalWrite(btnquatre,HIGH);
     digitalWrite(btndeux,HIGH);
     digitalWrite(btnun,LOW);
     digitalWrite(btnhuit,LOW);
    break;
    case 7:
     digitalWrite(btnquatre,HIGH);
     digitalWrite(btndeux,HIGH);
     digitalWrite(btnun,HIGH);
     digitalWrite(btnhuit,LOW);
    break;
    case 8:
     digitalWrite(btnhuit,HIGH);
     digitalWrite(btnun,LOW);
     digitalWrite(btnquatre,LOW);
     digitalWrite(btndeux,LOW);
    break;
    case 9:
     digitalWrite(btnhuit,HIGH);
     digitalWrite(btnun,HIGH);
     digitalWrite(btnquatre,LOW);
     digitalWrite(btndeux,LOW);
    break;
 }
  

  
 if ( radio.available() )                                           // si des données sont présentes
 {
   radio.read( TableauPaire, sizeof(TableauPaire) );                        // lecture des données
   //Serial.print(TableauPaire[pairetableau][1]);                                     // affichage dans le moniteur série
  //Serial.println(verif[pairetableau][1]);
   
  
   while(verif[pairetableau][1]<TableauPaire[pairetableau][1]){
     verif[pairetableau][1]=verif[pairetableau][1]+5;
     augmentation();    
   } 
   while(verif[pairetableau][1]>TableauPaire[pairetableau][1]){
     verif[pairetableau][1]=verif[pairetableau][1]-5;
     diminution();                                          //diminution hauteur barre
   } 
 
 }

}




void augmentation(){
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 1600; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  }



void diminution(){
  
      digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  
  for(int x = 0; x < 1600; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  } }
    
