/*NRF24L01_Emetteur est un programme qui, grâce à un module NRF24L01, envoie un tableau de valeurs à une autre carte Arduino.*/

#include <SPI.h>                                                          // appel des bibliothèques
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h> 
#include <Wire.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t adresse = 0xE8E8F0F0E1LL;           // adresse du canal de communication
int data[1]={0};
boolean leed = false;



const int BtnDescente = 5;
const int BtnMonte = 7;
const int BtnChoix = 6;


boolean Curseur = false;

// variables pour début d'affichage.
bool DebutAffichage=true;

// variable pour faire la hauteur et les num de paires
int TableauPaire[9][2] = { {1, 30},{2, 30},{3, 30},{4, 30},{5, 30},{6, 30},{7, 30},{8, 30},{9, 30}}; // tableau des paires
const int Hauteur = 1;
const int ValPaire = 0;
int Paire = 0;
int a;

LiquidCrystal_I2C lcd(0x27, 16, 2);
RF24 radio(CE_PIN, CSN_PIN);                                   // création de l'objet radio

void setup()
{ Serial.begin(9600);         
  radio.begin();                                                              // initialisation du module NRF24L01
  radio.openWritingPipe(adresse);                             // configuration du canal de communication du module NRF24L01
  lcd.init();
  lcd.backlight();

  pinMode (BtnDescente, INPUT);
  pinMode(7, INPUT);
  pinMode(BtnChoix, INPUT);
}

void loop()   
{
  //début de l'écran de contrôle.
 
 if(DebutAffichage==true){
  lcd.setCursor(15,1);
  lcd.print("*");
  lcd.setCursor(0,0);
  lcd.print("Paire :");
  lcd.setCursor(0,1);
  lcd.print("Hauteur :");
  DebutAffichage=false;
 }

  
while (digitalRead(BtnChoix)==HIGH){
  Serial.print(Curseur);
if (Curseur==true){
  Serial.print(Curseur);
  lcd.setCursor(15,0);
  lcd.print(" ");
  lcd.setCursor(15,1);
  lcd.print("*");
  Curseur=false;
  }else{
     Serial.print(Curseur);
    lcd.setCursor(15,0);
  lcd.print("*");
  lcd.setCursor(15,1);
  lcd.print(" ");
  Curseur=true;
    }
    while (digitalRead(BtnChoix)==HIGH){}    
}



//modification numéro de paires
if(Curseur==true){
  
  while (digitalRead(BtnMonte)==HIGH){
if(Paire<8){
    
   Paire=Paire+1;
    
}
     while (digitalRead(BtnMonte)==HIGH){}
    }  
while (digitalRead(BtnDescente)==HIGH){
  if (Paire>0){
  Paire=Paire-1;
  
  }
  while (digitalRead(BtnDescente)==HIGH){}
  }

   
  }
//modification hauteur de la paire
if(Curseur==false){

  while (digitalRead(BtnMonte)==HIGH){
  if(TableauPaire[Paire][Hauteur]<150){
    data[0]=data[0]+5;
   TableauPaire[Paire][Hauteur]=TableauPaire[Paire][Hauteur]+5;
    
  }
     while (digitalRead(BtnMonte)==HIGH){}
    }  
while (digitalRead(BtnDescente)==HIGH){
  
  if(TableauPaire[Paire][Hauteur]>30){
    data[0]=data[0]-5;
  TableauPaire[Paire][Hauteur]=TableauPaire[Paire][Hauteur]-5;
  Serial.println(TableauPaire[Paire][ValPaire]);
  }
    
  while (digitalRead(BtnDescente)==HIGH){}
  }
  }

if(TableauPaire[Paire][Hauteur]<100){
  lcd.setCursor(14,1);
  lcd.print(" ");
  }
 lcd.setCursor(8,0);
  lcd.print(TableauPaire[Paire][ValPaire]);
  lcd.setCursor(10,1);
  lcd.print(TableauPaire[Paire][Hauteur]);
  lcd.print("cm");


   Serial.println(TableauPaire[0][1]);
    
    
  radio.write( TableauPaire, sizeof(TableauPaire) );// envoi des données
  }
