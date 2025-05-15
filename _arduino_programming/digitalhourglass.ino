const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;
int led = 2;
long interval = 10000; //10 seconds
void setup() {
  for(int x = 2;x<8;x++){
    pinMode(x, OUTPUT);
  }
  pinMode(switchPin, INPUT);
}
void loop() {
  unsigned long currentTime = millis();
  if(currentTime - previousTime > interval){
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    led++;
    if(led == 7){
    }
  }
  switchState = digitalRead(switchPin);
  if(switchState != prevSwitchState){
    for(int x = 2;x<8;x++){
      digitalWrite(x, LOW);
    }
    led = 2;
    previousTime= currentTime;
  }  
  if(led == 7){
    digitalWrite(led, HIGH);
    delay(10000);//wait 10 secs
    digitalWrite(led, LOW);
    led = 2;
    for(int x = 2;x<8;x++){
      digitalWrite(x, LOW);
    }
    delay(10000);//wait 10 secs
  }
  prevSwitchState = switchState;
}
