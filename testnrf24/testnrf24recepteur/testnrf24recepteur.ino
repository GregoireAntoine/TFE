/*NRF24L01_Récepteur est un programme qui, grâce à un module NRF24L01, reçoit un tableau de valeurs
depuis une autre carte Arduino et les affiche dans le moniteur série.*/

#include <SPI.h>                                                       // appel des bibliothèques
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t adresse = 0xE8E8F0F0E1LL;        // adresse du canal de communication

RF24 radio(CE_PIN, CSN_PIN);                               // création de l'objet radio

int data[1];
int VieilleData[1];

void setup()   
{
  Serial.begin(9600);                                               // initialisation du moniteur série
  radio.begin();                                                         // initialisation du module NRF24L01
  radio.openReadingPipe(1,adresse);                   // configuration du canal de communication du module NRF24L01     
  radio.startListening();                            // configuration du module NRF24L01 en récepteur
  
  pinMode(2, OUTPUT); 
}


void loop() {  
  if ( radio.available() )                                           // si des données sont présentes
  {
    radio.read( data, sizeof(data) );                        // lecture des données
    Serial.print("data[0]=");                                     // affichage dans le moniteur série
    Serial.println(data[0]);
    
    if( data[0]!=VieilleData[0]){
      digitalWrite(2,HIGH);
      delay(2000);
      digitalWrite(2, LOW);
      }
    
     VieilleData[0]=data[0];
  }
}
