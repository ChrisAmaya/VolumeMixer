#include "Keyboard.h"

const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
int previous = 1;
int analogSliderValues[NUM_SLIDERS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }
  pinMode(4,INPUT);
  pinMode(8,INPUT);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);

 //Serial.print(analogRead(8));
 if (analogRead(8) == 1023){
    if (previous == 1){
      //Serial.print("===============================");
      Keyboard.press(0x80);
      Keyboard.press(0x82);
      Keyboard.press(0xD8);
      Keyboard.release(0x80);
      Keyboard.release(0x82);
      Keyboard.release(0xD8);   
      previous = 2;
      delay(100);
    }  
 }
 if (analogRead(8) != 1023){
    if (previous == 2){
      //Serial.print("+++++++++++++++++++++++++++++++++");
      Keyboard.press(0x80);
      Keyboard.press(0x82);
      Keyboard.press(0xD7);
      Keyboard.release(0x80);
      Keyboard.release(0x82);
      Keyboard.release(0xD7);
      previous = 1;
      delay(100);
    }
 }

  
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
