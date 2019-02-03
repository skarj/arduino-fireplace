#include <SPI.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <GU800_GFX.h>
#include "DFRobotDFPlayerMini.h"

#define DISPLAY_CS 10
#define DISPLAY_DC 9
#define DISPLAY_RESET 7
#define IR_PIN 6
#define DFPLAYER_RX 4
#define DFPLAYER_TX 5


GU800 display(DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);

IRrecv irrecv(IR_PIN);
decode_results results;
unsigned long key_value = 0;

SoftwareSerial SoftwareSerial1(DFPLAYER_RX, DFPLAYER_TX);
DFRobotDFPlayerMini DFPlayer;
bool playing = 0;

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
  display.begin();
  display.clearDisplay();    // Clear display buffer

  SoftwareSerial1.begin(9600);
  delay(1000);
  DFPlayer.begin(SoftwareSerial1);
  DFPlayer.volume(10);      //Set volume value. From 0 to 30
}

void loop() {
  if (irrecv.decode(&results)){
 
    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch(results.value){
      case 0x807F48B7:
        displaytext(F("Heater"));
      break;
      case 0x807F28D7:
        displaytext(F("PowerOffOn"));
      break;
      case 0x807F58A7:
        displaytext(F("Vol+"));
        DFPlayer.volumeUp();
      break;
      case 0x807FA05F:
        displaytext(F("Vol-"));
        DFPlayer.volumeDown();
      break;
      case 0x807FB847:
        displaytext(F("Temp+"));
      break;  
      case 0x807F9867:
        displaytext(F("Temp-"));
      break;
      case 0x807F7887:
        if (playing == 0){
          displaytext(F("CrackleOn"));
          DFPlayer.enableLoopAll();
          playing = 1;
        }
        else {
          displaytext(F("CrackleOff"));
          DFPlayer.disableLoopAll();
          playing = 0;
        }
      break;
      case 0x807FF807:
        displaytext(F("Effect"));
      break;  
    }
    key_value = results.value;
    irrecv.resume(); 
  }
}

void displaytext(const __FlashStringHelper* text) {
  display.clearDisplay();             // Clear the buffer
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 32);           // Start at top-left corner
  display.println(text);
  display.display();                  // Show the display buffer on the screen. 
}

