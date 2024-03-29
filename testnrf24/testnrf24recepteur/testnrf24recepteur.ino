/*NRF24L01_Récepteur est un programme qui, grâce à un module NRF24L01, reçoit un tableau de valeurs
depuis une autre carte Arduino et les affiche dans le moniteur série.*/

#include <SPI.h>                                                       // appel des bibliothèques
#include <nRF24L01.h>
#include <RF24.h>
#include <EEPROM.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t adresse = 0xE8E8F0F0E1LL;        // adresse du canal de communication

RF24 radio(CE_PIN, CSN_PIN);                               // création de l'objet radio

int TableauPaire[10][2]; // tableau des paires recu                                      
int pairetableau=0;
const int stepPin = 7;  //5
const int dirPin = 6;   //2
const int enPin = 8;    //8 

const int btnplus=A4;    
const int btnmoins=A3;  

const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;

boolean dmrg = false;

const int depart = 30;
int a = 0;//adresse de la case value
byte value;

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

     // on met les broches en sorties
    pinMode(bit_A, OUTPUT);
    pinMode(bit_B, OUTPUT);
    pinMode(bit_C, OUTPUT);
    pinMode(bit_D, OUTPUT);

    // on commence par écrire le chiffre 0, donc toutes les sorites à l'état bas
    digitalWrite(bit_A, LOW);
    digitalWrite(bit_B, LOW);
    digitalWrite(bit_C, LOW);
    digitalWrite(bit_D, LOW);

    
}


void loop() {  
  int num = pairetableau+1;
  afficher(num);

  value = EEPROM.read(a);
  //remise à 0.
   
  if(dmrg==false){
     while(value>depart){
       diminution();
       value=value-5 ;                                         //diminution hauteur barre
    } 
    dmrg=true;
  }

   
  while(digitalRead(btnplus)){
    if(pairetableau<=6){
      pairetableau=pairetableau+1;
      while(digitalRead(btnplus)){}
      verifchangement();
    }
  }
  
  while(digitalRead(btnmoins)){
    if(pairetableau>0){
      pairetableau=pairetableau-1;
      while(digitalRead(btnmoins)){}
    }
  }
 
 if ( radio.available() )                                           // si des données sont présentes
 {
   radio.read( TableauPaire, sizeof(TableauPaire) );                        // lecture des données
   while(value<TableauPaire[pairetableau][1]){
     value=value+5;
     augmentation();    
   } 
   while(value>TableauPaire[pairetableau][1]){
     value=value-5;
     diminution();                                          //diminution hauteur barre
   } 
 
 }

 EEPROM.write(a, value);
}

void augmentation(){
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 5000; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  }

void diminution(){

  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  
  for(int x = 0; x < 5000; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  } 
 }

void verifchangement(){
  if(value>=30 && radio.available()){
    while(value<TableauPaire[pairetableau][1]){
      value=value+5;
      augmentation();
    }
    while(value>TableauPaire[pairetableau][1]){
      value=value-5;
      diminution();
    }
  }
}
  void afficher(char chiffre)
{
    // on met à zéro tout les bits du décodeur
    digitalWrite(bit_A, LOW);
    digitalWrite(bit_B, LOW);
    digitalWrite(bit_C, LOW);
    digitalWrite(bit_D, LOW);

    // On allume les bits nécessaires
    if(chiffre >= 8)
    {
        digitalWrite(bit_D, HIGH);
        chiffre = chiffre - 8;
    }
    if(chiffre >= 4)
    {
        digitalWrite(bit_C, HIGH);
        chiffre = chiffre - 4;
    }
    if(chiffre >= 2)
    {
        digitalWrite(bit_B, HIGH);
        chiffre = chiffre - 2;
    }
    if(chiffre >= 1)
    {
        digitalWrite(bit_A, HIGH);
        chiffre = chiffre - 1;
    }

    
}
