#include <Arduino.h>

#define VRX1 36
#define VRY1 39
#define SW 34

#define LED 2



void setup() {
  Serial.begin(115200);

  pinMode(VRX1, INPUT);
  pinMode(VRY1, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

}

void loop() {
  while (1){
    
  
  Serial.print(" VRX1: ");
  Serial.print(analogRead(VRX1));
  Serial.print(" VRY1: ");
  Serial.print(analogRead(VRY1));
  Serial.print(" SW: ");
  Serial.print(digitalRead(SW));
  Serial.println(" ");
  delay(100);


  }
}

