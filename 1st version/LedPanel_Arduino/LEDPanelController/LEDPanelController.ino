int controlPins[] = {2,3,4,5,6,7,8,9,10,11,12,13};
int syncPin = A0;
int resetPin = A1;
int state = 0;
float rate = 10.0;
unsigned long d = 0;
unsigned int t = 100;
int powers = 12;
int oldSync = 0;
int oldReset = 0;

char msg[4];

void setup() {
  pinMode(syncPin, INPUT);
  pinMode(resetPin, INPUT);
  for(int i = 0 ; i < powers ; i++){
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], HIGH);
  }
  d = (1000000.0/rate) - t;
  Serial.begin(230400);
}

void loop() {
  int reset = digitalRead(resetPin);
  if (reset != oldReset) {
    digitalWrite(controlPins[state], HIGH); // OFF
    state = 10;
  }
  oldReset = reset;
  
  int sync = digitalRead(syncPin);
  while(sync == oldSync){
    oldSync = sync;
    sync = digitalRead(syncPin);
  }
  oldSync = sync;
  
  digitalWrite(controlPins[state], HIGH); // OFF
  state++;
  if(state == 12) state = 0;
  digitalWrite(controlPins[state], LOW); // ON
}
