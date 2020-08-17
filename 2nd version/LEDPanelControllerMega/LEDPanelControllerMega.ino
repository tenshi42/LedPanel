#include "Leters.h"

int controlPins[] = {22,23,24,25,26,27,28,29,30,31,32,33};
int ledPins[] = {38,39,40,41,42,43,44,46,47,48,49,50,51,52};
int state = 0;
float rate = 10.0;
unsigned long d = 0;
unsigned int t = 100;
int powers = 12;
int leds = 14;
int oldSync = 0;
int oldReset = 0;

int frame = 0;

int ThermistorPin = A0;
int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor

char msg[4];

int msgGrid[3*2*10][7];
int nbLetters = 0;

void setup() {
  for(int i = 0 ; i < powers ; i++){
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], HIGH);
  }

  for(int i = 0 ; i < leds ; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }
  
  d = (10000000.0/rate) - t;
  Serial.begin(9600);

  char txt[] = "350J";
  setMessage(txt);

  for(int j = 0 ; j < 5 ; j++){
      for(int k = 0 ; k < 7 ; k++){
        Serial.print(msgGrid[j][k]);
      }
      Serial.println();
  }

  state = nbLetters * 3 - 1;
}

void loop() {  
  digitalWrite(controlPins[state], HIGH); // OFF
  
  state++;
  if(state >= powers) state = 0;

  writeLine(msgGrid[state*2], msgGrid[state*2 + 1]);
  
  delayMicroseconds(t);
  //delay(10);
  //delay(1);
  digitalWrite(controlPins[state], LOW); // ON
  delayMicroseconds(d);
  //delay(10);
  //delay(4);

  frame++;
  if(frame % 10000 == 0){
    getTemps();
    char bb[4];
    dtostrf(T, 2, 1, bb);
    setMessage(bb);
    Serial.println(bb);
  }
}

void intToBin(int a, int* ret){
  //ret = new int[7];

  int b = a;
  
  for(int ii = 0 ; ii < 7 ; ii++){
    ret[ii] = b % 2;
    ret[ii] = (ret[ii] + 1) % 2;
    b /= 2;
    //Serial.println(ret[ii]);
  }
}

void setMessage(char pmsg[]){
  //Serial.println(pmsg);
  nbLetters = strlen(pmsg);
  
  for(int i = 0 ; i < nbLetters ; i++){
    int vLetter = ((int)pmsg[i]) - 32;
    const int *iLetter = letters[vLetter];
    
    for(int j = 0 ; j < 5 ; j++){
      //Serial.println(iLetter[j]);
      //Serial.println();
      int tmp[7] = {0,0,0,0,0,0,0};
      intToBin(iLetter[j], tmp);
      for(int k = 0 ; k < 7 ; k++){
        msgGrid[i*6 + j][k] = tmp[k];
        //Serial.print(msgGrid[i*6 + j][k]);
        //Serial.print(' ');
      }
      //Serial.println();
    }
    
    int tmp[7] = {0,0,0,0,0,0,0};
    intToBin(0x00, tmp);
    for(int k = 0 ; k < 7 ; k++){
      msgGrid[i*6 + 5][k] = tmp[k];
    }
  }
}

void writeLine(int line1[], int line2[]){
  for(int i = 0 ; i < 7 ; i++){
    //Serial.println(line1[i]);
    digitalWrite(ledPins[i + 7], line1[6-i]);
    digitalWrite(ledPins[i], line2[6-i]);
    //Serial.print(line1[i]);
  }
}

float getTemps(){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  T = T - 273.15; //convert Kelvin to Celcius
}

