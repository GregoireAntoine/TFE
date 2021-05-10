const int btn1= 4;
const int btn2= 5;
const int LED1 = 12;
const int LED2= 13;
boolean actif = true;

void setup() {
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

}

void loop() {
if (( actif == false )){
    while(digitalRead(btn1)==HIGH){
    digitalWrite(LED1, LOW);
    actif = true;
     while(digitalRead(btn1)==HIGH){};
    };
    };

  
  if (( actif == true )){
    while(digitalRead(btn1)==HIGH){
    digitalWrite(LED1, HIGH);
    actif = false;
     while(digitalRead(btn1)==HIGH){};
    };
    };
};
 
